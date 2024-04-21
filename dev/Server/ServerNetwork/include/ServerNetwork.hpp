#ifndef __SERVERNETWORK_HPP__
#define __SERVERNETWORK_HPP__

#include <iostream>
#include <SFML/Network.hpp>

#include "Player.hpp"

using namespace std;
using namespace sf;

class ServerNetwork
{
    private:
        uint16_t    _Port;
        string      _ConfigName;
        TcpListener _Listener;
        TcpSocket   _Client;

        void _initCommon();

    public:
        ServerNetwork();
        ServerNetwork(const string &configName);

        Player& createPlayer() const;
        void    waitForPlayer();
        void    receiveData()  const;
        void    sendData()     const;

        ~ServerNetwork();
};

#endif
