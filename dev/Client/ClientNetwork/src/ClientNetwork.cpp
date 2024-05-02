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
 * @brief Send data to server
 *
 * @param data Array of data to send
 * @param sizeOfArray size max of the array
 */
void ClientNetwork::sendData(const string *data, const uint32_t sizeOfArray)
{
    _Packet.clear();

    for (size_t i = 0; i < sizeOfArray; i++)
    {
        _Packet << data[i];
    }

    if (_Server.send(_Packet) != Socket::Done)
    {
        throw runtime_error("Failed to send data to server.");
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
uint32_t ClientNetwork::receiveData(string *data, const uint32_t sizeOfArray)
{
    uint32_t numberOfDataReceived = 0;
    string tmpData;

    _Packet.clear();

    if (_Server.receive(_Packet) != Socket::Done)
    {
        throw runtime_error("Failed to receive data from server.");
    }

    // _sendConfirmation();

    for (size_t i = 0; i < sizeOfArray; ++i)
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
uint32_t ClientNetwork::receiveData(uint32_t *data, const uint32_t sizeOfArray)
{
    uint32_t numberOfDataReceived = 0;
    _Packet.clear();

    if (_Server.receive(_Packet) != Socket::Done)
    {
        throw std::runtime_error("Failed to receive data from server.");
    }

    // _sendConfirmation();

    while ((numberOfDataReceived < sizeOfArray) && (_Packet >> data[numberOfDataReceived]))
    {
        numberOfDataReceived++;
    }

    return numberOfDataReceived;
}

ClientNetwork::~ClientNetwork()
{
    _Server.disconnect();
}
