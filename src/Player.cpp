#include "Player.hpp"

// Constructors
Player::Player() : Character()
{
    _Type = CHARACTER_TYPE_PLAYER;
    _Name = CharacterDefaultName[_Type];
    _Money = 0;

    _initAttributes(CharacterTypeString[_Type]);
}

Player::Player(const string name) : Character(name)
{
    _Type = CHARACTER_TYPE_PLAYER;
    _Money = 0;

    _initAttributes(CharacterTypeString[_Type]);
}

/**
 * @brief Get the money of the player
 *
 */
uint32_t Player::getMoney() const
{
    return _Money;
}

/**
 * @brief Set the money of the player
 *
 */
void Player::setMoney(const uint32_t money)
{
    _Money = money;
}
