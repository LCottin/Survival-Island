#include "Board.hpp"

Board::Board()
{
    _BoardWidthTile  = BOARD_WIDTH_TILE;
    _BoardHeightTile = BOARD_HEIGHT_TILE;
    _BoardSizeTile   = BOARD_SIZE_TILE;

    _Map = new uint32_t*[_BoardHeightTile];
    for (uint32_t i = 0; i < _BoardHeightTile; ++i)
    {
        _Map[i] = new uint32_t[_BoardWidthTile];
    }

    _initMap();
}

Board::~Board()
{
    for (uint32_t i = 0; i < _BoardHeightTile; i++)
    {
        delete[] _Map[i];
    }
    delete[] _Map;
}

void Board::_initMap()
{
    memset(_Map, TILE_TYPE_WATER_FULL, _BoardSizeTile * sizeof(uint32_t));
}

/**
 * @brief Get the Tile object at the given position
 *
 * @param x Position on the X axis
 * @param y Position on the Y axis
 * @return int32_t The tile type at the given position or -1 if the position is out of the board
 */
int32_t Board::getTile(const uint32_t x, const uint32_t y) const
{
    if (x >= _BoardWidthTile || y >= _BoardHeightTile)
    {
        return -1;
    }
    return _Map[y][x];
}

/**
 * @brief Set the Tile object at the given position
 *
 * @param x Position on the X axis
 * @param y Position on the Y axis
 * @param tile The tile type to set
 * @return true if the tile has been set, false otherwise
 */
bool Board::setTile(const uint32_t x, const uint32_t y, const uint32_t tile)
{
    if (x >= _BoardWidthTile || y >= _BoardHeightTile)
    {
        return false;
    }
    _Map[y][x] = tile;
    return true;
}
