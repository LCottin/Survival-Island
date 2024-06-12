#ifndef __WEAPON_PUB_HPP__
#define __WEAPON_PUB_HPP__

#include <iostream>

using namespace std;

typedef struct
{
    uint32_t Damage;
    uint32_t Accuracy;
    uint32_t Range;
} WeaponAttributes;

enum class WeaponType : uint32_t
{
    DEFAULT,
    KNIFE,
    PISTOL,
    COUNT,
};

enum class DirectionType : uint32_t
{
    UP,
    DOWN,
    LEFT,
    RIGHT,
};

extern const string WeaponName[static_cast<uint32_t>(WeaponType::COUNT)];

#endif //__WEAPON_PUB_HPP__
