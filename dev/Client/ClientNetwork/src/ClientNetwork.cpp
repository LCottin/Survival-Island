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
 * @brief Wait for a confirmation that the server has received the message
 *
 */
bool ClientNetwork::_waitForConfirmation()
{
    string confirmation;

    _Packet.clear();

    if (_Server.receive(_Packet) != Socket::Done)
    {
        throw runtime_error("Failed to receive confirmation from server.");
    }

    _Packet >> confirmation;
    return (confirmation == "OK from server");
}

/**
 * @brief Send confirmation to server
 *
 */
void ClientNetwork::_sendConfirmation()
{
    const string confirmation = "OK from client";

    _Packet.clear();
    _Packet << confirmation;

    if (_Server.send(_Packet) != Socket::Done)
    {
        throw runtime_error("Failed to send confirmation to server.");
    }
}

/**
 * @brief Send current game status to server
 *
 * @param gameStatus current game status
 */
void ClientNetwork::sendGameStatus(const GameStatus *gameStatus)
{
    _Packet.clear();
    _Packet << static_cast<uint32_t>(*gameStatus);

    if (_Server.send(_Packet) != Socket::Done)
    {
        throw runtime_error("Failed to send game status to server.");
    }
}

/**
 * @brief Receive current game status from server
 *
 * @param gameStatus current game status
 */
void ClientNetwork::receiveGameStatus(GameStatus *gameStatus)
{
    uint32_t gameStatus_tmp;

    _Packet.clear();

    if (_Server.receive(_Packet) != Socket::Done)
    {
        throw runtime_error("Failed to receive game status from server.");
    }

    _Packet >> gameStatus_tmp;
    *gameStatus = static_cast<GameStatus>(gameStatus_tmp);
}

ClientNetwork::~ClientNetwork()
{
    _Server.disconnect();
}
