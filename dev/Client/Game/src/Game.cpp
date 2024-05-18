#include "Game.hpp"
#include "NPCPub.hpp"
#include "ConfigUser.hpp"
#include "ConfigDev.hpp"
#include "Random.hpp"

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
    _ClientNetwork->send<MessageType::STRING>(&playerName, 1U);

    /* Get NPC size list from server */
    uint32_t NPCListSize;
    _ClientNetwork->receive(&NPCListSize, 1U);
    _NPCs->resize(NPCListSize);

    /* Receive NPCs from server */
    for (size_t i = 0; i < NPCListSize; i++)
    {
        string data[2];
        _ClientNetwork->receive(data, 2U);
        _NPCs->at(i) = make_shared<NPC>(data[0], data[1]);
    }

    /* Initialize event and command structures */
    _ResetInputEvent();
    _OutputCommands.NPCsCommands.resize(_NPCs->size());

    /* Send ready status to server */
    _GameStatus = GameStatus::READY;
    _ClientNetwork->send<MessageType::STATUS>(&_GameStatus);
}

/**
 * @brief Reset structure input event to default values
 *
 */
void Game::_ResetInputEvent()
{
    _InputEvents.isGamePaused    = (_GameStatus == GameStatus::PAUSE);
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
    _ClientNetwork->receive(&_GameStatus);
}

/**
 * @brief Send InputEvent structure to server
 *
 */
void Game::_SynchronizeToServer() const
{
    _ClientNetwork->send<MessageType::INPUT_EVENTS>(&_InputEvents);
}

/**
 * @brief Receive outputCommand structure from server
 *
 */
void Game::_SynchronizeFromServer()
{
    _ClientNetwork->receive(&_OutputCommands);
}

/**
 * @brief Main loop of the game on client side
 *
 */
void Game::play()
{
    _WaitForStatus();

    while ((_Screen->isWindowOpen()) && (_GameStatus != GameStatus::STOP))
    {
        /* Catch events */
        _CatchEvents();

        /* Send events to server */
        _SynchronizeToServer();

        /* Receive commands from server */
        _SynchronizeFromServer();

        /* Update according to commands */
        _UpdateGame();

        /* Refresh screen */
        _Draw();
    }
}

/**
 * @brief Update positions after receiving commands from server
 *
 */
void Game::_UpdateGame()
{
    _GameStatus = _OutputCommands.gameStatus;
    _Player->setAlive(_OutputCommands.playerCommand.isAlive);

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
