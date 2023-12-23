#ifndef __BOARD_HPP__
#define __BOARD_HPP__

#include <iostream>
#include <string>
#include <vector>

#include "BoardData.hpp"
#include "TileType.hpp"

using namespace std;

class Board
{
    private:
        uint32_t _WidthInTile;
        uint32_t _HeightInTile;
        uint32_t _SizeInTile;

        vector<vector<uint32_t>> _Map;

        void _initMap();

    public:
        Board();

        int32_t  getTile(const uint32_t x, const uint32_t y) const;
        uint32_t getWidthInTile() const;
        uint32_t getHeightInTile() const;
        uint32_t getSizeInTile() const;

        bool setTile(const uint32_t x, const uint32_t y, const uint32_t tile);

        bool fillMap(const uint32_t value);

        ~Board();
};

#endif // __BOARD_HPP__
