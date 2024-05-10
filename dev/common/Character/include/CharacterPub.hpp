#ifndef __CHARACTER_PUB_HPP__
#define __CHARACTER_PUB_HPP__

#include <string>

using namespace std;

typedef struct
{
    uint32_t Health;
    uint32_t MaxHealth;
    uint32_t Level;
    uint32_t Experience;
    uint32_t Strength;
    uint32_t Defense;
    uint32_t Speed;
    uint32_t Age;
} CharacterAttributes;

enum class CharacterType : uint32_t
{
    DEFAULT,
    PLAYER,
    NPC,
    COUNT,
};

extern const string CharacterDefaultName[static_cast<uint32_t>(CharacterType::COUNT)];

#endif //__CHARACTER_PUB_HPP__
