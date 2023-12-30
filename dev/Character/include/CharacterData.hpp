#ifndef __CHARACTERDATA_HPP__
#define __CHARACTERDATA_HPP__

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

typedef enum
{
    CHARACTER_TYPE_DEFAULT,
    CHARACTER_TYPE_PLAYER,
    CHARACTER_TYPE_NPC,
    CHARACTER_TYPE_COUNT,
} CharacterType;

typedef enum
{
    DIRECTION_UP,
    DIRECTION_DOWN,
    DIRECTION_LEFT,
    DIRECTION_RIGHT,
    DIRECTION_COUNT,
} DirectionType;

constexpr uint32_t HEALTH_BAR_HEIGHT    =  8U;

constexpr uint32_t FRAME_WIDTH          = 16U;
constexpr uint32_t FRAME_HEIGHT         = 24U;
constexpr uint32_t FRAMES_PER_DIRECTION =  4U;

extern const string CharacterTypeString[CHARACTER_TYPE_COUNT];

extern const string CharacterDefaultName[CHARACTER_TYPE_COUNT];

#endif // __CHARACTERDATA_HPP__
