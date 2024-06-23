#include "Pistol.hpp"
#include "PistolPrv.hpp"
#include "Random.hpp"
#include "ConfigDev.hpp"

static inline constexpr float_t radiansToDegrees(const float_t radians)
{
    return radians * 180.0f / M_PI;
}

static inline constexpr float_t normalizeAngle(float_t angle)
{
    while (angle < 0.0f)    angle += 360.0f;
    while (angle >= 360.0f) angle -= 360.0f;

    return angle;
}

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

/**
 * @brief Perform an attack with the pistol
 *
 * @param target The target of the attack
 * @param mousePosition Position of the mouse relative to window
 * @return true if the target survived the attack, false otherwise
 */
bool Pistol::performAttack(Character &target, const Vector2f &mousePosition)
{
    bool isStillAlive = target.isAlive();

    if ((isUsable() == true) && (_DamageCooldown.getElapsedTime() >= _DamageTimer))
    {
        const Vector2f targetPosition = target.getPosition();

        /* Compute angle between weapon and mouse */
        const float_t dxMouse = mousePosition.x - _Position.x;
        const float_t dyMouse = mousePosition.y - _Position.y;
        float_t angleToMouse  = normalizeAngle(radiansToDegrees(atan2f(dyMouse, dxMouse)));

        /* Compute offset on angle according to position */
        switch(_Direction)
        {
            case DirectionType::UP:
            {
                angleToMouse += 0.0f;
                break;
            }
            case DirectionType::LEFT:
            {
                angleToMouse -= 90.0f;
                break;
            }
            case DirectionType::RIGHT:
            {
                angleToMouse += 90.0f;
                break;
            }
            case DirectionType::DOWN:
            {
                angleToMouse -= 180.0f;
                break;
            }
        }

        /* Compute angle between weapon and target */
        const float_t dxTarget      = targetPosition.x - _Position.x;
        const float_t dyTarget      = targetPosition.y - _Position.y;
        const float_t angleToTarget = normalizeAngle(radiansToDegrees(atan2f(dyTarget, dxTarget)));

        /* Compute difference with max angle */
        const float_t angleDiff = fabsf(angleToTarget - angleToMouse);

        /* Compute distance between weapon and target */
        const float_t distanceToTarget = sqrtf(dxTarget * dxTarget + dyTarget * dyTarget);

        /* Compute probability to fail */
        const uint32_t failProbability = Random::getRandomInteger(0U, 100U);

        /* If angle is good and target in weapon range, then shoot */
        if ((angleDiff < MAXIMUM_ALLOWED_ANGLE_DEGREE) && (distanceToTarget <= _Attributes.Range) && (failProbability < _Attributes.Accuracy))
        {
            _Attributes.Durability -= 1U;
            _Ammo                  -= 1U;

            isStillAlive = target.takeDamage(_Attributes.Damage);
            _restartTimer();
        }
    }

    return isStillAlive;
}
