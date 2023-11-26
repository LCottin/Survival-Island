#include <iostream>

#include "Character.hpp"
#include "Player.hpp"

using namespace std;

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

    return 0;
}
