#ifndef __NPC_PUB_HPP__
#define __NPC_PUB_HPP__

#include <string>

using namespace std;

enum class NPCColors : uint32_t
{
    RED,
    GREEN,
    BLUE,
    COUNT,
};

extern const string NPCColorsString[static_cast<uint32_t>(NPCColors::COUNT)];

#endif //__NPC_PUB_HPP__
