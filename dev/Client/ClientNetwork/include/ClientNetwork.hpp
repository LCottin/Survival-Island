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

        template<typename T>
        uint32_t receiveData(T *data, const uint32_t sizeOfArray);

        template<typename T>
        void receiveStructure(T *data);

        template<typename T>
        void sendData(const T *data, const uint32_t sizeOfArray);

        template<typename T>
        void sendStructure(const T *data);

        void receiveGameStatus(GameStatus *gameStatus);
        void sendGameStatus(const GameStatus *gameStatus);

        ~ClientNetwork();
};

#include "ClientNetworkTemplate.hpp"

#endif
