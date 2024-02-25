#ifndef __NPC_PRV_HPP__
#define __NPC_PRV_HPP__

#include "NPCPub.hpp"

namespace NPCSize
{
    constexpr uint32_t WIDTH  = 18U;
    constexpr uint32_t HEIGHT = 26U;
}

extern const string NPCColorsString[static_cast<uint32_t>(NPCColors::COUNT)];

#endif //__NPC_PRV_HPP__
