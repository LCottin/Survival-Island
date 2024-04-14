#include <iostream>

#include "Game.hpp"
#include "ConfigDev.hpp"
#include "ConfigUser.hpp"

using namespace std;

int main()
{
    ConfigDev::loadConfig();
    ConfigUser::loadConfig();

    Game game("LCottin");

    game.play();

    return 0;
}
