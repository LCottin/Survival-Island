#include "Knife.hpp"
#include "Random.hpp"
#include "ConfigDev.hpp"

Knife::Knife() : Weapon()
{
    _Name = WeaponName[static_cast<uint32_t>(_Type)];

    _initKnife();
}

Knife::Knife(const string &name) : Weapon(name)
{
    _initKnife();
}

void Knife::_initKnife()
{
    _Type = WeaponType::KNIFE;
    _initCommon(_Type);

    if (_Texture.loadFromFile(ConfigDev::knifeImgPath) == false)
    {
        throw runtime_error("Error loading knife texture.");
    }
}
