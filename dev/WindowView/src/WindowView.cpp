#include "WindowView.hpp"

WindowView::WindowView(Board &board, Player &player) :
    _Board(board), _Player(player)
{
    _WidthInPixel  = VIEW_WIDTH_TILE  * ConfigDev::tileSize;
    _HeightInPixel = VIEW_HEIGHT_TILE * ConfigDev::tileSize;
    _SizeInPixel   = VIEW_SIZE_TILE   * ConfigDev::tileSize;
    _View         = View(FloatRect(Vector2f(0.0f, 0.0f), Vector2f(_WidthInPixel, _HeightInPixel)));
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
    const Vector2f halfViewSize = Vector2f(_WidthInPixel / 2.0f, _HeightInPixel / 2.0f);

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
uint32_t WindowView::getWidthInPixel() const
{
    return _WidthInPixel;
}

/**
 * @brief Return the height of the view in pixel
 *
 */
uint32_t WindowView::getHeightInPixel() const
{
    return _HeightInPixel;
}

/**
 * @brief Return the size of the view in pixel
 *
 */
uint32_t WindowView::getSizeInPixel() const
{
    return _SizeInPixel;
}

/**
 * @brief Return the position of the view (from top left corner)
 *
 */
Vector2f WindowView::getPosition() const
{
    Vector2f viewPos = _View.getCenter();
    return Vector2f(viewPos.x - _WidthInPixel / 2.0f, viewPos.y - _HeightInPixel / 2.0f);
}

/**
 * @brief Return the position of the center of the view
 *
 */
Vector2f WindowView::getCenterPosition() const
{
    return _View.getCenter();
}

