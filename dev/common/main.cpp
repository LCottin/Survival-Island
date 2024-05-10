#include <iostream>
#include "Board.hpp"
#include "Character.hpp"
#include "NPC.hpp"
#include "Player.hpp"
#include "ConfigDev.hpp"
#include "ConfigUser.hpp"
#include "ConfigNetwork.hpp"

using namespace std;
using namespace sf;

int main()
{
    /* Getting files */
    ConfigDev::loadConfig();
    ConfigUser::loadConfig();
    ConfigNetwork::loadConfig("localhost");

    /* Testing Board class */
    cout << "\nTesting Board class" << endl;
    Board board;
    cout << "Width in Tiles: " << board.getWidthInTile() << endl;
    cout << "Height in Tiles: " << board.getHeightInTile() << endl;
    cout << "Dimension in Tiles: " << board.getDimensionInTile().x << "x" << board.getDimensionInTile().y << endl;

    /* Assuming there's a function to compute vertices based on some parameters */
    board.computeVertices(32, Vector2u(256, 256));
    const VertexArray& vertices = board.getVertices();
    cout << "Vertices count: " << vertices.getVertexCount() << endl;

    /* Testing Character class */
    cout << "\nTesting Character class" << endl;
    Character character("John");
    character.sayHello();
    character.presentation();
    character.setPosition(Vector2f(10.f, 10.f));
    cout << "Position: (" << character.getPosition().x << ", " << character.getPosition().y << ")" << endl;
    cout << "Is alive? " << (character.isAlive() ? "Yes\n" : "No\n") << endl;
    cout << "Current Health: " << character.getHealth() << endl;
    character.takeDamage(10U);
    cout << "After taking 10 damage, current health: " << character.getHealth() << endl;

    /* Testing NPC class */
    cout << "\nTesting NPC class" << endl;
    string NPC_wrong_name = "NPC1";
    string NPC_valid_name = "NPC_1";
    try
    {
        NPC npc1(NPC_wrong_name, "red");
    }
    catch(const exception& e)
    {
        cout << "Failed to init an NPC called " << NPC_wrong_name <<endl;
        cout << "Creating another one called " << NPC_valid_name << endl;
    }
    NPC npc(NPC_valid_name, "green");
    cout << "NPC created successfully" << endl;
    npc.sayHello();
    npc.presentation();

    /* Testing Player class */
    cout << "\nTesting Player class" << endl;
    Player player("Alice");
    player.sayHello();
    player.presentation();
    player.setMoney(100);
    cout << "Money: " << player.getMoney() << endl;
    player.setPosition(Vector2f(20.f, 20.f), true);
    cout << "Position: (" << player.getPosition().x << ", " << player.getPosition().y << ")" << endl;

    /* Testing attack functionality between characters */
    Character enemy("Enemy");
    cout << "Enemy Health before attack: " << enemy.getHealth() << endl;
    player.attack(enemy);
    cout << "Enemy Health after attack: " << enemy.getHealth() << endl;

    /* Testing NPC interactions */
    npc.sayHello();
    player.sayHello();
    npc.presentation();
    player.presentation();
    npc.setPosition(Vector2f(30.f, 30.f));
    cout << "NPC Position: (" << npc.getPosition().x << ", " << npc.getPosition().y << ")" << endl;
    cout << "Player Position: (" << player.getPosition().x << ", " << player.getPosition().y << ")" << endl;
    player.attack(npc);
    cout << "NPC Health after player attack: " << npc.getHealth() << endl;

    /* Test Player's movement and previous position */
    Vector2f previousPos = player.getPosition();
    player.setPosition(Vector2f(40.f, 40.f), true);
    cout << "Previous Position: (" << previousPos.x << ", " << previousPos.y << ")" << endl;
    cout << "New Position: (" << player.getPosition().x << ", " << player.getPosition().y << ")" << endl;

    return 0;
}
