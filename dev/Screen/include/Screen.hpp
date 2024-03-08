#ifndef __SCREEN_HPP__
#define __SCREEN_HPP__

#include <string>
#include <SFML/Graphics.hpp>

#include "Board.hpp"
#include "Player.hpp"
#include "NPC.hpp"
#include "WindowView.hpp"
#include "GamePub.hpp"

using namespace std;
using namespace sf;

class Screen
{
    private:
        RenderWindow             _Window;
        Vector2u                 _TileSize;
        Texture                  _TilesetTexture;
        VertexArray              _Vertices;

        uint32_t                 _BoardWidthPixel;
        uint32_t                 _BoardHeightPixel;
        uint32_t                 _BoardSizePixel;
        uint32_t                 _ViewWidthPixel;
        uint32_t                 _ViewHeightPixel;

        string                   _WindowTitle;

        RectangleShape           _InfoPanel;
        Font                     _Font;
        Text                     _PanelText;

        unique_ptr<WindowView>   _View;

        Clock _PauseCooldown;
        Time  _PauseTimer;

        void _computeVertices();
        void _drawBoard(const Board &board);
        void _drawPlayer(Player &player);
        void _drawNPCs(const vector<shared_ptr<NPC>> &NPClist);
        void _drawIndicators(Player &player, const vector<shared_ptr<NPC>> &NPClist);
        void _drawInfoPanel(const Player &player);

    public:
        Screen(const string &title);

        Vector2u getImageSize()   const;
        bool     isWindowOpen()   const;

        void setWindowTitle(const string &title);

        void handleAllEvents(sharedEvents &sharedEvent);
        void drawAll(const Board &board, Player &player, const vector<shared_ptr<NPC>> &NPClist);

        ~Screen();
};

#endif
