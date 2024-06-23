#ifndef __PISTOL_HPP__
#define __PISTOL_HPP__

#include "Weapon.hpp"

class Pistol : public Weapon
{
    private:
        uint32_t _Ammo;

        void _initPistol();

    public:
        Pistol();
        Pistol(const string &name);

        uint32_t getAmmo() const;

        bool isUsable() const override;
        void updatePosition(const Vector2f &playerPosition, const DirectionType &frameDirection, const uint32_t frameIndex) override;
        bool performAttack(Character &target, const Vector2f &mousePosition) override;
};

#endif
