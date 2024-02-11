#include "WindowView.hpp"

template <typename T>
static inline constexpr T _min(T a, T b)
{
    return ((a < b) ? a : b);
}

template <typename T>
static inline constexpr T _max(T a, T b)
{
    return ((a < b) ? b : a);
}

WindowView::WindowView(Board &board, Player &player) :
    _Board(board), _Player(player)
{
    _WidthInTile  = VIEW_WIDTH_TILE;
    _HeightInTile = VIEW_HEIGHT_TILE;
    _SizeInTile   = VIEW_SIZE_TILE;
    _View         = View(FloatRect(Vector2f(0.0f, 0.0f), Vector2f(_WidthInTile * ConfigDev::tileSize, _HeightInTile * ConfigDev::tileSize)));
    update();
}

/**
 * @brief Update the view to focus on player when moving
 *
 */
void WindowView::update()
{
    const Vector2f playerPos = _Player.getPosition();
    const Vector2f boardSize = static_cast<const Vector2f>(_Board.getDimensionInTile());
    Vector2f newCenter       = playerPos;

    /* Calculate the half size of the view */
    const Vector2f halfViewSize = Vector2f(_WidthInTile * ConfigDev::tileSize / 2.0f, _HeightInTile * ConfigDev::tileSize / 2.0f);

    /* Do not exceed left side */
    if (playerPos.x <= halfViewSize.x)
    {
        newCenter.x = halfViewSize.x;
    }

    /* Do not exceed right side */
    else if (playerPos.x > (boardSize.x * ConfigDev::tileSize - halfViewSize.x + VIEW_PANEL_WIDTH_PIXEL))
    {
        newCenter.x = boardSize.x * ConfigDev::tileSize - halfViewSize.x + VIEW_PANEL_WIDTH_PIXEL;
    }

    /* Do not exceed top */
    if (playerPos.y <= halfViewSize.y)
    {
        newCenter.y = halfViewSize.y;
    }

    /* Do not exceed bottom */
    else if (playerPos.y > (boardSize.y * ConfigDev::tileSize - halfViewSize.y))
    {
        newCenter.y = boardSize.y * ConfigDev::tileSize - halfViewSize.y;
    }

    /* Update the view center */
    _View.setCenter(newCenter);
}


/**
 * @brief Return the current view
 *
 */
View& WindowView::getView()
{
    return _View;
}

/**
 * @brief Return the size of the view
 *
 * @return Vector2f of the size
 */
Vector2f WindowView::getViewSize() const
{
    return _View.getSize();
}

/**
 * @brief Return the width of the view in pixel
 *
 */
uint32_t WindowView::getWidthInTile() const
{
    return _WidthInTile;
}

/**
 * @brief Return the height of the view in pixel
 *
 */
uint32_t WindowView::getHeightInTile() const
{
    return _HeightInTile;
}

/**
 * @brief Return the size of the view in pixel
 *
 */
uint32_t WindowView::getSizeInTile() const
{
    return _SizeInTile;
}

/**
 * @brief Return the position of the view (from top left corner)
 *
 */
Vector2f WindowView::getPosition() const
{
    Vector2f viewPos = _View.getCenter();
    return Vector2f(viewPos.x - _WidthInTile * ConfigDev::tileSize / 2, viewPos.y - _HeightInTile * ConfigDev::tileSize / 2);
}

/**
 * @brief Return the position of the center of the view
 *
 */
Vector2f WindowView::getCenterPosition() const
{
    return _View.getCenter();
}

