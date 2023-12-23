#include <iostream>

#include "Character.hpp"
#include "Player.hpp"
#include "Board.hpp"
#include "Screen.hpp"

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
    Screen screen(board, "My first game");
    screen.render();

    return 0;
}
