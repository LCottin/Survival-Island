#include "Character.hpp"

// Constructors
Character::Character()
{
    _Type    = CHARACTER_TYPE_DEFAULT;
    _Name    = CharacterDefaultName[_Type];
    _IsAlive = true;

    _initAttributes(CharacterTypeString[_Type]);
}

Character::Character(const string name)
{
    _Type    = CHARACTER_TYPE_DEFAULT;
    _Name    = name;
    _IsAlive = true;

    _initAttributes(CharacterTypeString[_Type]);
}

// Destructor
Character::~Character()
{
}

/**
 * @brief Load the default values from a JSON file
 *
 */
json Character::_loadFromJson(const string filename) const
{
    ifstream file("../assets/json/" + filename + ".json");
    json data;

    if (!file.is_open())
    {
        cerr << "Error opening file" << endl;
        return json();
    }

    try
    {
        data = json::parse(file);
    }
    catch (const json::exception &e)
    {
        cerr << "JSON error: " << e.what() << endl;
    }
    catch (const exception &e)
    {
        cerr << "Standard error: " << e.what() << endl;
    }

    file.close();

    return data;
}

/**
 * @brief Initialize the attributes of the character from the JSON file
 *
 * @warning This function only initializes the attributes that are common to all characters
 *
 */
void Character::_initAttributes(const string filename)
{
    json data = _loadFromJson(filename);

    if (data.empty())
    {
        cerr << "Error loading JSON data" << endl;
        return;
    }

    auto characterData  = data[_Name];
    _Attributes         = { .Health     = characterData.contains("Health")     ? characterData["Health"].get<uint32_t>()     : 100U,
                            .Level      = characterData.contains("Level")      ? characterData["Level"].get<uint32_t>()      :   1U,
                            .Experience = characterData.contains("Experience") ? characterData["Experience"].get<uint32_t>() :   0U,
                            .Strength   = characterData.contains("Strength")   ? characterData["Strength"].get<uint32_t>()   :  10U,
                            .Defense    = characterData.contains("Defense")    ? characterData["Defense"].get<uint32_t>()    :  10U,
                            .Speed      = characterData.contains("Speed")      ? characterData["Speed"].get<uint32_t>()      :  10U,
                            .Age        = characterData.contains("Age")        ? characterData["Age"].get<uint32_t>()        :  25U };

    _Position.x = characterData.contains("Position_x") ? characterData["Position_x"].get<float_t>() : 0.0f;
    _Position.y = characterData.contains("Position_y") ? characterData["Position_y"].get<float_t>() : 0.0f;
    _Sprite.setPosition(_Position);
    _Sprite.scale(Vector2f(2.0f, 2.0f));
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
 * @brief Get player current position
 *
 */
Vector2f Character::getPosition() const
{
    return _Position;
}

/**
 * @brief Return play current scale
 *
 */
Vector2f Character::getScale() const
{
    return _Sprite.getScale();
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
void Character::setName(const string name)
{
    _Name = name;
}

/**
 * @brief Set new position of the player
 *
 * @param position Vector2f containing new position
 * @param changeFrame Boolean to change the frame displayed
 *
 */
void Character::setPosition(const Vector2f position, const bool changeFrame)
{
    (void)changeFrame;
    _Position = position;
    _Sprite.setPosition(_Position);
}

/**
 * @brief Set new position of the player
 *
 * @param x New position on x axis
 * @param y New position on y axis
 * @param changeFrame Boolean to change the frame displayed
 *
 */
void Character::setPosition(const float_t x, const float_t y, const bool changeFrame)
{
    (void)changeFrame;
    _Position.x = x;
    _Position.y = y;
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
 * @brief Change the frame
 *
 * @param direction New direction to set
 *
 */
void Character::updateFrame(const uint32_t direction)
{
    (void)direction;
}
