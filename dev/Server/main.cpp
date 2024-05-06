#include <iostream>

#include "ConfigDev.hpp"
#include "ConfigUser.hpp"
#include "ConfigNetwork.hpp"
#include "Game.hpp"

using namespace std;

int main()
{
    string configName = "localhost";
    ConfigDev::loadConfig();
    ConfigUser::loadConfig();
    ConfigNetwork::loadConfig("localhost");

    Game game(configName);
    game.play();

    return 0;
}
