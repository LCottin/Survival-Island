#include "Screen.hpp"

Screen::Screen(Board &board, Player &player, const string &title) :
    _Board(board), _Player(player)
{
    _GameStatus  = GameStatus::INIT;
    _TileSize    = Vector2u(ConfigDev::tileSize, ConfigDev::tileSize);
    _WindowTitle = title;

    if (_TilesetTexture.loadFromFile(ConfigDev::tilesetImgPath) == false)
    {
        throw runtime_error("Failed to load tileset image.");
    }

    _BoardWidthPixel  = _Board.getWidthInTile() * _TileSize.x;
    _BoardHeightPixel = _Board.getHeightInTile() * _TileSize.y;
    _BoardSizePixel   = _BoardWidthPixel * _BoardHeightPixel;

    _View            = new WindowView(_Board, _Player);
    _ViewWidthPixel  = _View->getWidthInPixel() + VIEW_PANEL_WIDTH_PIXEL;
    _ViewHeightPixel = _View->getHeightInPixel();

    _PauseTimer = seconds(0.5f);
    _PauseCooldown.restart();

    _Window.create(VideoMode(_ViewWidthPixel, _ViewHeightPixel), _WindowTitle);
    _Window.setFramerateLimit(ConfigDev::framerateLimit);
    _Window.setView(_View->getView());

    _InfoPanel.setSize(Vector2f(VIEW_PANEL_WIDTH_PIXEL, _ViewHeightPixel));
    _InfoPanel.setFillColor(Color(220, 200, 180)); /* Light brown */

    if (_Font.loadFromFile("../assets/fonts/Italic_text.ttf") == false)
    {
        throw runtime_error("Failed to load text font.");
    }

    _PanelText.setFont(_Font);
    _PanelText.setCharacterSize(20U);
    _PanelText.setFillColor(Color(80, 60, 40)); /* Dark Brown */

    _Vertices.setPrimitiveType(PrimitiveType::Quads);
    _computeVertices();

    _GameStatus = GameStatus::PLAY;
}

void Screen::_computeVertices()
{
    _Vertices.clear();
    _Vertices.resize(_Board.getSizeInTile() * 4U);

    const uint32_t boardWidth  = _Board.getWidthInTile();
    const uint32_t boardHeight = _Board.getHeightInTile();

    for (size_t j = 0; j < boardHeight; j++)
    {
        for (size_t i = 0; i < boardWidth; i++)
        {
            const int32_t tileIndex = _Board.getTile(i, j);

            if (tileIndex == -1)
            {
                throw runtime_error("Index out of bound when computing vertices.");
            }

            /* Calculate the position of the current tile in the vertex array */
            const float_t x = static_cast<const float_t>(i * _TileSize.x);
            const float_t y = static_cast<const float_t>(j * _TileSize.y);

            /* Get a pointer to the current tile quad */
            Vertex* quad = &_Vertices[(i + j * boardWidth) * 4U];

            /* Define its 4 corners */
            quad[0].position = Vector2f(x              , y);
            quad[1].position = Vector2f(x + _TileSize.x, y);
            quad[2].position = Vector2f(x + _TileSize.x, y + _TileSize.y);
            quad[3].position = Vector2f(x              , y + _TileSize.y);

            /* Calculate coordinate of the index in the image */
            const float_t tile_x = static_cast<const float_t>((tileIndex % (IMAGE_WIDTH_PIXEL / _TileSize.x)) * _TileSize.x);
            const float_t tile_y = static_cast<const float_t>((tileIndex / (IMAGE_WIDTH_PIXEL / _TileSize.y)) * _TileSize.y);

            /* Define its 4 texture coordinates */
            quad[0].texCoords = Vector2f(tile_x              , tile_y);
            quad[1].texCoords = Vector2f(tile_x + _TileSize.x, tile_y);
            quad[2].texCoords = Vector2f(tile_x + _TileSize.x, tile_y + _TileSize.y);
            quad[3].texCoords = Vector2f(tile_x              , tile_y + _TileSize.y);
        }
    }
}

/**
 * @brief Draw the board on the screen
 *
 */
void Screen::_drawBoard()
{
    _Window.draw(_Vertices, &_TilesetTexture);
    _Window.draw(_Player.getSprite());
}

/**
 * @brief Draw the player on the screen
 *
 */
void Screen::_drawPlayer()
{
    Sprite& sprite = _Player.getSprite();

    /* Draw player on the screen only if alive, otherwise move sprite away */
    if (_Player.isAlive() == false)
    {
        sprite.setPosition(-1000.0f, -1000.0f);
    }

    _Window.draw(sprite);
}

/**
 * @brief Draw the NPCs on the screen after being moved randomly
 *
 */
void Screen::_drawNPCs()
{
    for (auto &npc : _NPCs)
    {
        const float_t changeDirProbaX = Random::getRandomFloat(0.0f, 1.0f);
        const float_t changeDirProbaY = Random::getRandomFloat(0.0f, 1.0f);
        float_t deltaX                = Random::getRandomInteger(0, npc->getSpeed());
        float_t deltaY                = Random::getRandomInteger(0, npc->getSpeed());
        const float_t absDeltaX       = abs(deltaX);
        const float_t absDeltaY       = abs(deltaY);

        Vector2u npcSize     = npc->getSize();
        Vector2u currentPos  = npc->getPosition();
        Vector2u previousPos = npc->getPreviousPosition();

        /* Compute new directions */
        if (currentPos.x == (_BoardWidthPixel - npcSize.x))
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

        if (currentPos.y == (_BoardHeightPixel - npcSize.y))
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
        else if ((currentPos.x + absDeltaX + npcSize.x) > _BoardWidthPixel)
        {
            currentPos.x = _BoardWidthPixel - npcSize.x;
            deltaX       = -absDeltaX;
        }

        if ((currentPos.y - absDeltaY) < 0.0f)
        {
            currentPos.y = 0U;
            deltaY       = absDeltaY;
        }
        else if (((currentPos.y + absDeltaY + npcSize.y) > _BoardHeightPixel))
        {
            currentPos.y = _BoardHeightPixel - npcSize.y;
            deltaY       = -absDeltaY;
        }

        currentPos.x += deltaX;
        currentPos.y += deltaY;

        npc->setPosition(currentPos);

        _HandleInteractions();

        /* Draw npc only if alive */
        if (npc->isAlive() == true)
        {
            _Window.draw(npc->getSprite());
        }
    }
}

/**
 * @brief Draw indicators on the screen
 *
 */
void Screen::_drawIndicators()
{
    if (_Player.isAlive() == true)
    {
        _Player.updateHealthBar();
        _Window.draw(_Player.getHealthBar());
    }

    for (auto &npc : _NPCs)
    {
        /* Draw health bar is relevant */
        if (npc->isAlive() == true)
        {
            npc->updateHealthBar();
            _Window.draw(npc->getHealthBar());
        }
    }
}

/**
 * @brief Draw information panel on the screen
 *
 */
void Screen::_drawInfoPanel()
{
    Vector2u viewPos     = _View->getPosition();
    String textToDisplay = "Player\nHealth:\n" + to_string(_Player.getHealth()) + "\n\n\n\n";
    textToDisplay       += "Difficulty:\n" + GameDifficultyString[static_cast<uint32_t>(ConfigUser::difficulty)];

    _InfoPanel.setPosition(viewPos.x + _View->getWidthInPixel() - VIEW_PANEL_WIDTH_PIXEL + 0U, viewPos.y);
    _PanelText.setPosition(viewPos.x + _View->getWidthInPixel() - VIEW_PANEL_WIDTH_PIXEL + 5U, viewPos.y);
    _PanelText.setString(textToDisplay);

    _Window.draw(_InfoPanel);
    _Window.draw(_PanelText);
}

/**
 * @brief Handle events on the screen
 *
 */
void Screen::_HandleEvents()
{
    Event event;
    while (_Window.pollEvent(event))
    {
        /* Close window */
        if (event.type == Event::Closed)
            _Window.close();

        /* Update pause status */
        if ((event.type == Event::KeyPressed) && (Keyboard::isKeyPressed(ConfigUser::pauseKey)))
        {
            if (_PauseCooldown.getElapsedTime() > _PauseTimer)
            {
                _GameStatus = (_GameStatus == GameStatus::PLAY) ? GameStatus::PAUSE: GameStatus::PLAY;
                _PauseCooldown.restart();
            }
        }

        /* Move player ... */
        if ((event.type == Event::KeyPressed) && (_GameStatus == GameStatus::PLAY))
        {
            if (_Player.isAlive() == true)
            {
                const Vector2u playerSize = _Player.getSize();
                const int32_t playerSpeed = static_cast<int32_t>(_Player.getSpeed());
                Vector2i currentPos       = static_cast<Vector2i>(_Player.getPosition());
                bool updateFrame          = false;

                /* ... left */
                if (Keyboard::isKeyPressed(ConfigUser::leftKey))
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

                /* ... right */
                if (Keyboard::isKeyPressed(ConfigUser::rightKey))
                {
                    if ((currentPos.x + playerSpeed + playerSize.x) <= _BoardWidthPixel)
                    {
                        currentPos.x += playerSpeed;
                        updateFrame  |= true;
                    }
                    else
                    {
                        /* Sprite out of bound, do not exceed window size */
                        currentPos.x  = _BoardWidthPixel - playerSize.x;
                        updateFrame  |= false;
                    }
                }

                /* ... up */
                if (Keyboard::isKeyPressed(ConfigUser::upKey))
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

                /* ... down */
                if (Keyboard::isKeyPressed(ConfigUser::downKey))
                {
                    if ((currentPos.y + playerSpeed + playerSize.y) <= _BoardHeightPixel)
                    {
                        currentPos.y += playerSpeed;
                        updateFrame  |= true;
                    }
                    else
                    {
                        /* Sprite out of bound, do not exceed window size */
                        currentPos.y  = _BoardHeightPixel - playerSize.y;
                        updateFrame  |= false;
                    }
                }

                _Player.setPosition(static_cast<Vector2u>(currentPos), updateFrame);
                _View->update();
            }
            else
            {
                _GameStatus = GameStatus::STOP;
            }
        }
    }
}

/**
 * @brief Handle player and npcs interactions
 *
 */
void Screen::_HandleInteractions()
{
    for (auto &npc : _NPCs)
    {
        if (areClose(_Player, *npc, _TileSize.x) == true)
        {
            npc->attack(_Player);
        }
    }
}

/**
 * @brief Get the Screen Width in pixel object
 *
 * @return uint32_t The screen width in pixel
 */
uint32_t Screen::getWidthPixel() const
{
    return _BoardWidthPixel;
}

/**
 * @brief Get the Screen Height in pixel object
 *
 * @return uint32_t The screen height in pixel
 */
uint32_t Screen::getHeightPixel() const
{
    return _BoardHeightPixel;
}

/**
 * @brief Get the Screen Size in pixel object
 *
 * @return uint32_t The screen size in pixel
 */
uint32_t Screen::getSizePixel() const
{
    return _BoardSizePixel;
}

/**
 * @brief Change the window title
 *
 * @param title The new window title
 */
void Screen::setWindowTitle(const string &title)
{
    _WindowTitle = title;
    _Window.setTitle(_WindowTitle);
}

/**
 * @brief Change the board to display
 *
 * @param board The new board to display
 */
void Screen::setBoard(Board &board)
{
    _Board = board;
    _computeVertices();
}

/**
 * @brief Render the board on the screen
 *
 */
void Screen::render()
{
    while ((_Window.isOpen()) && (_GameStatus != GameStatus::STOP))
    {
        _HandleEvents();

        if (_GameStatus == GameStatus::PLAY)
        {
            _Window.clear();
            _Window.setView(_View->getView());
            _drawBoard();
            _drawPlayer();
            _drawNPCs();
            _drawIndicators();
            _drawInfoPanel();
           _Window.display();
        }
    }
}

/**
 * @brief Add a new NPC to the game
 *
 * @param &NPC Reference to the new NPC
 *
 */
void Screen::addNPC(shared_ptr<NPC> &NPC)
{
    Vector2u newPosition;
    newPosition.x = Random::getRandomInteger(0, _BoardWidthPixel - NPC->getSize().x);
    newPosition.y = Random::getRandomInteger(0, _BoardHeightPixel - NPC->getSize().y);

    NPC->setPosition(newPosition);
    _NPCs.push_back(NPC);
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
bool Screen::areClose(const Player &player, const NPC &npc, const uint32_t threshold) const
{
    const Vector2u playerPos = player.getPosition();
    const Vector2u npcPos    = npc.getPosition();

    const Vector2u playerSize = player.getSize();
    const Vector2u npcSize    = npc.getSize();

    const float_t distanceX = abs(static_cast<float_t>(playerPos.x - npcPos.x)) - (playerSize.x + npcSize.x) / 2.0f;
    const float_t distanceY = abs(static_cast<float_t>(playerPos.y - npcPos.y)) - (playerSize.y + npcSize.y) / 2.0f;

    return ((distanceX < threshold) && (distanceY < threshold));
}

Screen::~Screen()
{
    delete _View;
}
