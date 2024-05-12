#include <iostream>

#include "Game.hpp"
#include "ConfigDev.hpp"
#include "ConfigUser.hpp"
#include "ConfigNetwork.hpp"

using namespace std;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        cerr << "Usage: " << argv[0] << " <network_configuration_name>" << endl;
        return -1;
    }

    string configName = string(argv[1]);
    ConfigDev::loadConfig();
    ConfigUser::loadConfig();
    ConfigNetwork::loadConfig(configName);

    Game game("LCottin", configName);

    game.play();

    return 0;
}
