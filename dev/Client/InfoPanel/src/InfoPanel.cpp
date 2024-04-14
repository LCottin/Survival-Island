#include "InfoPanel.hpp"
#include "ConfigDev.hpp"
#include "ConfigUser.hpp"

InfoPanel::InfoPanel(const uint32_t widthInPixel, const uint32_t heightInPixel, const Vector2u &position)
{
    if (_Font.loadFromFile(ConfigDev::fontPath) == false)
    {
        throw runtime_error("Failed to load text font.");
    }

    _WidthInPixel  = widthInPixel;
    _HeightInPixel = heightInPixel;
    _Position      = position;

    _Shape.setSize(Vector2f(_WidthInPixel, _HeightInPixel));
    _Shape.setFillColor(Color(220, 200, 180)); /* Light brown */

    _Text.setFont(_Font);
    _Text.setCharacterSize(20U);
    _Text.setFillColor(Color(80, 60, 40)); /* Dark Brown */
}


/**
 * @brief Return the width of the panel in pixel
 *
 */
uint32_t InfoPanel::getWidthInPixel() const
{
    return _WidthInPixel;
}

/**
 * @brief Return the height of the panel in pixel
 *
 */
uint32_t InfoPanel::getHeightInPixel() const
{
    return _HeightInPixel;
}

/**
 * @brief Return the shape of the panel
 *
 * @return const RectangleShape& Constant reference to the shape
 */
const RectangleShape& InfoPanel::getShape() const
{
    return _Shape;
}

/**
 * @brief Return the text of the panel
 *
 * @return const RectangleShape& Constant reference to the text
 */
const Text& InfoPanel::getText() const
{
    return _Text;
}

void InfoPanel::update(const Player &player)
{
    String textToDisplay = "Player\nHealth:\n" + to_string(player.getHealth()) + "\n\n\n\n";
    textToDisplay       += "Difficulty:\n" + GameDifficultyString[static_cast<uint32_t>(ConfigUser::difficulty)];

    _Text.setString(textToDisplay);

    _Shape.setPosition(_Position.x + 0U, _Position.y);
    _Text.setPosition( _Position.x + 5U, _Position.y);
}
