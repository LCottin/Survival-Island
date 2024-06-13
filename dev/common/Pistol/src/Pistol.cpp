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

    const json data       = _initCommon(_Type);
    const auto weaponData = data[_Name];

    _Ammo = weaponData.contains("Ammo") ? weaponData["Ammo"].get<uint32_t>() : 10U;

    if (_Texture.loadFromFile(ConfigDev::pistolImgPath) == false)
    {
        throw runtime_error("Error loading pistol texture.");
    }
}

/**
 * @brief returns the ammo of the pistol
 *
 */
uint32_t Pistol::getAmmo() const
{
    return _Ammo;
}

/**
 * @brief Tells if the pistol can be used
 *
 * @return true if it can be used, false otherwise
 */
bool Pistol::isUsable() const
{
    return ((_Attributes.Durability > 0) && (_Ammo > 0U));
}

/**
 * @brief Set weapon position in character right hand
 *
 * @param playerPosition The position of the player
 * @param frameDirection The direction of the frame
 * @param frameIndex The index of the frame
 */
void Pistol::updatePosition(const Vector2f &playerPosition, const DirectionType &frameDirection, const uint32_t frameIndex)
{
    Vector2f rightHandPosition = playerPosition;

    if (frameDirection == DirectionType::DOWN)
    {
        rightHandPosition.x -= (_Size.x / 2.0f) + 4.0f;
        rightHandPosition.y += _Size.y;

        if (frameIndex == 1U)
        {
            rightHandPosition.y -= 2.0f;
        }
        else if (frameIndex == 3U)
        {
            rightHandPosition.x += 2.0f;
            rightHandPosition.y -= 1.0f;
        }
    }

    else if (frameDirection == DirectionType::RIGHT)
    {
        rightHandPosition.x += (_Size.x / 2) - 3.0f;
        rightHandPosition.y += (_Size.y / 2) + 3.0f;

        if (frameIndex == 1U)
        {
            rightHandPosition.x -= 3.0f;
            rightHandPosition.y += 3.0f;
        }
        else if (frameIndex == 3U)
        {
            rightHandPosition.x += 3.0f;
            rightHandPosition.y += 3.0f;
        }
    }

    else if (frameDirection == DirectionType::LEFT)
    {
        rightHandPosition.x -= (_Size.x / 2) - 3.0f;
        rightHandPosition.y += (_Size.y / 2) + 3.0f;

        if (frameIndex == 1U)
        {
            rightHandPosition.x += 3.0f;
            rightHandPosition.y += 3.0f;
        }
        else if (frameIndex == 3U)
        {
            rightHandPosition.x -= 3.0f;
            rightHandPosition.y += 3.0f;
        }
    }

    else if (frameDirection == DirectionType::UP)
    {
        rightHandPosition.x += (_Size.x / 2.0f) + 6.0f;
        rightHandPosition.y += 15.0f;

        if (frameIndex == 1U)
        {
            rightHandPosition.y -= 2.0f;
        }
        else if (frameIndex == 3U)
        {
            rightHandPosition.x -= 3.0f;
            rightHandPosition.y -= 1.0f;
        }
    }

    _Position = rightHandPosition;
    _Sprite.setPosition(_Position);
}
