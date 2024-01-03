#ifndef __CONFIG_USER_HPP__
#define __CONFIG_USER_HPP__

#include <iostream>
#include <fstream>
#include <string>
#include <nlohmann/json.hpp>

#include "ConfigData.hpp"

using namespace std;
using json = nlohmann::json;

namespace ConfigUser
{
    extern string         windowTitle;
    extern GameDifficulty difficulty;

    extern bool loadConfig();
}

#endif //__CONFIG_USER_HPP__
