#ifndef __SERVERNETWORK_HPP__
#define __SERVERNETWORK_HPP__

#include <iostream>
#include <SFML/Network.hpp>

#include "Player.hpp"
#include "NPC.hpp"
#include "Types.hpp"

using namespace std;
using namespace sf;

class ServerNetwork
{
    private:
        uint16_t    _Port;
        string      _ConfigName;
        TcpListener _Listener;
        TcpSocket   _Client;
        Packet      _Packet;

        void _initCommon();
        bool _waitForConfirmation();
        void _sendConfirmation();

    public:
        ServerNetwork();
        ServerNetwork(const string &configName);

        void acceptClient();

        bool receive(void *data, int32_t *numberOfElementReceived = nullptr, const uint32_t maxNumberOfElement = 1U);

        template<MessageType T>
        bool send(const void *data, const uint32_t numberOfElement = 1U);

        ~ServerNetwork();
};

#include "ServerNetworkTemplate.hpp"

#endif
