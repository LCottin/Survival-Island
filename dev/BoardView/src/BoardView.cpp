#include "BoardView.hpp"
#include "ConfigDev.hpp"

BoardView::BoardView(const uint32_t widthInPixel, const uint32_t heightInPixel, const uint32_t limitOffsetInPixel, const Vector2u &position)
{
    _WidthInPixel       = widthInPixel;
    _HeightInPixel      = heightInPixel;
    _LimitOffsetInPixel = limitOffsetInPixel;
    _Position           = position;

    _View = View(FloatRect(static_cast<Vector2f>(_Position), Vector2f(_WidthInPixel, _HeightInPixel)));
}

/**
 * @brief Return the current view
 *
 * @return const View& Constant reference to the view
 */
const View& BoardView::getView() const
{
    return _View;
}

/**
 * @brief Return the width of the view in pixel
 *
 */
uint32_t BoardView::getWidthInPixel() const
{
    return _WidthInPixel;
}

/**
 * @brief Return the height of the view in pixel
 *
 */
uint32_t BoardView::getHeightInPixel() const
{
    return _HeightInPixel;
}

/**
 * @brief Update the view to focus on player when moving
 *
 * @param board Constant reference to the board
 * @param player Constant reference to the player
 */
void BoardView::update(const Board &board, const Player &player)
{
    const Vector2u playerPos = player.getPosition();
    const Vector2u boardSize = static_cast<const Vector2u>(board.getDimensionInTile());
    Vector2f newCenter       = static_cast<Vector2f>(playerPos);

    /* Calculate the half size of the view */
    const Vector2f halfViewSize = Vector2f(_WidthInPixel / 2.0f, _HeightInPixel / 2.0f);

    /* Do not exceed left side */
    if (playerPos.x <= halfViewSize.x)
    {
        newCenter.x = halfViewSize.x;
    }

    /* Do not exceed right side */
    else if (playerPos.x >= ((boardSize.x - 1U) * ConfigDev::tileSize - halfViewSize.x + _LimitOffsetInPixel))
    {
        newCenter.x = (boardSize.x - 1U) * ConfigDev::tileSize - halfViewSize.x + _LimitOffsetInPixel;
    }

    /* Do not exceed top */
    if (playerPos.y <= halfViewSize.y)
    {
        newCenter.y = halfViewSize.y;
    }

    /* Do not exceed bottom */
    else if (playerPos.y >= (boardSize.y * ConfigDev::tileSize - halfViewSize.y))
    {
        newCenter.y = boardSize.y * ConfigDev::tileSize - halfViewSize.y;
    }

    /* Update the view center */
    _View.setCenter(newCenter);
}
