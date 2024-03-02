#include "Game.hpp"
#include "NPCPub.hpp"
#include "ConfigUser.hpp"
#include "Random.hpp"

Game::Game(const string &playerName)
{
    _Player = make_shared<Player>(playerName);
    _Board  = make_shared<Board>();

    _NPCs = make_shared<vector<shared_ptr<NPC>>>();
    _NPCs->resize(2U * static_cast<uint32_t>(ConfigUser::difficulty));

    for (size_t i = 0; i < _NPCs->size(); i++)
    {
        _NPCs->at(i) = make_shared<NPC>("NPC_" + to_string(i), NPCColorsString[Random::getRandomInteger(0, static_cast<uint32_t>(NPCColors::COUNT) - 1U)]);
    }

    _Screen = make_shared<Screen>(*_Board, *_Player, *_NPCs, ConfigUser::windowTitle);
}



/**
 * @brief Render the screen
 *
 */
void Game::play()
{
    _Screen->render();
}

Game::~Game()
{
}
