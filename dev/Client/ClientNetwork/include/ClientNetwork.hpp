#ifndef __CLIENTNETWORK_HPP__
#define __CLIENTNETWORK_HPP__

#include <iostream>
#include <SFML/Network.hpp>

#include "Types.hpp"

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
        bool _waitForConfirmation();
        void _sendConfirmation();

    public:
        ClientNetwork();
        ClientNetwork(const string &configName);

        uint32_t receive(void *data, const uint32_t maxNumberOfElement = 1U);

        template<MessageType T>
        void send(const void *data, const uint32_t numberOfElement = 1U);

        ~ClientNetwork();
};

#include "ClientNetworkTemplate.hpp"

#endif
