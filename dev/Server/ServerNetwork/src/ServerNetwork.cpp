#include "ServerNetwork.hpp"
#include "ConfigNetwork.hpp"
#include "Character.hpp"
#include "Player.hpp"
#include "NPC.hpp"

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
 * @brief Accept an incoming connection
 *
 */
void ServerNetwork::acceptClient()
{
    if (_Listener.accept(_Client) != Socket::Done)
    {
        throw runtime_error("Failed to accept client.");
    }
}

/**
 * @brief Wait for a confirmation that the client has received the message
 *
 */
bool ServerNetwork::_waitForConfirmation()
{
    string confirmation;

    _Packet.clear();

    if (_Client.receive(_Packet) != Socket::Done)
    {
        throw runtime_error("Failed to receive confirmation from client.");
    }

    _Packet >> confirmation;
    return (confirmation == "OK from client");
}

/**
 * @brief Send confirmation to client
 *
 */
void ServerNetwork::_sendConfirmation()
{
    const string confirmation = "OK from server";

    _Packet.clear();
    _Packet << confirmation;

    if (_Client.send(_Packet) != Socket::Done)
    {
        throw runtime_error("Failed to send confirmation to client.");
    }
}

/**
 * @brief Send a NPC to client
 *
 * @param npc NPC to send
 */
void ServerNetwork::sendNPC(const NPC &npc)
{
    _Packet.clear();

    _Packet << npc.getName() << npc.getColor();

    if (_Client.send(_Packet) != Socket::Done)
    {
        throw runtime_error("Failed to send NPC to client.");
    }
}

/**
 * @brief Send current game status to client
 *
 * @param gameStatus current game status
 */
void ServerNetwork::sendGameStatus(const GameStatus *gameStatus)
{
    _Packet.clear();
    _Packet << static_cast<uint32_t>(*gameStatus);

    if (_Client.send(_Packet) != Socket::Done)
    {
        throw runtime_error("Failed to send game status to client.");
    }
}

/**
 * @brief Receive current game status from client
 *
 * @param gameStatus current game status
 */
void ServerNetwork::receiveGameStatus(GameStatus *gameStatus)
{
    uint32_t gameStatus_tmp;

    _Packet.clear();

    if (_Client.receive(_Packet) != Socket::Done)
    {
        throw runtime_error("Failed to receive game status from client.");
    }

    _Packet >> gameStatus_tmp;
    *gameStatus = static_cast<GameStatus>(gameStatus_tmp);
}

ServerNetwork::~ServerNetwork()
{
    _Client.disconnect();
    _Listener.close();
}
