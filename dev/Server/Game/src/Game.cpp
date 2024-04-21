#include "Game.hpp"

Game::Game()
{
    _ServerNetwork = make_unique<ServerNetwork>("localhost");
}

Game::Game(const string& configName)
{
    _ServerNetwork = make_unique<ServerNetwork>(configName);
}

void Game::play()
{
    _ServerNetwork->waitForPlayer();
}
