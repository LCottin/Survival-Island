#ifndef __CONFIG_DEV_HPP__
#define __CONFIG_DEV_HPP__

#include <iostream>
#include <fstream>
#include <string>
#include <nlohmann/json.hpp>

using namespace std;
using json=nlohmann::json;

namespace ConfigDev
{
    extern string   tilesetImgPath;
    extern string   playerImgPath;
    extern string   NPCImgPath;
    extern string   knifeImgPath;
    extern string   pistolImgPath;
    extern string   fontPath;
    extern int32_t  framerateLimit;
    extern uint32_t tileSize;
    extern uint32_t imageSizeTileWidth;
    extern uint32_t imageSizeTileHeight;
    extern bool     configLoaded;

    extern void loadConfig();
}

#endif //__CONFIG_DEV_HPP__
