#include "Game.hpp"
#include "GamePrv.hpp"
#include "ConfigUser.hpp"
#include "ConfigDev.hpp"
#include "Random.hpp"

Game::Game(const string& configName)
{
    _GameStatus    = GameStatus::INIT;

    _ServerNetwork = make_unique<ServerNetwork>(configName);
    _Board         = make_shared<Board>();
    _NPCs          = make_shared<vector<shared_ptr<NPC>>>(10U * static_cast<uint32_t>(ConfigUser::difficulty));

    for (size_t i = 0; i < _NPCs->size(); i++)
    {
        _NPCs->at(i) = make_shared<NPC>("NPC_" + to_string(i), NPCColorsString[Random::getRandomInteger(0, static_cast<uint32_t>(NPCColors::COUNT) - 1U)]);
    }

    _Board->computeVertices(ConfigDev::tileSize, Vector2u(ConfigDev::imageSizeTileWidth, ConfigDev::imageSizeTileHeight));
    _BoardSizeInPixel = Vector2u(_Board->getWidthInTile() * ConfigDev::tileSize, _Board->getHeightInTile() * ConfigDev::tileSize);

    /* Initialize event and command structures */
    _OutputCommands.NPCsCommands.resize(_NPCs->size());

    _GameStatus = GameStatus::WAITING;
}

/**
 * @brief Update structure output command
 *
 */
void Game::_UpdateOutputCommands()
{
    _OutputCommands.gameStatus = _GameStatus;

    _OutputCommands.playerCommand.isAlive  = _Player->isAlive();
    _OutputCommands.playerCommand.health   = _Player->getHealth();
    _OutputCommands.playerCommand.position = _Player->getPosition();

    for (size_t i = 0; i < _OutputCommands.NPCsCommands.size(); i++)
    {
        _OutputCommands.NPCsCommands[i].isAlive  = _NPCs->at(i)->isAlive();
        _OutputCommands.NPCsCommands[i].health   = _NPCs->at(i)->getHealth();
        _OutputCommands.NPCsCommands[i].position = _NPCs->at(i)->getPosition();
    }
}

/**
 * @brief Send data to initialise the client
 *
 */
void Game::_sendInitData()
{
    /* Create a player after the name receive from client */
    string playerName;
    _ServerNetwork->receiveData<string>(&playerName, 1);
    _Player = make_shared<Player>(playerName);

    /* Send all NPCs to client */
    const uint32_t NPCSize = _NPCs->size();
    _ServerNetwork->sendData<uint32_t>(&NPCSize, 1U);

    for (size_t i = 0; i < NPCSize; i++)
    {
        _ServerNetwork->sendNPC(*(_NPCs->at(i)));
    }
}

/**
 * @brief Wait for a player to connect
 *
 */
void Game::_waitForPlayer()
{
    _ServerNetwork->acceptClient();

    _sendInitData();

    /* Wait for player to be ready */
    _ServerNetwork->receiveGameStatus(&_GameStatus);
}

/**
 * @brief Send outputCommands structure to client
 *
 */
void Game::_SynchronizeToClient() const
{
    _ServerNetwork->sendStructure<outputCommands>(&_OutputCommands);
}

/**
 * @brief Receive inputEvents structure from client
 *
 */
void Game::_SynchronizeFromClient()
{
    _ServerNetwork->receiveStructure<inputEvents>(&_InputEvents);
}
/**
 * @brief Move player after computing new position
 *
 */
void Game::_MovePlayer()
{
    if (_GameStatus == GameStatus::PLAY)
    {
        if (_Player->isAlive() == true)
        {
            const Vector2u playerSize     = _Player->getSize();
            const int32_t playerSpeed     = static_cast<int32_t>(_Player->getSpeed());
            Vector2f currentPos           = _Player->getPosition();
            bool hasMoved                 = false;

            /* Move player left */
            if (_InputEvents.movePlayerLeft == true)
            {
                if ((currentPos.x - playerSpeed) >= 0)
                {
                    currentPos.x -= playerSpeed;
                    hasMoved      = true;
                }
                else
                {
                    /* Sprite out of bound, do not exceed window size */
                    currentPos.x = 0;
                    hasMoved     = false;
                }
            }

            /* Move player right */
            if (_InputEvents.movePlayerRight == true)
            {
                if ((currentPos.x + playerSpeed + playerSize.x) <= _BoardSizeInPixel.x)
                {
                    currentPos.x += playerSpeed;
                    hasMoved     |= true;
                }
                else
                {
                    /* Sprite out of bound, do not exceed window size */
                    currentPos.x  = _BoardSizeInPixel.x - playerSize.x;
                    hasMoved     |= false;
                }
            }

            /* Move player up */
            if (_InputEvents.movePlayerUp == true)
            {
                if ((currentPos.y - playerSpeed) >= 0)
                {
                    currentPos.y -= playerSpeed;
                    hasMoved     |= true;
                }
                else
                {
                    /* Sprite out of bound, do not exceed window size */
                    currentPos.y  = 0;
                    hasMoved     |= false;
                }
            }

            /* Move player down */
            if (_InputEvents.movePlayerDown == true)
            {
                if ((currentPos.y + playerSpeed + playerSize.y) <= _BoardSizeInPixel.y)
                {
                    currentPos.y += playerSpeed;
                    hasMoved     |= true;
                }
                else
                {
                    /* Sprite out of bound, do not exceed window size */
                    currentPos.y  = _BoardSizeInPixel.y - playerSize.y;
                    hasMoved     |= false;
                }
            }

            /* Update player final position */
            _Player->setPosition(currentPos, hasMoved);
            _OutputCommands.playerCommand.hasMoved = hasMoved;
        }
        else
        {
            /* Player is dead, game over */
            _GameStatus = GameStatus::STOP;
        }
    }
}

/**
 * @brief Move NPCs by computing new position randomly
 *
 */
void Game::_MoveNPCs()
{
    if (_GameStatus == GameStatus::PLAY)
    {
        for (auto npc : *_NPCs)
        {
            if (npc->isAlive())
            {
                const float_t changeDirProbaX = Random::getRandomFloat(0.0f, 1.0f);
                const float_t changeDirProbaY = Random::getRandomFloat(0.0f, 1.0f);
                float_t deltaX                = Random::getRandomInteger(0, npc->getSpeed());
                float_t deltaY                = Random::getRandomInteger(0, npc->getSpeed());
                const float_t absDeltaX       = abs(deltaX);
                const float_t absDeltaY       = abs(deltaY);

                const Vector2u npcSize     = npc->getSize();
                const Vector2f previousPos = npc->getPreviousPosition();
                Vector2f currentPos        = npc->getPosition();

                /* Compute new directions */
                if (currentPos.x == (_BoardSizeInPixel.x - npcSize.x))
                {
                    /* Force moving left */
                    deltaX = -deltaX;
                }
                else if (currentPos.x != 0U)
                {
                    /* Check X direction change probability */
                    if (changeDirProbaX < CHANGE_DIRECTION_THRESHOLD)
                    {
                        /* If npc has moved left, change sign to move in the same direction */
                        deltaX = (currentPos.x < previousPos.x) ? -deltaX : deltaX;
                    }
                    else
                    {
                        /* Move npc the opposite side than previous movement */
                        deltaX = (currentPos.x < previousPos.x) ? deltaX : -deltaX;
                    }
                }

                if (currentPos.y == (_BoardSizeInPixel.y - npcSize.y))
                {
                    /* Force moving up */
                    deltaY = -deltaY;
                }
                else if (currentPos.y != 0U)
                {
                    /* Check Y direction change probability */
                    if (changeDirProbaY < CHANGE_DIRECTION_THRESHOLD)
                    {
                        /* If npc has moved up, change sign to move in the same direction */
                        deltaY = (currentPos.y < previousPos.y) ? -deltaY : deltaY;
                    }
                    else
                    {
                        /* Move npc the opposite side than previous movement */
                        deltaY = (currentPos.y < previousPos.y) ? deltaY : -deltaY;
                    }
                }

                /* Update positions considering window bounds */
                if ((currentPos.x - absDeltaX) < 0.0f)
                {
                    currentPos.x = 0U;
                    deltaX       = absDeltaX;
                }
                else if ((currentPos.x + absDeltaX + npcSize.x) > _BoardSizeInPixel.x)
                {
                    currentPos.x = _BoardSizeInPixel.x - npcSize.x;
                    deltaX       = -absDeltaX;
                }

                if ((currentPos.y - absDeltaY) < 0.0f)
                {
                    currentPos.y = 0U;
                    deltaY       = absDeltaY;
                }
                else if (((currentPos.y + absDeltaY + npcSize.y) > _BoardSizeInPixel.y))
                {
                    currentPos.y = _BoardSizeInPixel.y - npcSize.y;
                    deltaY       = -absDeltaY;
                }

                currentPos.x += deltaX;
                currentPos.y += deltaY;

                npc->setPosition(currentPos);
            }
        }
    }
}

/**
 * @brief Handle interactions between player and NPCs
 *
 */
void Game::_HandleInteractions()
{
    if (_GameStatus == GameStatus::PLAY)
    {
        for (auto npc : *_NPCs)
        {
            if (_AreClose(*_Player, *npc, ConfigDev::tileSize) == true)
            {
                npc->attack(*_Player);
            }
        }

        if (_Player->isAlive() == false)
        {
            _GameStatus = GameStatus::STOP;
        }
    }
}

/**
 * @brief Indicate if player and NPC are close
 *
 * @param player Source of the distance
 * @param npc Npc to compute the distance with
 * @param threshold Threshold to determine of player and npc are close
 * @return true if they are close, else false
 *
 */
bool Game::_AreClose(const Player &player, const NPC &npc, const uint32_t threshold) const
{
    const Vector2f playerPos = player.getPosition();
    const Vector2f npcPos    = npc.getPosition();

    const Vector2u playerSize = player.getSize();
    const Vector2u npcSize    = npc.getSize();

    const float_t distanceX = abs(playerPos.x - npcPos.x) - (playerSize.x + npcSize.x) / 2.0f;
    const float_t distanceY = abs(playerPos.y - npcPos.y) - (playerSize.y + npcSize.y) / 2.0f;

    return ((distanceX < threshold) && (distanceY < threshold));
}

/**
 * @brief Main loop of the game on server side
 *
 */
void Game::play()
{
    _waitForPlayer();

    if (_GameStatus == GameStatus::READY)
    {
        cout << "Player connected and ready, starting game ..." << endl;
        _GameStatus = GameStatus::PLAY;
        _ServerNetwork->sendGameStatus(&_GameStatus);
    }

    while(_GameStatus == GameStatus::PLAY)
    {
        /* Receive events from client */
        _SynchronizeFromClient();

        /* Move player and NPCs */
        _MovePlayer();
        _MoveNPCs();

        /* Manage interactions between player and NPCs */
        _HandleInteractions();

        /* Send to client new outputs */
        _UpdateOutputCommands();
        _SynchronizeToClient();
    }
}