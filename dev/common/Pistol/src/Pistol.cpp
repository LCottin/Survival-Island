#include "Pistol.hpp"
#include "Random.hpp"
#include "ConfigDev.hpp"

Pistol::Pistol() : Weapon()
{
    _Name = WeaponName[static_cast<uint32_t>(_Type)];

    _initPistol();
}

Pistol::Pistol(const string &name) : Weapon(name)
{
    _initPistol();
}

void Pistol::_initPistol()
{
    _Type = WeaponType::PISTOL;
    _initCommon(_Type);

    if (_Texture.loadFromFile(ConfigDev::pistolImgPath) == false)
    {
        throw runtime_error("Error loading pistol texture.");
    }
}
