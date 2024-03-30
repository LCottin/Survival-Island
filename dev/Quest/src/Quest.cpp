#include "Quest.hpp"

Quest::Quest()
{
    _initCommon();
}

Quest::Quest(const string &name)
{
    _Name = name;
    _initCommon();
}

void Quest::_initCommon()
{
    _Player      = nullptr;
    _CurrentStep = 0;
}

/**
 * @brief Starts the quest
 *
 * @param player Player that starts the question
 * @return true if the quest is successfully started, else false
 */
bool Quest::start(shared_ptr<Player> player)
{
    if ((_Player == nullptr) || (player == nullptr))
    {
        return false;
    }

    _Player = player;
    return true;
}

/**
 * @brief Aborts the quest
 *
 */
void Quest::abort()
{
    _Player = nullptr;
}

/**
 * @brief Stops the quest and rewards the player
 *
 */
void Quest::stop()
{
    _Player = nullptr;
    reward();
}
