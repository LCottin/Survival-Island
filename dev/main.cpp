#include <iostream>

#include "Game.hpp"
#include "ConfigDev.hpp"
#include "ConfigUser.hpp"

using namespace std;

int main()
{
    ConfigUser::loadConfig();
    ConfigDev::loadConfig();

    Game game("LCottin");

    game.play();

    return 0;
}
