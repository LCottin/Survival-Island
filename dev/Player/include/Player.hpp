#ifndef __PLAYER_HPP__
#define __PLAYER_HPP__

#include "Character.hpp"

class Player: public Character
{
    private:
        uint32_t _Money;

        void _initPlayer();

    public:
        /* Constructors */
        Player();
        Player(const string &name);

        /* Member functions (getters) */
        uint32_t getMoney() const;

        /* Member functions (setters) */
        void setMoney(const uint32_t money);
        void setPosition(const Vector2u position, const bool changeFrame);
        void setPosition(const uint32_t x, const uint32_t y, const bool changeFrame);

        /* Member functions (others) */
        void updateFrame(const DirectionType direction);
};

#endif
