#ifndef __BOARD_HPP__
#define __BOARD_HPP__

#include <iostream>
#include <string>
#include <vector>

#include "BoardData.hpp"
#include "TileType.hpp"
#include "FastNoiseLite.hpp"
#include "Random.hpp"

using namespace std;

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

        bool setTile(const uint32_t x, const uint32_t y, const TileTypeBackground tile);

        bool fillMap(const TileTypeBackground value);

        ~Board();
};

#endif //__BOARD_HPP__
