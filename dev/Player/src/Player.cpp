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
 * @brief Change the frame of the player
 *
 * @param direction New direction to set, -1 to keep the same
 */
void Player::updateFrame(const int32_t direction)
{
    switch (direction)
    {
        case DIRECTION_UP :
            _CurrentFrames     = &_UpFrames;
            _CurrentFrameIndex = 0;
            _Sprite.setTextureRect((*_CurrentFrames)[_CurrentFrameIndex]);
            break;

        case DIRECTION_DOWN :
            _CurrentFrames     = &_DownFrames;
            _CurrentFrameIndex = 0;
            _Sprite.setTextureRect((*_CurrentFrames)[_CurrentFrameIndex]);
            break;

        case DIRECTION_LEFT :
            _CurrentFrames     = &_LeftFrames;
            _CurrentFrameIndex = 0;
            _Sprite.setTextureRect((*_CurrentFrames)[_CurrentFrameIndex]);
            break;

        case DIRECTION_RIGHT:
            _CurrentFrames     = &_RightFrames;
            _CurrentFrameIndex = 0;
            _Sprite.setTextureRect((*_CurrentFrames)[_CurrentFrameIndex]);
            break;

        default :
            _CurrentFrameIndex = (_CurrentFrameIndex + 1U) % FRAMES_PER_DIRECTION;
            break;
    }
}
