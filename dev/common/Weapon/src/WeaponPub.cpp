#include "WeaponPub.hpp"

const string WeaponName[static_cast<uint32_t>(WeaponType::COUNT)] =
{
    [static_cast<uint32_t>(WeaponType::DEFAULT)] = "Default",
    [static_cast<uint32_t>(WeaponType::KNIFE)]   = "Knife",
};
