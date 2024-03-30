#ifndef __QUEST_PRV_HPP__
#define __QUEST_PRV_HPP__

#include <string>

enum class QuestType : uint32_t
{
    FIND_SURVIVOR,
    COUNT,
}

extern const string QuestNames[static_cast<uint32_t>(QuestType::COUNT)];

#endif; //__QUEST_PRV_HPP__
