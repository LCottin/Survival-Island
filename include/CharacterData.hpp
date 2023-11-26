#ifndef __CHARACTERDATA_HPP__
#define __CHARACTERDATA_HPP__

#include <string>

using namespace std;

typedef struct
{
    uint32_t Age;
    uint32_t Health;
    uint32_t Level;
    uint32_t Experience;
    uint32_t Strength;
    uint32_t Defense;
    uint32_t Speed;
} CharacterAttributes;

typedef enum
{
    CHARACTER_TYPE_DEFAULT,
    CHARACTER_TYPE_COUNT,
} CharacterType;

extern const string CharacterTypeString[CHARACTER_TYPE_COUNT];

extern const string CharacterDefaultName[CHARACTER_TYPE_COUNT];

#endif // __CHARACTERDATA_HPP__
