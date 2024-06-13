#ifndef __KNIFE_HPP__
#define __KNIFE_HPP__

#include "Weapon.hpp"

class Knife : public Weapon
{
    private:
        void _initKnife();

    public:
        Knife();
        Knife(const string &name);

        void updatePosition(const Vector2f &playerPosition, const DirectionType &frameDirection, const uint32_t frameIndex) override;
        bool performAttack(Character &target) override;
};

#endif
