#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "Character.hpp"
#include "Player.hpp"

using namespace std;
using namespace sf;

#define TILE_SIZE 16
#define MAP_TILE_WIDTH 80
#define MAP_TILE_HEIGHT 50
#define MAP_WIDTH (TILE_SIZE * MAP_TILE_WIDTH)
#define MAP_HEIGHT (TILE_SIZE * MAP_TILE_HEIGHT)
#define MAP_SIZE (MAP_WIDTH * MAP_HEIGHT)
#define MAP_TILE_SIZE (MAP_TILE_WIDTH * MAP_TILE_HEIGHT)

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

    RenderWindow window(VideoMode(MAP_WIDTH, MAP_HEIGHT), "SFML window");

    Texture tilesetTexture;
    tilesetTexture.loadFromFile("../assets/tileset.png");

    // Define the size of each tile in the tileset
    Vector2u tileSize(TILE_SIZE, TILE_SIZE);

    // Map size in tiles
    const int map[MAP_TILE_HEIGHT][MAP_TILE_WIDTH] =
    {
        {0, 0, 0, 0, 0, 30, 31, 32, 33 ,34 ,35 ,36 ,37 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0, },
        {0, 1, 2, 1, 0, 1, 2, 1, 0 ,1 ,2 ,1 ,0 ,1 ,2 ,1 ,0 ,1 ,2 ,1 ,0, },
        {0, 2, 1, 2, 0, 2, 1, 2, 0 ,2 ,1 ,2 ,0 ,2 ,1 ,2 ,0 ,2 ,1 ,2 ,0, },
        {0, 1, 2, 1, 0, 1, 2, 1, 0 ,1 ,2 ,1 ,0 ,1 ,2 ,1 ,0 ,1 ,2 ,1 ,0, },

        {0, 0, 0, 0, 0, 30, 31, 32, 33 ,34 ,35 ,36 ,37 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0, },
        {0, 1, 2, 1, 0, 1, 2, 1, 0 ,1 ,2,  1 ,0 ,1 ,2 ,1 ,0 ,1 ,2 ,1 ,0, },
        {0, 2, 1, 2, 0, 2, 1, 2, 0 ,2 ,1 ,2 ,0 ,2 ,1 ,2 ,0 ,2 ,1 ,2 ,0, },
        {0, 1, 2, 1, 0, 1, 2, 1, 0 ,1 ,2 ,1 ,0 ,1 ,2 ,1 ,0 ,1 ,2 ,1 ,0, },

        {0, 0, 0, 0, 0, 30, 31, 32, 33 ,34 ,35 ,36 ,37 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0, },
        {0, 1, 2, 1, 0, 1, 2, 1, 0 ,1 ,2 ,1 ,0 ,1 ,2 ,1 ,0 ,1 ,2 ,1 ,0, },
        {0, 2, 1, 2, 0, 2, 1, 2, 0 ,2 ,1 ,2 ,0 ,2 ,1 ,2 ,0 ,2 ,1 ,2 ,0, },
        {0, 1, 2, 1, 0, 1, 2, 1, 0 ,1 ,2 ,1 ,0 ,1 ,2 ,1 ,0 ,1 ,2 ,1 ,0, },

        {0, 0, 0, 0, 0, 30, 31, 32, 33 ,34 ,35 ,36 ,37 ,0 ,0 ,0 ,0 ,0 ,0 ,0 ,0, },
        {0, 1, 2, 1, 0, 1, 2, 1, 0 ,1 ,2 ,1 ,0 ,1 ,2 ,1 ,0 ,1 ,2 ,1 ,0, },
    };

    VertexArray vertices(PrimitiveType::Quads, MAP_TILE_SIZE * 4);

    for (unsigned int i = 0; i < MAP_TILE_HEIGHT; ++i)
    {  // Adjust based on your map size
        for (unsigned int j = 0; j < MAP_TILE_WIDTH; ++j) {  // Adjust based on your map size
            int tileIndex = map[i][j];

            // Calculate the position of the current tile in the vertex array
            float x = static_cast<float>(j * tileSize.x);
            float y = static_cast<float>(i * tileSize.y);

            // Populate the vertex array with the four corners of the current tile
            vertices[(i * MAP_TILE_WIDTH + j) * 4 + 0].position = Vector2f(x, y);
            vertices[(i * MAP_TILE_WIDTH + j) * 4 + 1].position = Vector2f(x + tileSize.x, y);
            vertices[(i * MAP_TILE_WIDTH + j) * 4 + 2].position = Vector2f(x + tileSize.x, y + tileSize.y);
            vertices[(i * MAP_TILE_WIDTH + j) * 4 + 3].position = Vector2f(x, y + tileSize.y);

            // Set the texture coordinates based on the tile index
            vertices[(i * MAP_TILE_WIDTH + j) * 4 + 0].texCoords = Vector2f(tileIndex * tileSize.x, 0);
            vertices[(i * MAP_TILE_WIDTH + j) * 4 + 1].texCoords = Vector2f((tileIndex + 1) * tileSize.x, 0);
            vertices[(i * MAP_TILE_WIDTH + j) * 4 + 2].texCoords = Vector2f((tileIndex + 1) * tileSize.x, tileSize.y);
            vertices[(i * MAP_TILE_WIDTH + j) * 4 + 3].texCoords = Vector2f(tileIndex * tileSize.x, tileSize.y);
        }
    }

    // Main loop
    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();
        }

        // Clear the window
        window.clear();

        // Draw the entire vertex array in one go
        window.draw(vertices, &tilesetTexture);

        // Display the content
        window.display();
    }

    return 0;
}
