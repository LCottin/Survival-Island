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
 * @brief Fills the map using Perlin noise
 *
 */
void Board::_initMap()
{
    FastNoiseLite noise;

    /* Configure the noise parameters */
    noise.SetNoiseType(FastNoiseLite::NoiseType_Perlin);
    noise.SetFrequency(0.05f);
    noise.SetSeed(Random::getRandomInteger(0, 1000));

    /* Generate terrain based on Perlin noise */
    for (size_t j = 0; j < _HeightInTile; j++)
    {
        for (size_t i = 0; i < _WidthInTile; i++)
        {
            /* Check if the current position is on the border */
            bool isTopBorder    = (j == 0);
            bool isBottomBorder = (j == (_HeightInTile - 1U));
            bool isLeftBorder   = (i == 0);
            bool isRightBorder  = (i == (_WidthInTile - 1U));

            /* Set the appropriate wall tile for the borders */
            if (isTopBorder || isBottomBorder || isLeftBorder || isRightBorder)
            {
                float_t borderValue = noise.GetNoise(static_cast<float_t>(i) * 0.1f, static_cast<float_t>(j) * 0.1f);

                /* Add some variation to the corners */
                if (isTopBorder && isLeftBorder)
                    _Map[i][j] = (borderValue < -0.3f) ? TileTypeBackground::WATER_WALL_UP_LEFT : TileTypeBackground::WATER_FULL;
                else if (isTopBorder && isRightBorder)
                    _Map[i][j] = (borderValue < -0.3f) ? TileTypeBackground::WATER_WALL_UP_RIGHT : TileTypeBackground::WATER_FULL;
                else if (isBottomBorder && isLeftBorder)
                    _Map[i][j] = (borderValue < -0.3f) ? TileTypeBackground::WATER_WALL_BOTTOM_LEFT : TileTypeBackground::WATER_FULL;
                else if (isBottomBorder && isRightBorder)
                    _Map[i][j] = (borderValue < -0.3f) ? TileTypeBackground::WATER_WALL_BOTTOM_RIGHT : TileTypeBackground::WATER_FULL;
                /* Add some variation to the edges */
                else if (isTopBorder)
                    _Map[i][j] = (borderValue < -0.3f) ? TileTypeBackground::WATER_WALL_UP : TileTypeBackground::WATER_FULL;
                else if (isBottomBorder)
                    _Map[i][j] = (borderValue < -0.3f) ? TileTypeBackground::WATER_WALL_DOWN : TileTypeBackground::WATER_FULL;
                else if (isLeftBorder)
                    _Map[i][j] = (borderValue < -0.3f) ? TileTypeBackground::WATER_WALL_LEFT : TileTypeBackground::WATER_FULL;
                else if (isRightBorder)
                    _Map[i][j] = (borderValue < -0.3f) ? TileTypeBackground::WATER_WALL_RIGHT : TileTypeBackground::WATER_FULL;
            }
            else
            {
                /* Interior tiles */
                float_t value = noise.GetNoise(static_cast<float_t>(i), static_cast<float_t>(j));

                if (value < -0.2f)
                {
                    /* Water */
                    if (value < -0.5f)
                        _Map[i][j] = TileTypeBackground::WATER_FULL;
                    else if (value < -0.3f)
                        _Map[i][j] = TileTypeBackground::WATER_WALL_BOTTOM_RIGHT;
                    else
                        _Map[i][j] = TileTypeBackground::WATER_WALL_BOTTOM_LEFT_RIGHT;
                }
                else if (value < 0.6f)
                {
                    /* Grass */
                    if (value < 0.2f)
                        _Map[i][j] = TileTypeBackground::GRASS_FULL;
                    else if (value < 0.3f)
                        _Map[i][j] = TileTypeBackground::GRASS_WALL_BOTTOM_RIGHT;
                    else if (value < 0.4f)
                        _Map[i][j] = TileTypeBackground::GRASS_WALL_BOTTOM_LEFT;
                    else if (value < 0.5f)
                        _Map[i][j] = TileTypeBackground::GRASS_WALL_TOP_RIGHT;
                    else
                        _Map[i][j] = TileTypeBackground::GRASS_WALL_TOP_LEFT_BOTTOM_RIGHT;
                }
                else
                {
                    /* Default to snow */
                    _Map[i][j] = TileTypeBackground::SNOW_FULL;
                }
            }
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
 * @brief Get the Board dimension in tile object
 *
 * @return Vector2i The board dimension in tile
 */
Vector2i Board::getDimensionInTile() const
{
    return Vector2i(_WidthInTile, _HeightInTile);
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
