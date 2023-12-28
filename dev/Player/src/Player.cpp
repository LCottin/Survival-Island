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
    _Sprite.setTexture(_Texture);

    // Initialize frame sequences for each direction
    for (size_t i = 0; i < FRAMES_PER_DIRECTION; i++)
    {
        _UpFrames.push_back(   IntRect(i * FRAME_WIDTH, 0 * FRAME_HEIGHT, FRAME_WIDTH, FRAME_HEIGHT));
        _RightFrames.push_back(IntRect(i * FRAME_WIDTH, 1 * FRAME_HEIGHT, FRAME_WIDTH, FRAME_HEIGHT));
        _LeftFrames.push_back( IntRect(i * FRAME_WIDTH, 2 * FRAME_HEIGHT, FRAME_WIDTH, FRAME_HEIGHT));
        _DownFrames.push_back( IntRect(i * FRAME_WIDTH, 3 * FRAME_HEIGHT, FRAME_WIDTH, FRAME_HEIGHT));
    }

    // Set initial animation state
    _CurrentFrames     = &_UpFrames;
    _CurrentFrameIndex = 0;
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

    _Position.x = x;
    _Position.y = y;
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

/**
 * @brief Change the health bar
 *
 */
void Player::updateHealthBar()
{
    float_t barWidth = static_cast<float_t>(_Attributes.Health / _Attributes.MaxHealth * FRAME_WIDTH * _Sprite.getScale().x);
    _HealthBar.setSize(Vector2f(barWidth, HEALTH_BAR_HEIGHT));
    _HealthBar.setPosition(Vector2f(_Position.x, _Position.y - 10.0f));

    if (_Attributes.Health < (_Attributes.MaxHealth / 3U))
    {
        _HealthBar.setFillColor(Color::Red);
    }
    else if (_Attributes.Health < (2U * _Attributes.MaxHealth / 3U))
    {
        _HealthBar.setFillColor(Color::Yellow);
    }
    else
    {
        _HealthBar.setFillColor(Color::Green);
    }
}
