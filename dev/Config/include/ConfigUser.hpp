#ifndef __CONFIG_USER_HPP__
#define __CONFIG_USER_HPP__

#include <iostream>
#include <fstream>
#include <string>
#include <nlohmann/json.hpp>
#include <SFML/Window.hpp>
#include <unordered_map>

#include "ConfigData.hpp"

using namespace std;
using namespace sf;
using json = nlohmann::json;

namespace ConfigUser
{
    extern string         windowTitle;
    extern GameDifficulty difficulty;
    extern Keyboard::Key  upKey;
    extern Keyboard::Key  downKey;
    extern Keyboard::Key  leftKey;
    extern Keyboard::Key  rightKey;
    extern Keyboard::Key  pauseKey;

    extern bool loadConfig();
}

#endif //__CONFIG_USER_HPP__
