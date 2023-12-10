#ifndef __BOARD_HPP__
#define __BOARD_HPP__

#include <iostream>
#include <string>

#include "BoardData.hpp"
#include "TileType.hpp"

using namespace std;

class Board
{
    private:
        uint32_t _BoardWidthTile;
        uint32_t _BoardHeightTile;
        uint32_t _BoardSizeTile;

        uint32_t **_Map;

        void _initMap();

    public:
        Board();

        int32_t getTile(const uint32_t x, const uint32_t y) const;

        bool setTile(const uint32_t x, const uint32_t y, const uint32_t tile);

        ~Board();
};

#endif // __BOARD_HPP__
