#include <iostream>

#include "Character.hpp"
#include "Player.hpp"
#include "Board.hpp"
#include "Screen.hpp"
#include "NPC.hpp"
#include "NPCData.hpp"

#include "ConfigDev.hpp"
#include "ConfigUser.hpp"

using namespace std;
using namespace sf;

int main()
{
    ConfigUser::loadConfig();
    ConfigDev::loadConfig();

    Board board;
    Player player("LCottin");

    Screen screen(board, player, ConfigUser::windowTitle);

    vector<shared_ptr<NPC>>listNPC(2U * static_cast<uint32_t>(ConfigUser::difficulty));

    for (size_t i = 0; i < (2U * static_cast<uint32_t>(ConfigUser::difficulty)); i++)
    {
        listNPC[i] = make_shared<NPC>("NPC_" + to_string(i), NPCColorsString[Random::getRandomInteger(0, static_cast<uint32_t>(NPCColors::COUNT) - 1U)]);
        screen.addNPC(listNPC[i]);
    }

    screen.render();

    return 0;
}
