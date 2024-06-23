# Survival-Island

## Description

You find yourself stranded on ***Survival-Island***, a mysterious place filled with strangers and hidden dangers. With limited resources and no clear path home, your primary goal is to survive and uncover the secrets of the island.

## Features

### Exploration and Survival

Navigate through the map.

### Dynamic NPC Interactions

Engage with non-player characters (NPCs) scattered throughout the island.

### Quest System

TBD

### Character Progression and Customization

TBD

### Quests

TBD

### Parameters

In the file *userConfig.json*, you can configure parameters to customize you experience. Commentary fields shall no be changed.
Among the parameters, you can modify:

- **windowTitle**: title of the screen to render the game.
- **difficulty**: a number between 1 (easy) and 3 (hard).

## How to run the game

- Clone this repository:
- Create build directory: ***mkdir -p build***
- Navigate to the build directory: ***cd build***
- Create the Makefile: ***cmake ..***
- Compile the source code: ***make***
- Run: ***./Survival-Island***
- Enjoy your adventure!

## Dependencies

- [SFML Library](https://opengameart.org/users/buch): responsible for all displaying functionalities.
- [json](https://github.com/nlohmann/json): responsible for managing JSON files.

## Credits

Images are originally taken from the following sources but may be modified (resized, scaled) to suit the game needs.

- Map: [Buch](https://opengameart.org/users/buch)
- Player : [sogomn](https://opengameart.org/users/sogomn)
- NPC : [Buch](https://opengameart.org/users/buch)
- Knife and Pistol : [ghostbytedev](https://opengameart.org/users/ghostbytedev)

## Contribution guideline

Contributions from the community to enhance the Survival-Island game and make it a more engaging and enjoyable experience for players worldwide are very welcome. Whether you are a developer, designer, writer, tester, or passionate gamer, your contributions are valuable and appreciated.

### Code Contributions

Fork the repository, create a new branch, and submit pull requests with your enhancements, bug fixes, or new features.

### Asset Creation

Design and create artwork, graphics, sound effects, music, or other multimedia assets to enrich the game's visuals and audio experience.
Ensure that all assets adhere to licensing requirements and compatibility with the game engine (SFML).

### Testing and Feedback

Playtest the game, report bugs, provide feedback, and suggest improvements to gameplay mechanics, controls, user interface, and overall player experience.

### Documentation and Localization

Update existing documentation, create new guides, tutorials, and resources to help players understand the game mechanics, controls, quests, and other features.
Translate game content, user interface elements, and documentation into different languages to make Survival-Island accessible to a global audience.

### Licensing

Respect copyright, licensing agreements, and intellectual property rights when submitting contributions, using third-party assets, or incorporating external libraries and resources.

## License

This repository is under the [MIT License](https://opensource.org/licenses/MIT).

Copyright &copy; 2023-2024 LCottin

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
