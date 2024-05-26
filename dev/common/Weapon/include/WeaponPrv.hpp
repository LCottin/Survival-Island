#ifndef __WEAPON_PRV_HPP__
#define __WEAPON_PRV_HPP__

#include "WeaponPub.hpp"

namespace WeaponSize
{
    constexpr uint32_t WIDTH  = 32U;
    constexpr uint32_t HEIGHT = 32U;
}

extern const string WeaponTypeString[static_cast<uint32_t>(WeaponType::COUNT)];

#endif //__WEAPON_PRV_HPP__
