#include <iostream>

#include "Game.hpp"
#include "ConfigDev.hpp"
#include "ConfigUser.hpp"
#include "ConfigNetwork.hpp"
#include "ClientNetwork.hpp"

using namespace std;

int main()
{
    ConfigDev::loadConfig();
    ConfigUser::loadConfig();
    ConfigNetwork::loadConfig("localhost");

    Player player("LCottin");

    ClientNetwork clientNetwork("localhost");
    clientNetwork.connectPlayer(player);

    Game game("LCottin");

    game.play();

    return 0;
}
