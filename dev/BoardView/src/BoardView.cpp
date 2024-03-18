#include "BoardView.hpp"
#include "ConfigDev.hpp"

BoardView::BoardView(const uint32_t widthInPixel, const uint32_t heightInPixel, const uint32_t limitOffsetInPixel, const Vector2u &position, const RenderWindow &window)
{
    _WidthInPixel       = widthInPixel;
    _HeightInPixel      = heightInPixel;
    _LimitOffsetInPixel = limitOffsetInPixel;
    _Position           = position;

    /* Get the default view of the window */
    View defaultView = window.getDefaultView();

    /* Set the center of the BoardView to the center of the  default view */
    _View.setCenter(defaultView.getCenter());

    /* Set the size of the BoardView */
    _View.setSize(static_cast<float>(_WidthInPixel), static_cast<float>(_HeightInPixel));

    /* Calculate the viewport parameters */
    const float_t viewportLeft   = static_cast<float_t>(_Position.x)    / window.getSize().x;
    const float_t viewportTop    = static_cast<float_t>(_Position.y)    / window.getSize().y;
    const float_t viewportWidth  = static_cast<float_t>(_WidthInPixel)  / window.getSize().x;
    const float_t viewportHeight = static_cast<float_t>(_HeightInPixel) / window.getSize().y;

    /* Set the viewport of the BoardView */
    _View.setViewport(FloatRect(viewportLeft, viewportTop, viewportWidth, viewportHeight));
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
