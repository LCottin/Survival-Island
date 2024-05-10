#include "CharacterPub.hpp"

const string CharacterDefaultName[static_cast<uint32_t>(CharacterType::COUNT)] =
{
    [static_cast<uint32_t>(CharacterType::DEFAULT)] = "Default",
    [static_cast<uint32_t>(CharacterType::PLAYER)]  = "Player",
    [static_cast<uint32_t>(CharacterType::NPC)]     = "NPC",
};
