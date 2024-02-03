#include "ConfigData.hpp"

const string GameDifficultyString[static_cast<uint32_t>(GameDifficulty::COUNT)]
{
    [static_cast<uint32_t>(GameDifficulty::EASY)]   = "EASY",
    [static_cast<uint32_t>(GameDifficulty::MEDIUM)] = "MEDIUM",
    [static_cast<uint32_t>(GameDifficulty::HARD)]   = "HARD",
};
