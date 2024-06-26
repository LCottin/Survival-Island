#include "Board.hpp"
#include "BoardPub.hpp"
#include "FastNoiseLite.hpp"
#include "Random.hpp"

Board::Board()
{
    _WidthInTile  = BoardSizeInTile::WIDTH;
    _HeightInTile = BoardSizeInTile::HEIGHT;

    _Map.resize(_WidthInTile, vector<TileTypeBackground>(_HeightInTile));
    _Vertices.setPrimitiveType(PrimitiveType::Quads);

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
            const bool isTopBorder    = (j == 0);
            const bool isBottomBorder = (j == (_HeightInTile - 1U));
            const bool isLeftBorder   = (i == 0);
            const bool isRightBorder  = (i == (_WidthInTile - 1U));

            /* Set the appropriate wall tile for the borders */
            if (isTopBorder || isBottomBorder || isLeftBorder || isRightBorder)
            {
                const float_t borderValue = noise.GetNoise(static_cast<float_t>(i) * 0.1f, static_cast<float_t>(j) * 0.1f);

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
                const float_t value = noise.GetNoise(static_cast<float_t>(i), static_cast<float_t>(j));

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
 * @brief Computes board vertices
 *
 */
void Board::computeVertices(const uint32_t tileSize, const Vector2u &imageSizeInPixel)
{
    _Vertices.clear();
    _Vertices.resize(_WidthInTile * _HeightInTile * 4U);

    for (size_t j = 0; j < _WidthInTile; j++)
    {
        for (size_t i = 0; i < _HeightInTile; i++)
        {
            const uint32_t tileIndex = static_cast<uint32_t>(_Map[i][j]);

            /* Calculate the position of the current tile in the vertex array */
            const float_t x = static_cast<float_t>(i * tileSize);
            const float_t y = static_cast<float_t>(j * tileSize);

            /* Get a pointer to the current tile quad */
            Vertex* quad = &_Vertices[(i + j * _WidthInTile) * 4U];

            /* Define its 4 corners */
            quad[0].position = Vector2f(x           , y);
            quad[1].position = Vector2f(x + tileSize, y);
            quad[2].position = Vector2f(x + tileSize, y + tileSize);
            quad[3].position = Vector2f(x           , y + tileSize);

            /* Calculate coordinate of the index in the image */
            const float_t tile_x = static_cast<float_t>((tileIndex % (imageSizeInPixel.x / tileSize)) * tileSize);
            const float_t tile_y = static_cast<float_t>((tileIndex / (imageSizeInPixel.y / tileSize)) * tileSize);

            /* Define its 4 texture coordinates */
            quad[0].texCoords = Vector2f(tile_x           , tile_y);
            quad[1].texCoords = Vector2f(tile_x + tileSize, tile_y);
            quad[2].texCoords = Vector2f(tile_x + tileSize, tile_y + tileSize);
            quad[3].texCoords = Vector2f(tile_x           , tile_y + tileSize);
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
 * @brief Get the Board dimension in tile object
 *
 * @return Vector2i The board dimension in tile
 */
Vector2i Board::getDimensionInTile() const
{
    return Vector2i(_WidthInTile, _HeightInTile);
}

/**
 * @brief Gives a reference to the board vertices
 *
 */
const VertexArray& Board::getVertices() const
{
    return _Vertices;
}
