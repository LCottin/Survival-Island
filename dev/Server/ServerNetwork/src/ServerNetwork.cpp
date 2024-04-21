#include "ServerNetwork.hpp"
#include "ConfigNetwork.hpp"

ServerNetwork::ServerNetwork()
{
    _ConfigName = "localhost";

    _initCommon();
}

ServerNetwork::ServerNetwork(const string &configName)
{
    _ConfigName = configName;

    _initCommon();
}

void ServerNetwork::_initCommon()
{
    _Port = ConfigNetwork::port;

    _Listener.listen(_Port);
}

/**
 * @brief Wait for a player to connect
 *
 */
void ServerNetwork::waitForPlayer()
{
    Packet packet;
    string message;

    _Listener.accept(_Client);
    _Client.receive(packet);

    packet >> message;
}

ServerNetwork::~ServerNetwork()
{
    _Client.disconnect();
    _Listener.close();
}
