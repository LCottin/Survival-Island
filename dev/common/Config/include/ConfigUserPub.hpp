#ifndef __CONFIG_USER_PUB_HPP__
#define __CONFIG_USER_PUB_HPP__

#include <string>

using namespace std;

enum class GameDifficulty : uint32_t
{
    NONE,
    EASY,
    MEDIUM,
    HARD,
    COUNT,
};

extern const string GameDifficultyString[static_cast<uint32_t>(GameDifficulty::COUNT)];

#endif //__CONFIG_USER_PUB_HPP__
