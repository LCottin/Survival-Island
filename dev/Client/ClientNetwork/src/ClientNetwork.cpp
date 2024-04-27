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
        throw runtime_error("Failed to connect to server.");
    }
}

/**
 * @brief Send a character to be created by server
 *
 * @param character character to send
 */
void ClientNetwork::connectCharacter(const Character& character)
{
    _Packet.clear();

    _Packet << character.getName() << static_cast<uint32_t>(character.getType());

    if (_Server.send(_Packet) != Socket::Done)
    {
        throw runtime_error("Failed to connect character.");
    }
}

/**
 * @brief Receive data from the server
 *
 * @return string Data received
 */
string ClientNetwork::receiveData()
{
    string data;

    _Packet.clear();

    if (_Server.receive(_Packet) != Socket::Done)
    {
        throw runtime_error("Failed to receive data from server.");
    }

    _Packet >> data;

    return data;
}

ClientNetwork::~ClientNetwork()
{
    _Server.disconnect();
}
