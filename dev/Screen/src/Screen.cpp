#include "Screen.hpp"

Screen::Screen(Board &board, Player &player, const string title) :
    _Board(board), _Player(player)
{
    _WindowTitle = title;
    _TileSize    = Vector2u(16U, 16U);

    if (_TilesetTexture.loadFromFile("../assets/images/tileset.png") == false)
    {
        cerr << "Error loading tileset" << endl;
        exit(EXIT_FAILURE);
    }

    _WidthPixel  = _Board.getWidthInTile() * _TileSize.x;
    _HeightPixel = _Board.getHeightInTile() * _TileSize.y;
    _SizePixel   = _WidthPixel * _HeightPixel;

    _Window.create(VideoMode(_WidthPixel, _HeightPixel), _WindowTitle);
    _Window.setFramerateLimit(10);

    _Vertices.setPrimitiveType(PrimitiveType::Quads);
    _computeVertices();

}

void Screen::_computeVertices()
{
    _Vertices.clear();
    _Vertices.resize(_Board.getSizeInTile() * 4);

    const uint32_t boardWidth  = _Board.getWidthInTile();
    const uint32_t boardHeight = _Board.getHeightInTile();

    for (size_t j = 0; j < boardHeight; j++)
    {
        for (size_t i = 0; i < boardWidth; i++)
        {
            int32_t tileIndex = _Board.getTile(i, j);

            if (tileIndex == -1)
            {
                cout << "index out of bound" << endl;
                continue;
            }

            // Calculate the position of the current tile in the vertex array
            float_t x = static_cast<float_t>(i * _TileSize.x);
            float_t y = static_cast<float_t>(j * _TileSize.y);

            // Get a pointer to the current tile quad
            Vertex* quad = &_Vertices[(i + j * boardWidth) * 4];

            // Define its 4 corners
            quad[0].position = Vector2f(x              , y);
            quad[1].position = Vector2f(x + _TileSize.x, y);
            quad[2].position = Vector2f(x + _TileSize.x, y + _TileSize.y);
            quad[3].position = Vector2f(x              , y + _TileSize.y);

            // Calculate coordinate of the index in the image
            float_t tile_x = static_cast<float_t>((tileIndex % (IMAGE_WIDTH_PIXEL / _TileSize.x)) * _TileSize.x);
            float_t tile_y = static_cast<float_t>((tileIndex / (IMAGE_WIDTH_PIXEL / _TileSize.y)) * _TileSize.y);

            // Define its 4 texture coordinates
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
    _Window.draw(_Player.getSprite());
}

/**
 * @brief Draw the NPCs on the screen after being moved randomly
 *
 */
void Screen::_drawNPCs()
{
    constexpr float_t changeDirThreshold = 0.6f;

    for (auto &npc : _NPCs)
    {
        float_t changeDirProbaX = Random::getRandomFloat(0.0f, 1.0f);
        float_t changeDirProbaY = Random::getRandomFloat(0.0f, 1.0f);
        float_t deltaX          = Random::getRandomInteger(0, 5);
        float_t deltaY          = Random::getRandomInteger(0, 5);
        float_t absDeltaX       = abs(deltaX);
        float_t absDeltaY       = abs(deltaY);

        Vector2f currentPos  = npc->getPosition();
        Vector2f previousPos = npc->getPreviousPosition();

        /* Compute new directions */
        if (currentPos.x == (static_cast<float_t>(_WidthPixel) - static_cast<float_t>(NPC_WIDTH) * npc->getScale().x))
        {
            /* Force moving left */
            deltaX = -deltaX;
        }
        else if (currentPos.x != 0)
        {
            /* Check X direction change probability */
            if (changeDirProbaX < changeDirThreshold)
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

        if (currentPos.y == (static_cast<float_t>(_HeightPixel) - static_cast<float_t>(NPC_HEIGHT) * npc->getScale().y))
        {
            /* Force moving up */
            deltaY = -deltaY;
        }
        else if (currentPos.y != 0)
        {
            /* Check Y direction change probability */
            if (changeDirProbaY < changeDirThreshold)
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
        if ((currentPos.x - absDeltaX) < 0)
        {
            currentPos.x = 0;
            deltaX       = absDeltaX;
        }
        else if ((currentPos.x + absDeltaX + NPC_WIDTH * npc->getScale().x) > _WidthPixel)
        {
            currentPos.x = static_cast<float_t>(_WidthPixel) - static_cast<float_t>(NPC_WIDTH) * npc->getScale().x;
            deltaX       = -absDeltaX;
        }

        if ((currentPos.y - absDeltaY) < 0)
        {
            currentPos.y = 0;
            deltaY       = absDeltaY;
        }
        else if (((currentPos.y + absDeltaY + NPC_HEIGHT * npc->getScale().y) > _HeightPixel))
        {
            currentPos.y = static_cast<float_t>(_HeightPixel) - static_cast<float_t>(NPC_HEIGHT) * npc->getScale().y;
            deltaY       = -absDeltaY;
        }

        currentPos.x += deltaX;
        currentPos.y += deltaY;

        npc->setPosition(currentPos);

        _Window.draw(npc->getSprite());
    }
}

/**
 * @brief Draw indicators on the screen
 *
 */
void Screen::_drawIndicators()
{
    _Player.updateHealthBar();
    _Window.draw(_Player.getHealthBar());
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

        /* Move player ... */
        if (event.type == Event::KeyPressed)
        {
            bool updateFrame;
            Vector2f currentPos = _Player.getPosition();

            /* ... left */
            if (Keyboard::isKeyPressed(Keyboard::Left))
            {
                if ((currentPos.x - 10.0f) >= 0)
                {
                    currentPos.x -= 10.0f;
                    updateFrame   = true;
                }
                else
                {
                    /* Sprite out of bound, do not exceed window size */
                    currentPos.x = 0.0f;
                    updateFrame  = false;
                }
            }

            /* ... right */
            if (Keyboard::isKeyPressed(Keyboard::Right))
            {
                if ((currentPos.x + 10.0f + PLAYER_WIDTH*_Player.getScale().x) <= _WidthPixel)
                {
                    currentPos.x += 10.0f;
                    updateFrame   = true;
                }
                else
                {
                    /* Sprite out of bound, do not exceed window size */
                    currentPos.x = static_cast<float_t>(_WidthPixel) - static_cast<float_t>(PLAYER_WIDTH) * _Player.getScale().x;
                    updateFrame  = false;
                }
            }

            /* ... up */
            if (Keyboard::isKeyPressed(Keyboard::Up))
            {
                if ((currentPos.y - 10.0f) >= 0)
                {
                    currentPos.y -= 10.0f;
                    updateFrame   = true;
                }
                else
                {
                    /* Sprite out of bound, do not exceed window size */
                    currentPos.y = 0.0f;
                    updateFrame  = false;
                }
            }

            /* ... down */
            if (Keyboard::isKeyPressed(Keyboard::Down))
            {
                if ((currentPos.y + 10.0f + PLAYER_HEIGHT*_Player.getScale().y) <= _HeightPixel)
                {
                    currentPos.y += 10.0f;
                    updateFrame   = true;
                }
                else
                {
                    /* Sprite out of bound, do not exceed window size */
                    currentPos.y = (float_t)_HeightPixel - (float_t)PLAYER_HEIGHT*_Player.getScale().y;
                    updateFrame  = false;
                }
            }

            _Player.setPosition(currentPos, updateFrame);
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
    return _WidthPixel;
}

/**
 * @brief Get the Screen Height in pixel object
 *
 * @return uint32_t The screen height in pixel
 */
uint32_t Screen::getHeightPixel() const
{
    return _HeightPixel;
}

/**
 * @brief Get the Screen Size in pixel object
 *
 * @return uint32_t The screen size in pixel
 */
uint32_t Screen::getSizePixel() const
{
    return _SizePixel;
}

/**
 * @brief Change the window title
 *
 * @param title The new window title
 */
void Screen::setWindowTitle(const string title)
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
    while (_Window.isOpen())
    {
        _HandleEvents();

        _Window.clear();
        _drawBoard();
        _drawPlayer();
        _drawNPCs();
        _drawIndicators();
        _Window.display();
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
    Vector2f newPosition;
    newPosition.x = (float_t)Random::getRandomInteger(0, _WidthPixel - NPC_WIDTH*NPC->getScale().x);
    newPosition.y = (float_t)Random::getRandomInteger(0, _HeightPixel - NPC_HEIGHT*NPC->getScale().y);

    NPC->setPosition(newPosition);
    _NPCs.push_back(NPC);
}

Screen::~Screen()
{
}
