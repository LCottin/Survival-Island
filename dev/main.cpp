#include <iostream>

#include "Game.hpp"

#include "ConfigDev.hpp"
#include "ConfigUser.hpp"

int main()
{
    ConfigUser::loadConfig();
    ConfigDev::loadConfig();

    Game game("Lcottin");

    game.play();

    return 0;
}
