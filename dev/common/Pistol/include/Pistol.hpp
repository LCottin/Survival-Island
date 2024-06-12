#ifndef __PISTOL_HPP__
#define __PISTOL_HPP__

#include "Weapon.hpp"

class Pistol : public Weapon
{
    private:
        void _initPistol();

    public:
        Pistol();
        Pistol(const string &name);
};

#endif
