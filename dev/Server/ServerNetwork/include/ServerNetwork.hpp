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

        template<typename T>
        uint32_t receiveData(T *data, const uint32_t sizeOfArray);

        template<typename T>
        void receiveStructure(T *data);

        template<typename T>
        void sendData(const T *data, const uint32_t sizeOfArray);

        template<typename T>
        void sendStructure(const T *data);

        void sendNPC(const NPC &npc);

        void receiveGameStatus(GameStatus *gameStatus);
        void sendGameStatus(const GameStatus *gameStatus);

        ~ServerNetwork();
};

#include "ServerNetworkTemplate.hpp"

#endif
