#ifndef __PLAYER_HPP__
#define __PLAYER_HPP__

#include "Character.hpp"

class Player: public Character
{
    private:
        uint32_t _Money;

    public:
        // Constructors
        Player();
        Player(const string name);

        // Member functions (getters)
        uint32_t getMoney() const;

        // Member functions (setters)
        void setMoney(const uint32_t money);
};

#endif
