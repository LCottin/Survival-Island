#ifndef __PLAYER_HPP__
#define __PLAYER_HPP__

#include "Character.hpp"

class Player: public Character
{
    private:
        uint32_t _Money;

        void _initPlayer();
        void _updateFrame(const Vector2f newPosition);

    public:
        /* Constructors */
        Player();
        Player(const string &name);

        /* Member functions (getters) */
        uint32_t getMoney() const;

        /* Member functions (setters) */
        void setMoney(const uint32_t money);
        void setPosition(const Vector2f position, const bool hasMoved);
        void setPosition(const float_t x, const float_t y, const bool hasMoved);

        /* Member functions (others) */
};

#endif
