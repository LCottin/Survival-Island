#include "WeaponPrv.hpp"

const string WeaponTypeString[static_cast<uint32_t>(WeaponType::COUNT)] =
{
    [static_cast<uint32_t>(WeaponType::DEFAULT)] = "Weapons",
    [static_cast<uint32_t>(WeaponType::KNIFE)]   = "Knives",
};
