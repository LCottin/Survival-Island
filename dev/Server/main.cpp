#include <iostream>

#include "ConfigNetwork.hpp"

using namespace std;

int main()
{
    cout << "Hello from main Server" << endl;

    string configName = "localhost";
    ConfigNetwork::loadConfig(configName);

    return 0;
}
