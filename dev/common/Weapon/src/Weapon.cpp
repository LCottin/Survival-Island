#include "Weapon.hpp"
#include "WeaponPrv.hpp"
#include "ConfigDev.hpp"
#include "BoardPub.hpp"
#include "Random.hpp"

Weapon::Weapon()
{
    _Name = WeaponName[static_cast<uint32_t>(WeaponType::DEFAULT)];
}

Weapon::Weapon(const string &name)
{
    _Name = name;
}

Weapon::~Weapon()
{
}

/**
 * @brief Load the default values from a JSON file
 *
 */
json Weapon::_loadFromJson(const WeaponType type) const
{
    const string filename = WeaponTypeString[static_cast<uint32_t>(type)];
    ifstream file("../assets/json/Weapons/" + filename + ".json");
    json data;

    if (file.is_open() == false)
    {
        throw runtime_error("Failed to open json/" + filename + " file.");
    }

    try
    {
        data = json::parse(file);

        if (data.empty() == true)
        {
            throw runtime_error("File json/" + filename + " is empty.");
        }
    }
    catch (const exception& e)
    {
        throw runtime_error("Failed to parse json/" + filename + " file.");
    }

    file.close();

    return data;
}

/**
 * @brief Initialize the attributes of the weapon from the JSON file
 *
 * @param type Type of the Weapon
 * @warning This function only initializes the attributes that are common to all weapons
 *
 */
json Weapon::_initCommon(const WeaponType type)
{
    _Type = type;

    const json data = _loadFromJson(type);

    const auto weaponData       = data[_Name];
    _Attributes = { .Accuracy   = weaponData.contains("Accuracy")   ? weaponData["Accuracy"].get<uint32_t>()   : 100U,
                    .Damage     = weaponData.contains("Damage")     ? weaponData["Damage"].get<uint32_t>()     :   0U,
                    .Range      = weaponData.contains("Range")      ? weaponData["Range"].get<uint32_t>()      :   0U,
                    .Durability = weaponData.contains("Durability") ? weaponData["Durability"].get<uint32_t>() :   0U };

    _UpFrame    = IntRect(0 * WeaponSize::WIDTH, 0 * WeaponSize::HEIGHT, WeaponSize::WIDTH, WeaponSize::HEIGHT);
    _RightFrame = IntRect(1 * WeaponSize::WIDTH, 0 * WeaponSize::HEIGHT, WeaponSize::WIDTH, WeaponSize::HEIGHT);
    _LeftFrame  = IntRect(0 * WeaponSize::WIDTH, 1 * WeaponSize::HEIGHT, WeaponSize::WIDTH, WeaponSize::HEIGHT);
    _DownFrame  = IntRect(1 * WeaponSize::WIDTH, 1 * WeaponSize::HEIGHT, WeaponSize::WIDTH, WeaponSize::HEIGHT);

    _CurrentFrame = &_DownFrame;

    _Scale = Vector2f(1.5f, 1.5f);
    _Size  = Vector2f(WeaponSize::WIDTH * _Scale.x, WeaponSize::HEIGHT * _Scale.y);

    _Sprite.setPosition(static_cast<Vector2f>(_Position));
    _Sprite.setTexture(_Texture);
    _Sprite.setScale(_Scale);
    _Sprite.setTextureRect(*_CurrentFrame);

    _DamageTimer = seconds(1.0f);
    _DamageCooldown.restart();

    return data;
}

/**
 * @brief Restart cooldown timer after being used
 *
 */
void Weapon::_restartTimer()
{
    _DamageCooldown.restart();
}

/**
 * @brief Get the damage of the weapon
 *
 * @return Damage of the weapon
 *
 */
uint32_t Weapon::getDamage() const
{
    return _Attributes.Damage;
}

/**
 * @brief Get the accuracy of the weapon
 *
 * @return Accuracy of the weapon
 *
 */
uint32_t Weapon::getAccuracy() const
{
    return _Attributes.Accuracy;
}

/**
 * @brief Get the range of the weapon
 *
 * @return Range of the weapon
 *
 */
uint32_t Weapon::getRange() const
{
    return _Attributes.Range;
}

/**
 * @brief Get the current durability
 *
 */
uint32_t Weapon::getDurability() const
{
    return _Attributes.Durability;
}

/**
 * @brief Get weapon current position
 *
 */
Vector2f Weapon::getPosition() const
{
    return _Position;
}

/**
 * @brief Get weapon previous position
 *
 */
Vector2f Weapon::getPreviousPosition() const
{
    return _PreviousPosition;
}

/**
 * @brief Return weapon current scale
 *
 */
Vector2f Weapon::getScale() const
{
    return _Scale;
}

/**
 * @brief Return weapon current scaled size
 *
 */
Vector2f Weapon::getSize() const
{
    return _Size;
}

/**
 * @brief Return weapon current type
 *
 */
WeaponType Weapon::getType() const
{
    return _Type;
}

/**
 * @brief Get the current sprite
 *
 */
Sprite& Weapon::getSprite()
{
    return _Sprite;
}

/**
 * @brief Tell if the weapon is usable
 *
 * @return true if the weapon is usable, false otherwise
 */
bool Weapon::isUsable() const
{
    return (_Attributes.Durability > 0);
}

/**
 * @brief Set new position of the weapon
 *
 * @param position Vector2f containing new position
 *
 */
void Weapon::setPosition(const Vector2f position)
{
    _PreviousPosition = _Position;
    _Position         = position;
    _Sprite.setPosition(_Position);
}

/**
 * @brief Set new position of the weapon
 *
 * @param x New position on x axis
 * @param y New position on y axis
 *
 */
void Weapon::setPosition(const float_t x, const float_t y)
{
    setPosition(Vector2f(x, y));
}

/**
 * @brief Set new frame of the weapon
 *
 * @param direction new direction to set the frame
 *
 */
void Weapon::setFrame(const DirectionType direction)
{
    switch (direction)
    {
        case DirectionType::LEFT:
        {
            _CurrentFrame = &_LeftFrame;
            _Direction    = DirectionType::LEFT;
            break;
        }
        case DirectionType::RIGHT:
        {
            _CurrentFrame = &_RightFrame;
            _Direction    = DirectionType::RIGHT;
            break;
        }
        case DirectionType::UP:
        {
            _CurrentFrame = &_UpFrame;
            _Direction    = DirectionType::UP;
            break;
        }
        case DirectionType::DOWN:
        {
            _CurrentFrame = &_DownFrame;
            _Direction    = DirectionType::DOWN;
            break;
        }
    }

    _Sprite.setTextureRect(*_CurrentFrame);
}
