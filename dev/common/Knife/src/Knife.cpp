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

/**
 * @brief Set weapon position in character right hand
 *
 * @param playerPosition The position of the player
 * @param frameDirection The direction of the frame
 * @param frameIndex The index of the frame
 */
void Knife::updatePosition(const Vector2f &playerPosition, const DirectionType &frameDirection, const uint32_t frameIndex)
{
    Vector2f rightHandPosition = playerPosition;

    if (frameDirection == DirectionType::DOWN)
    {
        rightHandPosition.x += 5.0f - (_Size.x / 2.0f);
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
        rightHandPosition.x -= (_Size.x) / 2 - 3.0f;
        rightHandPosition.y += (_Size.y) / 2 + 3.0f;

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
        rightHandPosition.x += (_Size.x / 2.0f) - 5.0f;
        rightHandPosition.y += 6.0f;

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
 * @brief Perform an attack with the knife
 *
 * @param target The target of the attack
 * @param mousePosition Position of the mouse relative to window
 * @return true if the target survived the attack, false otherwise
 */
bool Knife::performAttack(Character &target, const Vector2f &mousePosition)
{
    (void)mousePosition;

    bool isStillAlive = target.isAlive();

    if (isUsable() == true)
    {
        _Attributes.Durability -= 1U;

        /* Compute probability to fail */
        const uint32_t failProbability = Random::getRandomInteger(0U, 100U);

        /* Attack opponent if not fail */
        if (failProbability < _Attributes.Accuracy)
        {
            isStillAlive = target.takeDamage(_Attributes.Damage);
        }
    }

    return isStillAlive;
}
