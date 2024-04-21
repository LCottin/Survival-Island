#ifndef __CLIENTNETWORK_HPP__
#define __CLIENTNETWORK_HPP__

#include <iostream>

#include "Player.hpp"
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

        void _initCommon();

    public:
        ClientNetwork();
        ClientNetwork(const string &configName);

        void receiveData()  const;
        void sendData()     const;
        void connectPlayer(const Player& player);

        ~ClientNetwork();
};

#endif
