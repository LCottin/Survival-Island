#include "Player.hpp"
#include "PlayerPrv.hpp"
#include "ConfigDev.hpp"

/* Constructors */
Player::Player() : Character()
{
    _Name  = CharacterDefaultName[static_cast<uint32_t>(_Type)];

    _initCommon(CharacterType::PLAYER);
    _initPlayer();
}

Player::Player(const string &name) : Character(name)
{
    _Name = name;

    _initCommon(CharacterType::PLAYER);
    _initPlayer();
}

/**
 * @brief Init Player data
 *
 */
void Player::_initPlayer()
{
    if (_Texture.loadFromFile(ConfigDev::playerImgPath) == false)
    {
        throw runtime_error("Error loading player texture");
    }

    /* Initialize frame sequences for each direction */
    for (size_t i = 0; i < FRAMES_PER_DIRECTION; i++)
    {
        _UpFrames.push_back(   IntRect(i * PlayerSize::WIDTH, 0 * PlayerSize::HEIGHT, PlayerSize::WIDTH, PlayerSize::HEIGHT));
        _RightFrames.push_back(IntRect(i * PlayerSize::WIDTH, 1 * PlayerSize::HEIGHT, PlayerSize::WIDTH, PlayerSize::HEIGHT));
        _LeftFrames.push_back( IntRect(i * PlayerSize::WIDTH, 2 * PlayerSize::HEIGHT, PlayerSize::WIDTH, PlayerSize::HEIGHT));
        _DownFrames.push_back( IntRect(i * PlayerSize::WIDTH, 3 * PlayerSize::HEIGHT, PlayerSize::WIDTH, PlayerSize::HEIGHT));
    }

    /* Set initial animation state */
    _CurrentFrames     = &_UpFrames;
    _CurrentFrameIndex = 0;

    _Scale = Vector2u(3U, 3U);
    _Size  = Vector2u(PlayerSize::WIDTH * _Scale.x, PlayerSize::HEIGHT * _Scale.y);

    _Sprite.scale(static_cast<Vector2f>(_Scale));
    _Sprite.setTexture(_Texture);
    _Sprite.setTextureRect((*_CurrentFrames)[_CurrentFrameIndex]);

    _Money = 0;
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

/**
 * @brief Set new position of the player
 *
 * @param position Vector2f containing new position
 * @param hasMoved Boolean to change the frame displayed
 *
 */
void Player::setPosition(const Vector2f position, const bool hasMoved)
{
    if (hasMoved == true)
    {
        _updateFrame(position);
    }

    _PreviousPosition = _Position;
    _Position         = position;
    _Sprite.setPosition(_Position);
}

/**
 * @brief Set new position of the player
 *
 * @param x New position on x axis
 * @param y New position on y axis
 * @param hasMoved Boolean to change the frame displayed
 *
 */
void Player::setPosition(const float_t x, const float_t y, const bool hasMoved)
{
    if (hasMoved == true)
    {
        _updateFrame(Vector2f(x, y));
    }

    _PreviousPosition = _Position;
    _Position.x       = x;
    _Position.y       = y;
    _Sprite.setPosition(_Position);
}

/**
 * @brief Change the frame of the player
 *
 * @param newDirection New direction to set
 *
 */
void Player::_updateFrame(const Vector2f newPosition)
{
    if (_Position.x < newPosition.x)
    {
        _CurrentFrames = &_RightFrames;
    }
    else if (_Position.x > newPosition.x)
    {
        _CurrentFrames = &_LeftFrames;
    }
    else if (_Position.y < newPosition.y)
    {
        _CurrentFrames = &_UpFrames;
    }
    else if (_Position.y > newPosition.y)
    {
        _CurrentFrames = &_DownFrames;
    }

    _CurrentFrameIndex = (_CurrentFrameIndex + 1U) % FRAMES_PER_DIRECTION;
    _Sprite.setTextureRect((*_CurrentFrames)[_CurrentFrameIndex]);
}
