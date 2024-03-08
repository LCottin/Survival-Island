#include "Screen.hpp"
#include "ScreenPrv.hpp"
#include "ConfigDev.hpp"
#include "ConfigUser.hpp"
#include "Random.hpp"
#include "WindowViewPub.hpp"

Screen::Screen(Board &board, Player &player, vector<shared_ptr<NPC>> &NPClist, const string &title) :
    _Board(board), _Player(player), _NPCs(NPClist)
{
    _TileSize    = Vector2u(ConfigDev::tileSize, ConfigDev::tileSize);
    _WindowTitle = title;

    if (_TilesetTexture.loadFromFile(ConfigDev::tilesetImgPath) == false)
    {
        throw runtime_error("Failed to load tileset image.");
    }

    _BoardWidthPixel  = _Board.getWidthInTile() * _TileSize.x;
    _BoardHeightPixel = _Board.getHeightInTile() * _TileSize.y;
    _BoardSizePixel   = _BoardWidthPixel * _BoardHeightPixel;

    _View            = make_unique<WindowView>(_Board, _Player);
    _ViewWidthPixel  = _View->getWidthInPixel() + VIEW_PANEL_WIDTH_PIXEL;
    _ViewHeightPixel = _View->getHeightInPixel();

    _PauseTimer = seconds(0.5f);
    _PauseCooldown.restart();

    _Window.create(VideoMode(_ViewWidthPixel, _ViewHeightPixel), _WindowTitle, Style::Titlebar | Style::Close);
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
            const float_t tile_x = static_cast<const float_t>((tileIndex % (ImageSizeInPixel::WIDTH / _TileSize.x)) * _TileSize.x);
            const float_t tile_y = static_cast<const float_t>((tileIndex / (ImageSizeInPixel::HEIGHT / _TileSize.y)) * _TileSize.y);

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
 * @brief Draw the NPCs on the screen
 *
 */
void Screen::_drawNPCs()
{
    for (auto &npc : _NPCs)
    {
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
 * @brief Handle all events on the screen
 *
 * @param sharedEvent Reference to the structure
 */
void Screen::handleAllEvents(sharedEvents &sharedEvent)
{
    Event event;
    while (_Window.pollEvent(event))
    {
        /* Close window */
        if (event.type == Event::Closed)
        {
            _Window.close();
        }

        /* Update pause status */
        if ((event.type == Event::KeyPressed) && (Keyboard::isKeyPressed(ConfigUser::pauseKey)))
        {
            if (_PauseCooldown.getElapsedTime() > _PauseTimer)
            {
                sharedEvent.isGamePaused = !sharedEvent.isGamePaused;
                _PauseCooldown.restart();
            }
        }

        /* Move player ... */
        if (event.type == Event::KeyPressed)
        {
            if (_Player.isAlive() == true)
            {
                /* ... left */
                if (Keyboard::isKeyPressed(ConfigUser::leftKey))
                {
                    sharedEvent.movePlayerLeft = true;
                }

                /* ... right */
                if (Keyboard::isKeyPressed(ConfigUser::rightKey))
                {
                    sharedEvent.movePlayerRight = true;
                }

                /* ... up */
                if (Keyboard::isKeyPressed(ConfigUser::upKey))
                {
                    sharedEvent.movePlayerUp = true;
                }

                /* ... down */
                if (Keyboard::isKeyPressed(ConfigUser::downKey))
                {
                    sharedEvent.movePlayerDown = true;
                }
            }
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
 * @brief Indicates if the window has been close
 *
 * @return true if the window is opened, false otherwise
 */
bool Screen::isWindowOpen() const
{
    return _Window.isOpen();
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
 * @brief Draw all objects on the window
 *
 */
void Screen::drawAll()
{
    _Window.clear();
    _View->update();
    _Window.setView(_View->getView());
    _drawBoard();
    _drawPlayer();
    _drawNPCs();
    _drawIndicators();
    _drawInfoPanel();
    _Window.display();
}

Screen::~Screen()
{
}
