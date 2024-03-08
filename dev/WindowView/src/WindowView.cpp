#include "WindowView.hpp"
#include "WindowViewPub.hpp"
#include "ConfigDev.hpp"

WindowView::WindowView()
{
    _WidthInPixel  = ViewSizeInTile::WIDTH  * ConfigDev::tileSize;
    _HeightInPixel = ViewSizeInTile::HEIGHT * ConfigDev::tileSize;
    _View          = View(FloatRect(Vector2f(0.0f, 0.0f), Vector2f(_WidthInPixel, _HeightInPixel)));
}

/**
 * @brief Update the view to focus on player when moving
 *
 * @param board Reference to the board
 * @param player Reference to the player
 */
void WindowView::update(const Board &board, const Player &player)
{
    const Vector2u playerPos = player.getPosition();
    const Vector2u boardSize = static_cast<const Vector2u>(board.getDimensionInTile());
    Vector2u newCenter       = playerPos;

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
    _View.setCenter(static_cast<Vector2f>(newCenter));
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
 * @brief Return the position of the view (from top left corner)
 *
 */
Vector2u WindowView::getPosition() const
{
    Vector2f viewPos = _View.getCenter();
    return Vector2u(viewPos.x - _WidthInPixel / 2U, viewPos.y - _HeightInPixel / 2U);
}

/**
 * @brief Return the position of the center of the view
 *
 */
Vector2u WindowView::getCenterPosition() const
{
    return static_cast<Vector2u>(_View.getCenter());
}

