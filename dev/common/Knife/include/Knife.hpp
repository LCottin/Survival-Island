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
};

#endif
