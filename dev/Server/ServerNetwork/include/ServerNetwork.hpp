#ifndef __SERVERNETWORK_HPP__
#define __SERVERNETWORK_HPP__

#include <iostream>
#include <SFML/Network.hpp>

#include "Player.hpp"
#include "NPC.hpp"

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
        void _acceptClient();
        bool _waitForConfirmation();
        void _sendConfirmation();

    public:
        ServerNetwork();
        ServerNetwork(const string &configName);

        template<typename T>
        uint32_t receiveData(T *data, const uint32_t sizeOfArray);

        template<typename T>
        void sendData(const T *data, const uint32_t sizeOfArray);

        void sendNPC(const NPC &npc);

        ~ServerNetwork();
};

#include "ServerNetworkTemplate.hpp"

#endif
