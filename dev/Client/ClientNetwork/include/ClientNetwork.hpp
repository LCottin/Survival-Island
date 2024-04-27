#ifndef __CLIENTNETWORK_HPP__
#define __CLIENTNETWORK_HPP__

#include <iostream>

#include "Character.hpp"
#include "SFML/Network.hpp"

using namespace std;
using namespace sf;

class ClientNetwork
{
    private:
        uint16_t  _Port;
        string    _IPAddress;
        string    _ConfigName;
        TcpSocket _Server;
        Packet    _Packet;

        void _initCommon();

    public:
        ClientNetwork();
        ClientNetwork(const string &configName);

        string receiveData();
        void sendData()     const;
        void connectCharacter(const Character& character);

        ~ClientNetwork();
};

#endif
