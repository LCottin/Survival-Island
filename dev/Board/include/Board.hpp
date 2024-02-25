#ifndef __BOARD_HPP__
#define __BOARD_HPP__

#include <string>
#include <vector>
#include <SFML/System.hpp>

#include "TileType.hpp"

using namespace std;
using namespace sf;

class Board
{
    private:
        uint32_t _WidthInTile;
        uint32_t _HeightInTile;
        uint32_t _SizeInTile;

        vector<vector<TileTypeBackground>> _Map;

        void _initMap();

    public:
        Board();

        int32_t  getTile(const uint32_t x, const uint32_t y) const;
        uint32_t getWidthInTile() const;
        uint32_t getHeightInTile() const;
        uint32_t getSizeInTile() const;
        Vector2i getDimensionInTile() const;

        bool setTile(const uint32_t x, const uint32_t y, const TileTypeBackground tile);

        bool fillMap(const TileTypeBackground value);

        ~Board();
};

#endif //__BOARD_HPP__
