#include "Game.hpp"
#include "NPCPub.hpp"
#include "ConfigUser.hpp"
#include "ConfigDev.hpp"
#include "Random.hpp"
#include <csignal>
#include <atomic>

static volatile atomic_bool _GameRunning;

Game::Game(const string &playerName, const string &configName)
{
    _GameStatus = GameStatus::INIT;

    _ClientNetwork = make_unique<ClientNetwork>(configName);
    _Board         = make_shared<Board>();
    _Player        = make_shared<Player>(playerName);
    _Screen        = make_shared<Screen>(ConfigUser::windowTitle);
    _NPCs          = make_shared<vector<shared_ptr<NPC>>>(1);

    _Board->computeVertices(ConfigDev::tileSize, Vector2u(ConfigDev::imageSizeTileWidth, ConfigDev::imageSizeTileHeight));

    /* Send player name to server */
    const bool sendStatus = _ClientNetwork->send<MessageType::STRING>(&playerName, 1U);
    bool     readStatus;
    uint32_t NPCListSize;

    if (sendStatus == true)
    {
        /* Get NPC size list from server */
        readStatus = _ClientNetwork->receive(&NPCListSize, nullptr, 1U);
    }
    else
    {
        readStatus = false;
    }

    if (readStatus == true)
    {
        _NPCs->resize(NPCListSize);

        /* Initialize event and command structures */
        _ResetInputEvent();
        _OutputCommands.NPCsCommands.resize(NPCListSize);
    }
    else
    {
        _GameStatus = GameStatus::STOP;
    }

    /* Receive NPCs from server */
    for (size_t i = 0; (readStatus == true) && (i < NPCListSize); i++)
    {
        string data[2];
        readStatus = _ClientNetwork->receive(data, nullptr, 2U);

        if (readStatus == true)
        {
            _NPCs->at(i) = make_shared<NPC>(data[0], data[1]);
        }
    }

    if (readStatus == true)
    {
        _GameRunning   = true;
        _ServerRunning = true;
        _GameStatus    = GameStatus::READY;

        _ClientNetwork->send<MessageType::STATUS>(&_GameStatus);
    }
    else
    {
        _GameRunning   = false;
        _ServerRunning = false;
        _GameStatus    = GameStatus::STOP;

        _ClientNetwork->send<MessageType::CLIENT_STOP>(&_GameStatus);
    }
}

/**
 * @brief Reset structure input event to default values
 *
 */
void Game::_ResetInputEvent()
{
    _InputEvents.isGamePaused    = (_GameStatus == GameStatus::PAUSE);
    _InputEvents.isWindowClosed  = false;
    _InputEvents.isClientStopped = false;
    _InputEvents.movePlayerDown  = false;
    _InputEvents.movePlayerUp    = false;
    _InputEvents.movePlayerLeft  = false;
    _InputEvents.movePlayerRight = false;
}

/**
 * @brief Wait to server to send new status
 *
 */
void Game::_WaitForStatus()
{
    const bool status = _ClientNetwork->receive(&_GameStatus);

    /* Error when reading the message */
    if (status == false)
    {
        _ServerRunning = false;
    }
}

/**
 * @brief Send InputEvent structure to server
 *
 */
void Game::_SynchronizeToServer()
{
    const bool status = _ClientNetwork->send<MessageType::INPUT_EVENTS>(&_InputEvents);

    /* Error when sending the message */
    if (status == false)
    {
        _ServerRunning = false;
    }
}

/**
 * @brief Receive outputCommand structure from server
 *
 */
void Game::_SynchronizeFromServer()
{
    const bool status = _ClientNetwork->receive(&_OutputCommands);
    _GameStatus       = _OutputCommands.gameStatus;

    /* Error when reading message or if server has stopped the game */
    if ((status == false) || (_OutputCommands.gameStatus == GameStatus::STOP))
    {
        _ServerRunning = false;
    }
}

/**
 * @brief Main loop of the game on client side
 *
 */
void Game::play()
{
    _Shutdown = thread(&Game::_HandleShutdown, this);

    _WaitForStatus();

    while ((_GameStatus != GameStatus::STOP) && (_GameRunning == true) && (_ServerRunning == true))
    {
        /* Catch events */
        _CatchEvents();

        /* Send events to server */
        _SynchronizeToServer();

        /* Continue execution if window is still opened */
        if (_InputEvents.isWindowClosed == false)
        {
            /* Receive commands from server */
            _SynchronizeFromServer();

            /* Update according to commands */
            _UpdateGame();

            /* Refresh screen */
            _Draw();
        }
        else
        {
            _GameRunning = false;
        }
    }
}

/**
 * @brief Update positions after receiving commands from server
 *
 */
void Game::_UpdateGame()
{
    _Player->setAlive(_OutputCommands.playerCommand.isAlive);

    if (_OutputCommands.playerCommand.isAlive == true)
    {
        if (_GameStatus == GameStatus::PLAY)
        {
            _Player->setPosition(_OutputCommands.playerCommand.position, _OutputCommands.playerCommand.hasMoved);
            _Player->setHealth(_OutputCommands.playerCommand.health);

            for(size_t i = 0; i < _NPCs->size(); i++)
            {
                _NPCs->at(i)->setAlive(_OutputCommands.NPCsCommands[i].isAlive);
                _NPCs->at(i)->setHealth(_OutputCommands.NPCsCommands[i].health);
                _NPCs->at(i)->setPosition(_OutputCommands.NPCsCommands[i].position);
            }
        }
    }
    else
    {
        _GameRunning = false;
        _GameStatus  = GameStatus::STOP;
    }
}

/**
 * @brief catch event and user inputs
 *
 */
void Game::_CatchEvents()
{
    _ResetInputEvent();
    _Screen->catchEvents(_InputEvents);

    _GameStatus = (_InputEvents.isGamePaused == true) ? GameStatus::PAUSE : GameStatus::PLAY;
}

/**
 * @brief Draw all on the screen
 *
 */
void Game::_Draw() const
{
    if (_GameStatus == GameStatus::PLAY)
    {
        _Screen->drawAll(*_Board, *_Player, *_NPCs);
    }
}

/**
 * @brief Handle shutting down the client properly
 *
 */
void Game::_HandleShutdown()
{
    signal(SIGINT, [](int32_t signum)
    {
        (void)signum;
        _GameRunning = false;
    });

    while (_GameRunning == true)
    {
        sleep(Time(milliseconds(500)));
    }
}

Game::~Game()
{
    if (_InputEvents.isWindowClosed == true)
    {
        cout << "Closing window. Good bye !" << endl;
    }
    else if (_Player->isAlive() == false)
    {
        cout << "Player is dead, end of game." << endl;
    }
    else if (_ServerRunning == false)
    {
        cout << "Server has stopped, end of game." << endl;
    }
    else if (_GameRunning == false)
    {
        cout << "Stopping client ... " << endl;

        _InputEvents.isClientStopped = true;
        _ClientNetwork->send<MessageType::CLIENT_STOP>(&_InputEvents);
    }
    else if (_GameStatus == GameStatus::STOP)
    {
        cout << "Server stopped running, stopping game." << endl;
    }

    _GameRunning = false;
    if (_Shutdown.joinable() == true)
    {
        _Shutdown.join();
    }
}
