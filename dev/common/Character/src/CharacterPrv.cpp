#include "CharacterPrv.hpp"

const string CharacterTypeString[static_cast<uint32_t>(CharacterType::COUNT)] =
{
    [static_cast<uint32_t>(CharacterType::DEFAULT)] = "Characters",
    [static_cast<uint32_t>(CharacterType::PLAYER)]  = "Players",
    [static_cast<uint32_t>(CharacterType::NPC)]     = "NPCs",
};
