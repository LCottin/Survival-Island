#include <iostream>

#include "ConfigNetwork.hpp"
#include "Game.hpp"

using namespace std;

int main()
{
    cout << "Hello from main Server" << endl;

    string configName = "localhost";
    ConfigNetwork::loadConfig(configName);

    Game game(configName);
    game.play();

    return 0;
}
