#include "Game.hpp"
#include "ConfigUser.hpp"

Game::Game()
{
    _ServerNetwork = make_unique<ServerNetwork>("localhost");
    _NPCs          = make_shared<vector<shared_ptr<NPC>>>(10U * static_cast<uint32_t>(ConfigUser::difficulty));
}

Game::Game(const string& configName)
{
    _ServerNetwork = make_unique<ServerNetwork>(configName);
    _NPCs          = make_shared<vector<shared_ptr<NPC>>>(10U * static_cast<uint32_t>(ConfigUser::difficulty));
}

void Game::play()
{
    for (size_t i = 0; i < _NPCs->size() + 1U; i++)
    {
        _ServerNetwork->waitForCharacter(_Player, _NPCs);
    }
}
