#include "ClientNetwork.hpp"
#include "ConfigNetwork.hpp"

ClientNetwork::ClientNetwork()
{
    _ConfigName = "localhost";

    _initCommon();
}

ClientNetwork::ClientNetwork(const string &configName)
{
    _ConfigName = configName;

    _initCommon();
}

void ClientNetwork::_initCommon()
{
    _Port      = ConfigNetwork::port;
    _IPAddress = ConfigNetwork::ipAddress;

    if (_Server.connect(_IPAddress, _Port) != Socket::Done)
    {
        throw invalid_argument("Failed to connect to server.");
    }
}

void ClientNetwork::connectPlayer(const Player& player)
{
    Packet packet;
    packet << player.getName();

    _Server.send(packet);
}

ClientNetwork::~ClientNetwork()
{
    _Server.disconnect();
}
