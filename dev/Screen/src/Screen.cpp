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
}

/**
 * @brief Draw the board on the screen
 *
 */
void Screen::_drawBoard()
{
    _Window.draw(_Board.getVertices(), &_TilesetTexture);
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
