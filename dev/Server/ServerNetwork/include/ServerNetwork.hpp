#ifndef __SERVERNETWORK_HPP__
#define __SERVERNETWORK_HPP__

#include <iostream>
#include <SFML/Network.hpp>

#include "Character.hpp"
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

    public:
        ServerNetwork();
        ServerNetwork(const string &configName);

        void createCharacter(Packet &packet, shared_ptr<Player> player, shared_ptr<vector<shared_ptr<NPC>>> NPClist) const;
        void waitForCharacter(shared_ptr<Player> player, shared_ptr<vector<shared_ptr<NPC>>> NPClist);
        void acceptClient();
        void receiveData()  const;
        void sendData()     const;

        ~ServerNetwork();
};

#endif
