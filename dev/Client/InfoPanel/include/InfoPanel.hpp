#ifndef __INFOPANEL_HPP__
#define __INFOPANEL_HPP__

#include <iostream>
#include <SFML/Graphics.hpp>

#include "Player.hpp"

using namespace std;
using namespace sf;

class InfoPanel
{
    private:
        uint32_t       _WidthInPixel;
        uint32_t       _HeightInPixel;
        Vector2u       _Position;

        RectangleShape _Shape;
        Font           _Font;
        Text           _Text;

    public:
        InfoPanel(const uint32_t widthInPixel, const uint32_t heightInPixel, const Vector2u &position);

        uint32_t getWidthInPixel()  const;
        uint32_t getHeightInPixel() const;

        const RectangleShape& getShape() const;
        const Text&           getText()  const;

        void update(const Player &player);
};

#endif
