#ifndef __CONFIG_DATA_HPP__
#define __CONFIG_DATA_HPP__

#include <string>

using namespace std;

enum class GameDifficulty : uint32_t
{
    EASY,
    MEDIUM,
    HARD,
    COUNT,
};

extern const string GameDifficultyString[static_cast<uint32_t>(GameDifficulty::COUNT)];

#endif //__CONFIG_DATA_HPP__
