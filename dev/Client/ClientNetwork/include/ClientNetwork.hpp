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

    public:
        ClientNetwork();
        ClientNetwork(const string &configName);

        bool receive(void *data, int32_t *numberOfElementReceived = nullptr, const uint32_t maxNumberOfElement = 1U);

        template<MessageType T>
        bool send(const void *data, const uint32_t numberOfElement = 1U);

        ~ClientNetwork();
};

#include "ClientNetworkTemplate.hpp"

#endif
