#include "Character.hpp"
#include "CharacterPrv.hpp"
#include "ConfigDev.hpp"
#include "Random.hpp"
#include "BoardPub.hpp"

/* Constructors */
Character::Character()
{
    _Name = CharacterDefaultName[static_cast<uint32_t>(CharacterType::DEFAULT)];
}

Character::Character(const string &name)
{
    _Name = name;
}

/* Destructor */
Character::~Character()
{
}

/**
 * @brief Load the default values from a JSON file
 *
 */
json Character::_loadFromJson(const CharacterType type) const
{
    const string filename = CharacterTypeString[static_cast<uint32_t>(type)];
    ifstream file("../assets/json/" + filename + ".json");
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
 * @brief Initialize the attributes of the character from the JSON file
 *
 * @param type Type of the Character
 * @warning This function only initializes the attributes that are common to all characters
 *
 */
void Character::_initCommon(const CharacterType type)
{
    _Type    = type;
    _IsAlive = true;

    const json data = _loadFromJson(type);

    const auto characterData    = data[_Name];
    _Attributes = { .Health     = characterData.contains("Health")     ? characterData["Health"].get<uint32_t>()     : 100U,
                    .MaxHealth  = characterData.contains("Health")     ? characterData["Health"].get<uint32_t>()     : 100U,
                    .Level      = characterData.contains("Level")      ? characterData["Level"].get<uint32_t>()      :   1U,
                    .Experience = characterData.contains("Experience") ? characterData["Experience"].get<uint32_t>() :   0U,
                    .Strength   = characterData.contains("Strength")   ? characterData["Strength"].get<uint32_t>()   :  10U,
                    .Defense    = characterData.contains("Defense")    ? characterData["Defense"].get<uint32_t>()    :  10U,
                    .Speed      = characterData.contains("Speed")      ? characterData["Speed"].get<uint32_t>()      :  10U,
                    .Age        = characterData.contains("Age")        ? characterData["Age"].get<uint32_t>()        :  25U };

    _Position.x = characterData.contains("Position_x") ? characterData["Position_x"].get<float_t>() : Random::getRandomFloat(0.0f, static_cast<float_t>(BoardSizeInTile::WIDTH  * ConfigDev::tileSize));
    _Position.y = characterData.contains("Position_y") ? characterData["Position_y"].get<float_t>() : Random::getRandomFloat(0.0f, static_cast<float_t>(BoardSizeInTile::HEIGHT * ConfigDev::tileSize));

    _Sprite.setPosition(static_cast<Vector2f>(_Position));

    _DamageTimer = seconds(1.0f);
    _DamageCooldown.restart();
}

/**
 * @brief Restart cooldown timer after taking damage
 *
 */
void Character::_restartTimer()
{
    _DamageCooldown.restart();
}

/**
 * @brief Get the name of the character
 *
 * @return Name of the character
 *
 */
string Character::getName() const
{
    return _Name;
}

/**
 * @brief Get the age of the character
 *
 * @return Age of the character
 *
 */
uint32_t Character::getAge() const
{
    return _Attributes.Age;
}

/**
 * @brief Get the health of the character
 *
 * @return Health of the character
 *
 */
uint32_t Character::getHealth() const
{
    return _Attributes.Health;
}

/**
 * @brief Get the maximum health of the character
 *
 * @return Maximum health of the character
 *
 */
uint32_t Character::getMaxHealth() const
{
    return _Attributes.MaxHealth;
}

/**
 * @brief Get the level of the character
 *
 * @return Level of the character
 *
 */
uint32_t Character::getLevel() const
{
    return _Attributes.Level;
}

/**
 * @brief Get the experience of the character
 *
 * @return Experience of the character
 *
 */
uint32_t Character::getExperience() const
{
    return _Attributes.Experience;
}

/**
 * @brief Get the strength of the character
 *
 * @return Strength of the character
 *
 */
uint32_t Character::getStrength() const
{
    return _Attributes.Strength;
}

/**
 * @brief Get the defense of the character
 *
 * @return Defense of the character
 *
 */
uint32_t Character::getDefense() const
{
    return _Attributes.Defense;
}

/**
 * @brief Get the speed of the character
 *
 * @return Speed of the character
 *
 */
uint32_t Character::getSpeed() const
{
    return _Attributes.Speed;
}

/**
 * @brief Get character current position
 *
 */
Vector2f Character::getPosition() const
{
    return _Position;
}

/**
 * @brief Get character previous position
 *
 */
Vector2f Character::getPreviousPosition() const
{
    return _PreviousPosition;
}

/**
 * @brief Return character current scale
 *
 */
Vector2u Character::getScale() const
{
    return _Scale;
}

/**
 * @brief Return character current scaled size
 *
 */
Vector2u Character::getSize() const
{
    return _Size;
}

/**
 * @brief Return character current type
 *
 */
CharacterType Character::getType() const
{
    return _Type;
}

/**
 * @brief Get the current sprite
 *
 */
Sprite& Character::getSprite()
{
    return _Sprite;
}

/**
 * @brief Get the healthBar
 *
 */
RectangleShape& Character::getHealthBar()
{
    return _HealthBar;
}

/**
 * @brief Check if the character is alive
 *
 * @return True if the character is alive, false otherwise
 *
 */
bool Character::isAlive() const
{
    return _IsAlive;
}

/**
 * @brief Set the name of the character
 *
 * @param name Name of the character
 *
 */
void Character::setName(const string &name)
{
    _Name = name;
}

/**
 * @brief Decrease health when defending
 *
 * @param damage Damage to take
 * @return true if character is still alive, false if the character died
 *
 */
bool Character::takeDamage(const uint32_t damage)
{
    if (_DamageCooldown.getElapsedTime() >= _DamageTimer)
    {
        if (_Attributes.Health <= damage)
        {
            /* Kill the character */
            _Attributes.Health = 0U;
            _IsAlive           = false;
        }
        else
        {
            _Attributes.Health -= damage;
        }

        updateHealthBar();
        _restartTimer();
    }

    return _IsAlive;
}

/**
 * @brief Set alive status
 *
 * @param isAlive New status of the character
 */
void Character::setAlive(const bool isAlive)
{
    _IsAlive = isAlive;
}

/**
 * @brief Set new health and update status and health bar
 *
 * @param health New health of the character
 */
void Character::setHealth(const uint32_t health)
{
    if (health > _Attributes.MaxHealth)
    {
        _Attributes.Health = _Attributes.MaxHealth;
    }
    else
    {
        _Attributes.Health = health;
    }

    if (_Attributes.Health == 0)
    {
        _IsAlive = false;
    }

    updateHealthBar();
}

/**
 * @brief Set new position of the character
 *
 * @param position Vector2f containing new position
 *
 */
void Character::setPosition(const Vector2f position)
{
    _PreviousPosition = _Position;
    _Position         = position;
    _Sprite.setPosition(_Position);
}

/**
 * @brief Set new position of the character
 *
 * @param x New position on x axis
 * @param y New position on y axis
 *
 */
void Character::setPosition(const float_t x, const float_t y)
{
    _PreviousPosition = _Position;
    _Position.x       = x;
    _Position.y       = y;
    _Sprite.setPosition(_Position);
}

/**
 * @brief The character says hello
 *
 */
void Character::sayHello() const
{
    cout << "Hello World, my name is " << _Name << endl;
}

/**
 * @brief The character presents himself
 *
 */
void Character::presentation() const
{
    cout << "Hello, my name is " << _Name << " and I am " << _Attributes.Age << " years old." << endl;
    cout << "I am level " << _Attributes.Level << " and I have " << _Attributes.Health << " health points." << endl;
    cout << "I have " << _Attributes.Strength << " strength points, " << _Attributes.Defense << " defense points and " << _Attributes.Speed << " speed points." << endl;
}

/**
 * @brief Attack someone, decrease both healths and update alive status
 *
 * @param defender Character attacked
 * @return true if the attacker survived, else false
 *
 */
bool Character::attack(Character &defender)
{
    if (_DamageCooldown.getElapsedTime() >= _DamageTimer)
    {
        /* Attack opponent */
        const uint32_t defense = defender.getDefense();
        uint32_t damageToDeal  = 0U;

        if (defense < _Attributes.Strength)
        {
            damageToDeal = _Attributes.Strength - defense;
        }

        const bool isStillAlive = defender.takeDamage(damageToDeal);

        /* If opponent is still alive, take damage according to its defense */
        if (isStillAlive == true)
        {
            if (_Attributes.Health <= defense)
            {
                _Attributes.Health = 0U;
                _IsAlive           = false;
            }
            else
            {
                _Attributes.Health -= defense;
            }
        }

        updateHealthBar();
        _restartTimer();
    }

    return _IsAlive;
}

/**
 * @brief Change the health bar
 *
 */
void Character::updateHealthBar()
{
    /* Calculate the health percentage */
    const float_t healthPercentage = static_cast<float_t>(_Attributes.Health) / static_cast<float_t>(_Attributes.MaxHealth);

    /* Calculate the width of the health bar based on the health percentage */
    const float_t barWidth = healthPercentage * _Size.x;

    /* Set the size and position of the health bar */
    _HealthBar.setSize(Vector2f(barWidth, HEALTH_BAR_HEIGHT));
    _HealthBar.setPosition(Vector2f(_Position.x, _Position.y - 10.0f));

    /* Set the fill color based on the health percentage */
    if (healthPercentage < 0.33f)
    {
        _HealthBar.setFillColor(Color::Red);
    }
    else if (healthPercentage < 0.66f)
    {
        _HealthBar.setFillColor(Color::Yellow);
    }
    else
    {
        _HealthBar.setFillColor(Color::Green);
    }
}
