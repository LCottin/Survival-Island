#include "Board.hpp"

Board::Board()
{
    _WidthInTile  = BOARD_WIDTH_TILE;
    _HeightInTile = BOARD_HEIGHT_TILE;
    _SizeInTile   = BOARD_SIZE_TILE;

    _Map.resize(_WidthInTile, vector<TileTypeBackground>(_HeightInTile));

    _initMap();
}

Board::~Board()
{
}

/**
 * @brief Fills the map with default values
 *
 */
void Board::_initMap()
{
    /* Fills map with water */
    for (uint32_t j = 0; j < _HeightInTile; j++)
    {
        for (uint32_t i = 0; i < _WidthInTile; i++)
        {
            _Map[i][j] = TileTypeBackground::WATER_FULL;
        }
    }

    /* Sets a region of grass */
   for (uint32_t j = 5; j < _HeightInTile - 5; j++)
    {
        for (uint32_t i = 5; i < _WidthInTile - 5; i++)
        {
            _Map[i][j] = TileTypeBackground::GRASS_FULL;
        }
    }
}

/**
 * @brief Get the tile object at the given position
 *
 * @param x Position on the X axis
 * @param y Position on the Y axis
 * @return int32_t The tile type at the given position or -1 if the position is out of the board
 */
int32_t Board::getTile(const uint32_t x, const uint32_t y) const
{
    if ((x >= _WidthInTile) || (y >= _HeightInTile))
    {
        return -1;
    }
    return static_cast<int32_t>(_Map[x][y]);
}

/**
 * @brief Get the Board Width in tile object
 *
 * @return uint32_t The board width in tile
 */
uint32_t Board::getWidthInTile() const
{
    return _WidthInTile;
}

/**
 * @brief Get the Board Height in tile object
 *
 * @return uint32_t The board height in tile
 */
uint32_t Board::getHeightInTile() const
{
    return _HeightInTile;
}

/**
 * @brief Get the Board Size in tile object
 *
 * @return uint32_t The board size in tile
 */
uint32_t Board::getSizeInTile() const
{
    return _SizeInTile;
}

/**
 * @brief Set the tile object at the given position
 *
 * @param x Position on the X axis
 * @param y Position on the Y axis
 * @param tile The tile type to set
 * @return true if the tile has been set, false otherwise
 */
bool Board::setTile(const uint32_t x, const uint32_t y, const TileTypeBackground tile)
{
    if ((x >= _WidthInTile) || (y >= _HeightInTile))
    {
        return false;
    }
    _Map[x][y] = tile;
    return true;
}

/**
 * @brief Fill the map with one value
 *
 * @param value Value to fill the map with
 * @return true if the map is correctly filled, else false (error in value)
 */
bool Board::fillMap(const TileTypeBackground value)
{
    if (value >= TileTypeBackground::TILE_COUNT)
    {
        return false;
    }

    for (uint32_t j = 0; j < _HeightInTile; j++)
    {
        for (uint32_t i = 0; i < _WidthInTile; i++)
        {
            _Map[i][j] = value;
        }
    }

    return true;
}
