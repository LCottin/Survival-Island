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

    _acceptClient();
}

/**
 * @brief Accept an incoming connection
 *
 */
void ServerNetwork::_acceptClient()
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

    // _waitForConfirmation();
}

/**
 * @brief Send data to server
 *
 * @param data Array of data to send
 * @param sizeOfArray size max of the array
 */
void ServerNetwork::sendData(const string *data, const uint32_t sizeOfArray)
{
    _Packet.clear();

    for (size_t i = 0; i < sizeOfArray; i++)
    {
        _Packet << data[i];
    }

    if (_Client.send(_Packet) != Socket::Done)
    {
        throw runtime_error("Failed to send data to client.");
    }

    // _waitForConfirmation();
}

/**
 * @brief Send data to server
 *
 * @param data Array of data to send
 * @param sizeOfArray size max of the array
 */
void ServerNetwork::sendData(const uint32_t *data, const uint32_t sizeOfArray)
{
    _Packet.clear();

    for (size_t i = 0; i < sizeOfArray; i++)
    {
        _Packet << data[i];
    }

    if (_Client.send(_Packet) != Socket::Done)
    {
        throw runtime_error("Failed to send data to client.");
    }

    // _waitForConfirmation();
}

/**
 * @brief Receive data from server
 *
 * @param data data received
 * @param sizeOfArray size max of the array
 * @return uint32_t number of data received
 */
uint32_t ServerNetwork::receiveData(string *data, const uint32_t sizeOfArray)
{
    uint32_t numberOfDataReceived = 0;
    string tmpData;

    _Packet.clear();

    if (_Client.receive(_Packet) != Socket::Done)
    {
        throw runtime_error("Failed to receive data from client.");
    }

    // _sendConfirmation();

    for (size_t i = 0; i < sizeOfArray; i++)
    {
        data[i].clear();
    }

    while ((numberOfDataReceived < sizeOfArray) && (_Packet >> data[numberOfDataReceived]))
    {
        numberOfDataReceived++;
    }

    return numberOfDataReceived;
}

/**
 * @brief Receive data from server
 *
 * @param data data received
 * @param sizeOfArray size max of the array
 * @return uint32_t number of data received
 */
uint32_t ServerNetwork::receiveData(uint32_t *data, const uint32_t sizeOfArray)
{
    uint32_t numberOfDataReceived = 0;
    _Packet.clear();

    if (_Client.receive(_Packet) != Socket::Done)
    {
        throw std::runtime_error("Failed to receive data from client.");
    }

    // _sendConfirmation();

    while ((numberOfDataReceived < sizeOfArray) && (_Packet >> data[numberOfDataReceived]))
    {
        numberOfDataReceived++;
    }

    return numberOfDataReceived;
}

ServerNetwork::~ServerNetwork()
{
    _Client.disconnect();
    _Listener.close();
}
