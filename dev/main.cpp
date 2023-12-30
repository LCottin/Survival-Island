#include <iostream>

#include "Character.hpp"
#include "Player.hpp"
#include "Board.hpp"
#include "Screen.hpp"
#include "NPC.hpp"

using namespace std;
using namespace sf;

int main()
{
    Character character;
    character.sayHello();
    character.setName("John Doe");
    character.presentation();

    printf("\n\n");

    Player player;
    player.sayHello();
    player.setName("Jane Doe");
    player.presentation();

    Board board;
    shared_ptr<NPC> npc1 = make_shared<NPC>("NPC1", "red");
    shared_ptr<NPC> npc2 = make_shared<NPC>("NPC2", "green");
    shared_ptr<NPC> npc3 = make_shared<NPC>("NPC3", "blue");

    Screen screen(board, player, "My first game");
    screen.addNPC(npc1);
    screen.addNPC(npc2);
    screen.addNPC(npc3);
    screen.render();

    return 0;
}
