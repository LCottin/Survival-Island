#ifndef __PLAYER_HPP__
#define __PLAYER_HPP__

#include "Character.hpp"
#include "PlayerData.hpp"

class Player: public Character
{
    private:
        uint32_t _Money;

        void _initPlayer();

    public:
        // Constructors
        Player();
        Player(const string name);

        // Member functions (getters)
        uint32_t getMoney() const;

        // Member functions (setters)
        void setMoney(const uint32_t money);

        void updateFrame(const int32_t direction);
};

#endif
