#ifndef __BOARD_HPP__
#define __BOARD_HPP__

#include <string>
#include <vector>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include "TileType.hpp"

using namespace std;
using namespace sf;

class Board
{
    private:
        uint32_t _WidthInTile;
        uint32_t _HeightInTile;

        vector<vector<TileTypeBackground>> _Map;

        VertexArray _Vertices;

        void _initMap();

    public:
        Board();

        int32_t      getTile(const uint32_t x, const uint32_t y) const;
        uint32_t     getWidthInTile() const;
        uint32_t     getHeightInTile() const;
        Vector2i     getDimensionInTile() const;
        const VertexArray &getVertices() const;

        void computeVertices(const uint32_t tileSize, const Vector2u &imageSizeInPixel);

        ~Board();
};

#endif //__BOARD_HPP__
