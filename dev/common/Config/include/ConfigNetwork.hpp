#ifndef __CONFIG_NETWORK_HPP__
#define __CONFIG_NETWORK_HPP__

#include <iostream>
#include <fstream>
#include <string>
#include <nlohmann/json.hpp>

using namespace std;
using json=nlohmann::json;

namespace ConfigNetwork
{
    extern uint16_t port;
    extern string   ipAddress;
    extern bool     configLoaded;

    extern void loadConfig(const string &configName);
}

#endif //__CONFIG_NETWORK_HPP__
