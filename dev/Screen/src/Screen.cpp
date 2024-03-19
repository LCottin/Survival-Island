#include "Screen.hpp"
#include "ScreenPrv.hpp"
#include "ConfigDev.hpp"
#include "ConfigUser.hpp"
#include "Random.hpp"

Screen::Screen(const string &title)
{
    _TileSize    = Vector2u(ConfigDev::tileSize, ConfigDev::tileSize);
    _WindowTitle = title;

    if (_TilesetTexture.loadFromFile(ConfigDev::tilesetImgPath) == false)
    {
        throw runtime_error("Failed to load tileset image.");
    }

    _ScreenWidthInPixel  = ScreenSizeInTile::WIDTH  * _TileSize.x;
    _ScreenHeightInPixel = ScreenSizeInTile::HEIGHT * _TileSize.y;

    _Window.create(VideoMode(_ScreenWidthInPixel, _ScreenHeightInPixel), _WindowTitle, Style::Titlebar | Style::Close);
    _Window.setFramerateLimit(ConfigDev::framerateLimit);

    _BoardView = make_unique<GenericView>(BoardViewSizeInTile::WIDTH * _TileSize.x, BoardViewSizeInTile::HEIGHT * _TileSize.y, Vector2u(0U, 0U),                                                                             _Window, _TileSize.x);
    _Minimap   = make_unique<GenericView>(MinimapSizeInTile::WIDTH   * _TileSize.x, MinimapSizeInTile::HEIGHT   * _TileSize.y, Vector2u(BoardViewSizeInTile::WIDTH * _TileSize.x, InfoViewSizeInTile::HEIGHT * _TileSize.y), _Window, _TileSize.x, 10.0f);

    _InfoPanel = make_unique<InfoPanel>(InfoViewSizeInTile::WIDTH  * _TileSize.x, InfoViewSizeInTile::HEIGHT  * _TileSize.y, Vector2u(BoardViewSizeInTile::WIDTH * _TileSize.x, 0));

    _PauseTimer = seconds(0.5f);
    _PauseCooldown.restart();
}

/**
 * @brief Draw the board on the screen
 *
 * @param board Reference to the board
 */
void Screen::_drawBoard(const Board &board)
{
    _Window.draw(board.getVertices(), &_TilesetTexture);
}

/**
 * @brief Draw the player on the screen
 *
 * @param player Reference to the player
 */
void Screen::_drawPlayer(Player &player)
{
    Sprite& sprite = player.getSprite();

    /* Draw player on the screen only if alive, otherwise move sprite away */
    if (player.isAlive() == false)
    {
        sprite.setPosition(-1000.0f, -1000.0f);
    }

    _Window.draw(sprite);
}

/**
 * @brief Draw the NPCs on the screen
 *
 * @param NPClist Reference to the NPCs
 */
void Screen::_drawNPCs(const vector<shared_ptr<NPC>> &NPClist)
{
    for (auto &npc : NPClist)
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
 * @param player Reference to the player
 * @param NPClist Reference to the NPCs
 */
void Screen::_drawIndicators(Player &player, const vector<shared_ptr<NPC>> &NPClist)
{
    if (player.isAlive() == true)
    {
        player.updateHealthBar();
        _Window.draw(player.getHealthBar());
    }

    for (auto &npc : NPClist)
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
    _Window.draw(_InfoPanel->getShape());
    _Window.draw(_InfoPanel->getText());
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

/**
 * @brief Return image size
 *
 */
Vector2u Screen::getImageSize() const
{
    return Vector2u(ImageSizeInPixel::WIDTH, ImageSizeInPixel::HEIGHT);
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
 * @brief Draw all objects on the window
 *
 * @param board Constant reference to the board
 * @param player Reference to the player
 * @param NPClist Constant reference to the NPCs
 */
void Screen::drawAll(const Board &board, Player &player, const vector<shared_ptr<NPC>> &NPClist)
{
    _Window.clear();

    /* Draw elements for the main view (BoardView) */
    _BoardView->update(board, player);
    _Window.setView(_BoardView->getView());
    _drawBoard(board);
    _drawPlayer(player);
    _drawNPCs(NPClist);
    _drawIndicators(player, NPClist);

    /* Draw elements for the minimap view (Minimap) */
    _Minimap->update(board, player);
    _Window.setView(_Minimap->getView());
    _drawBoard(board);
    _drawPlayer(player);

    /* Reset view to default before drawing the information panel */
    _Window.setView(_Window.getDefaultView());
    _InfoPanel->update(player);
    _drawInfoPanel();

    _Window.display();
}

Screen::~Screen()
{
}
