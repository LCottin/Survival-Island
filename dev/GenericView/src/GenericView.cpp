#include "GenericView.hpp"
#include "ConfigDev.hpp"

GenericView::GenericView(const uint32_t widthInPixel, const uint32_t heightInPixel, const Vector2u &position, const RenderWindow &window, const uint32_t limitOffsetInPixel, const float_t zoomFactor)
{
    _WidthInPixel       = widthInPixel;
    _HeightInPixel      = heightInPixel;
    _Position           = position;
    _LimitOffsetInPixel = limitOffsetInPixel;

    /* Set the size of the Minimap view */
    _View.setSize(static_cast<float>(_WidthInPixel), static_cast<float>(_HeightInPixel));

    /* Calculate the viewport parameters */
    const float_t viewportLeft   = static_cast<float_t>(_Position.x)    / window.getSize().x;
    const float_t viewportTop    = static_cast<float_t>(_Position.y)    / window.getSize().y;
    const float_t viewportWidth  = static_cast<float_t>(_WidthInPixel)  / window.getSize().x;
    const float_t viewportHeight = static_cast<float_t>(_HeightInPixel) / window.getSize().y;

    /* Set the viewport of the Minimap view */
    _View.setViewport(FloatRect(viewportLeft, viewportTop, viewportWidth, viewportHeight));

    /* Zoom the Minimap view */
    _View.zoom(zoomFactor);

    /* Set the center of the BoardView to the center of the  default view */
    _View.setCenter(window.getDefaultView().getCenter());
}

/**
 * @brief Return the current view
 *
 * @return const View& Constant reference to the view
 */
const View& GenericView::getView() const
{
    return _View;
}

/**
 * @brief Update the view
 *
 * @param board Constant reference to the board
 * @param player Constant reference to the player
 */
void GenericView::update(const Board &board, const Player &player)
{
    const Vector2f playerPos = player.getPosition();
    const Vector2u boardSize = static_cast<const Vector2u>(board.getDimensionInTile());
    Vector2f newCenter       = playerPos;

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
