#include "Player.hpp"

// Constructors
Player::Player() : Character()
{
    _Type  = CHARACTER_TYPE_PLAYER;
    _Name  = CharacterDefaultName[_Type];
    _Money = 0;

    _initAttributes(CharacterTypeString[_Type]);
    _initPlayer();
}

Player::Player(const string name) : Character(name)
{
    _Type  = CHARACTER_TYPE_PLAYER;
    _Money = 0;

    _initAttributes(CharacterTypeString[_Type]);
    _initPlayer();
}

/**
 * @brief Init Player data
 *
 */
void Player::_initPlayer()
{
    bool load = _Texture.loadFromFile("../assets/images/player.png");
    if (load == false)
    {
        cerr << "Error loading player texture" << endl;
        exit(EXIT_FAILURE);
    }

    // Initialize frame sequences for each direction
    for (size_t i = 0; i < FRAMES_PER_DIRECTION; i++)
    {
        _UpFrames.push_back(   IntRect(i * PLAYER_WIDTH, 0 * PLAYER_HEIGHT, PLAYER_WIDTH, PLAYER_HEIGHT));
        _RightFrames.push_back(IntRect(i * PLAYER_WIDTH, 1 * PLAYER_HEIGHT, PLAYER_WIDTH, PLAYER_HEIGHT));
        _LeftFrames.push_back( IntRect(i * PLAYER_WIDTH, 2 * PLAYER_HEIGHT, PLAYER_WIDTH, PLAYER_HEIGHT));
        _DownFrames.push_back( IntRect(i * PLAYER_WIDTH, 3 * PLAYER_HEIGHT, PLAYER_WIDTH, PLAYER_HEIGHT));
    }

    // Set initial animation state
    _CurrentFrames     = &_UpFrames;
    _CurrentFrameIndex = 0;

    _Scale = Vector2f(3.0f, 3.0f);
    _Size  = Vector2f(PLAYER_WIDTH * _Scale.x, PLAYER_HEIGHT * _Scale.y);

    _Sprite.scale(_Scale);
    _Sprite.setTexture(_Texture);
    _Sprite.setTextureRect((*_CurrentFrames)[_CurrentFrameIndex]);
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
 * @param changeFrame Boolean to change the frame displayed
 *
 */
void Player::setPosition(const Vector2f position, const bool changeFrame)
{
    if (changeFrame == true)
    {
        int32_t newDirection = -1;
        if (_Position.x < position.x)
        {
            newDirection = DIRECTION_RIGHT;
        }
        else if (_Position.x > position.x)
        {
            newDirection = DIRECTION_LEFT;
        }
        else if (_Position.y < position.y)
        {
            newDirection = DIRECTION_UP;
        }
        else if (_Position.y > position.y)
        {
            newDirection = DIRECTION_DOWN;
        }
        updateFrame(newDirection);
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
 * @param changeFrame Boolean to change the frame displayed
 *
 */
void Player::setPosition(const float_t x, const float_t y, const bool changeFrame)
{
    if (changeFrame == true)
    {
        int32_t newDirection = -1;
        if (_Position.x < x)
        {
            newDirection = DIRECTION_RIGHT;
        }
        else if (_Position.x > x)
        {
            newDirection = DIRECTION_LEFT;
        }
        else if (_Position.y < y)
        {
            newDirection = DIRECTION_UP;
        }
        else if (_Position.y > y)
        {
            newDirection = DIRECTION_DOWN;
        }
        updateFrame(newDirection);
    }

    _PreviousPosition = _Position;
    _Position.x       = x;
    _Position.y       = y;
    _Sprite.setPosition(_Position);
}

/**
 * @brief Change the frame of the player
 *
 * @param direction New direction to set
 *
 */
void Player::updateFrame(const uint32_t direction)
{
    switch (direction)
    {
        case DIRECTION_UP :
            _CurrentFrames     = &_UpFrames;
            break;

        case DIRECTION_DOWN :
            _CurrentFrames     = &_DownFrames;
            break;

        case DIRECTION_LEFT :
            _CurrentFrames     = &_LeftFrames;
            break;

        case DIRECTION_RIGHT:
            _CurrentFrames     = &_RightFrames;
            break;
    }

    _CurrentFrameIndex = (_CurrentFrameIndex + 1U) % FRAMES_PER_DIRECTION;
    _Sprite.setTextureRect((*_CurrentFrames)[_CurrentFrameIndex]);
}
