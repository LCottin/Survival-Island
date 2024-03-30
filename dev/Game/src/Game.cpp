#include "Game.hpp"
#include "GamePrv.hpp"
#include "NPCPub.hpp"
#include "ConfigUser.hpp"
#include "ConfigDev.hpp"
#include "Random.hpp"

Game::Game(const string &playerName)
{
    _GameStatus = GameStatus::INIT;

    _Player = make_shared<Player>(playerName);
    _Board  = make_shared<Board>();
    _Screen = make_shared<Screen>(ConfigUser::windowTitle);
    _NPCs   = make_shared<vector<shared_ptr<NPC>>>(10U * static_cast<uint32_t>(ConfigUser::difficulty));

    for (size_t i = 0; i < _NPCs->size(); i++)
    {
        _NPCs->at(i) = make_shared<NPC>("NPC_" + to_string(i), NPCColorsString[Random::getRandomInteger(0, static_cast<uint32_t>(NPCColors::COUNT) - 1U)]);
    }

    _Board->computeVertices(ConfigDev::tileSize, _Screen->getImageSize());
    _BoardSizeInPixel  = Vector2u(_Board->getWidthInTile() * ConfigDev::tileSize, _Board->getHeightInTile() * ConfigDev::tileSize);
}

/**
 * @brief Reset structure to default values
 *
 * @param sharedEvent Reference to the structure of shared events
 */
void Game::_ResetSharedEvent(sharedEvents &sharedEvent)
{
    sharedEvent.isGamePaused    = (_GameStatus == GameStatus::PAUSE);
    sharedEvent.movePlayerDown  = false;
    sharedEvent.movePlayerUp    = false;
    sharedEvent.movePlayerLeft  = false;
    sharedEvent.movePlayerRight = false;
}

/**
 * @brief Main loop of the game
 *
 */
void Game::play()
{
    sharedEvents sharedEvent;
    _GameStatus = GameStatus::PLAY;

    while ((_Screen->isWindowOpen()) && (_GameStatus != GameStatus::STOP))
    {
        /* Catch events */
        _HandleEvents(sharedEvent);

        /* Move player and NPCs */
        _MovePlayer(sharedEvent);
        _MoveNPCs();

        /* Manage interactions between player and NPCs */
        _HandleInteractions();

        /* Refresh screen */
        _Draw();
    }
}

/**
 * @brief Move player after computing new position
 *
 * @param sharedEvent List of occurred events
 */
void Game::_MovePlayer(const sharedEvents &sharedEvent)
{
    if (_GameStatus == GameStatus::PLAY)
    {
        if (_Player->isAlive() == true)
        {
            const Vector2u playerSize     = _Player->getSize();
            const int32_t playerSpeed     = static_cast<int32_t>(_Player->getSpeed());
            Vector2f currentPos           = _Player->getPosition();
            bool updateFrame              = false;

            /* Move player left */
            if (sharedEvent.movePlayerLeft == true)
            {
                if ((currentPos.x - playerSpeed) >= 0)
                {
                    currentPos.x -= playerSpeed;
                    updateFrame   = true;
                }
                else
                {
                    /* Sprite out of bound, do not exceed window size */
                    currentPos.x = 0;
                    updateFrame  = false;
                }
            }

            /* Move player right */
            if (sharedEvent.movePlayerRight == true)
            {
                if ((currentPos.x + playerSpeed + playerSize.x) <= _BoardSizeInPixel.x)
                {
                    currentPos.x += playerSpeed;
                    updateFrame  |= true;
                }
                else
                {
                    /* Sprite out of bound, do not exceed window size */
                    currentPos.x  = _BoardSizeInPixel.x - playerSize.x;
                    updateFrame  |= false;
                }
            }

            /* Move player up */
            if (sharedEvent.movePlayerUp == true)
            {
                if ((currentPos.y - playerSpeed) >= 0)
                {
                    currentPos.y -= playerSpeed;
                    updateFrame  |= true;
                }
                else
                {
                    /* Sprite out of bound, do not exceed window size */
                    currentPos.y  = 0;
                    updateFrame  |= false;
                }
            }

            /* Move player down */
            if (sharedEvent.movePlayerDown == true)
            {
                if ((currentPos.y + playerSpeed + playerSize.y) <= _BoardSizeInPixel.y)
                {
                    currentPos.y += playerSpeed;
                    updateFrame  |= true;
                }
                else
                {
                    /* Sprite out of bound, do not exceed window size */
                    currentPos.y  = _BoardSizeInPixel.y - playerSize.y;
                    updateFrame  |= false;
                }
            }

            /* Update player final position */
            _Player->setPosition(currentPos, updateFrame);
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
 * @brief Handle event and user inputs
 *
 * @param sharedEvent Reference to the structure of shared events
 */
void Game::_HandleEvents(sharedEvents &sharedEvent)
{
    _ResetSharedEvent(sharedEvent);
    _Screen->handleAllEvents(sharedEvent);

    _GameStatus = (sharedEvent.isGamePaused == true) ? GameStatus::PAUSE : GameStatus::PLAY;
}

/**
 * @brief Draw all on the screen
 *
 */
void Game::_Draw()
{
    if (_GameStatus == GameStatus::PLAY)
    {
        _Screen->drawAll(*_Board, *_Player, *_NPCs);
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

Game::~Game()
{
}
