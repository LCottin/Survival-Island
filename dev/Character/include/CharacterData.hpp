#ifndef __CHARACTER_DATA_HPP__
#define __CHARACTER_DATA_HPP__

#include <string>

using namespace std;

typedef struct
{
    uint32_t Age;
    uint32_t Health;
    uint32_t MaxHealth;
    uint32_t Level;
    uint32_t Experience;
    uint32_t Strength;
    uint32_t Defense;
    uint32_t Speed;
} CharacterAttributes;

enum class CharacterType : uint32_t
{
    DEFAULT,
    PLAYER,
    NPC,
    COUNT,
};

enum class DirectionType : uint32_t
{
    NONE,
    UP,
    DOWN,
    LEFT,
    RIGHT,
    COUNT,
};

constexpr uint32_t HEALTH_BAR_HEIGHT    =  8U;

constexpr uint32_t PLAYER_WIDTH         = 16U;
constexpr uint32_t PLAYER_HEIGHT        = 24U;
constexpr uint32_t FRAMES_PER_DIRECTION =  4U;

constexpr uint32_t NPC_WIDTH            = 18U;
constexpr uint32_t NPC_HEIGHT           = 26U;

extern const string CharacterTypeString[static_cast<uint32_t>(CharacterType::COUNT)];

extern const string CharacterDefaultName[static_cast<uint32_t>(CharacterType::COUNT)];

#endif //__CHARACTER_DATA_HPP__
