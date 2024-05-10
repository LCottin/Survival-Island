#include <iostream>

#include "Game.hpp"
#include "ConfigDev.hpp"
#include "ConfigUser.hpp"
#include "ConfigNetwork.hpp"

using namespace std;

int main()
{
    ConfigDev::loadConfig();
    ConfigUser::loadConfig();
    ConfigNetwork::loadConfig("localhost");

    Game game("LCottin", "localhost");

    game.play();

    return 0;
}
