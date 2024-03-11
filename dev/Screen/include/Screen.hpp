#ifndef __SCREEN_HPP__
#define __SCREEN_HPP__

#include <string>
#include <SFML/Graphics.hpp>

#include "Board.hpp"
#include "Player.hpp"
#include "NPC.hpp"
#include "GamePub.hpp"
#include "BoardView.hpp"
#include "InfoPanel.hpp"

using namespace std;
using namespace sf;

class Screen
{
    private:
        RenderWindow             _Window;
        Vector2u                 _TileSize;
        Texture                  _TilesetTexture;

        uint32_t                 _ScreenWidthInPixel;
        uint32_t                 _ScreenHeightInPixel;

        string                   _WindowTitle;

        unique_ptr<BoardView>  _BoardView;
        unique_ptr<InfoPanel>  _InfoPanel;

        Clock _PauseCooldown;
        Time  _PauseTimer;

        void _computeVertices();
        void _drawBoard(const Board &board);
        void _drawPlayer(Player &player);
        void _drawNPCs(const vector<shared_ptr<NPC>> &NPClist);
        void _drawIndicators(Player &player, const vector<shared_ptr<NPC>> &NPClist);
        void _drawInfoPanel();

    public:
        Screen(const string &title);

        Vector2u getImageSize()   const;
        bool     isWindowOpen()   const;

        void handleAllEvents(sharedEvents &sharedEvent);
        void drawAll(const Board &board, Player &player, const vector<shared_ptr<NPC>> &NPClist);

        ~Screen();
};

#endif
