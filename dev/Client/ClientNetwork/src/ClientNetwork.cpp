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
 * @brief Receive and decode data from server
 *
 * @param data Data to receive
 * @param maxNumberOfElement Maximum number of element that can be received in case of an array
 * @return Number of data received
 */
uint32_t ClientNetwork::receive(void *data, const uint32_t maxNumberOfElement)
{
    uint32_t numberOfDataReceived = 0;

    _Packet.clear();

    if (_Server.receive(_Packet) != Socket::Done)
    {
        throw runtime_error("Failed to receive data from server.");
    }
    else
    {
        /* Manage message type */
        uint32_t    packetReceived;
        MessageType messageTypeReceived;

        _Packet >> packetReceived;
        messageTypeReceived = static_cast<MessageType>(packetReceived);

        if (messageTypeReceived == MessageType::DATA)
        {
            while ((numberOfDataReceived < maxNumberOfElement) && (_Packet >> static_cast<uint32_t *>(data)[numberOfDataReceived]))
            {
                numberOfDataReceived++;
            }
        }
        else if (messageTypeReceived == MessageType::STRING)
        {
            while ((numberOfDataReceived < maxNumberOfElement) && (_Packet >> static_cast<string *>(data)[numberOfDataReceived]))
            {
                numberOfDataReceived++;
            }
        }
        else if (messageTypeReceived == MessageType::STATUS)
        {
            uint32_t gameStatusReceived;
            _Packet >> gameStatusReceived;
            *static_cast<uint32_t *>(data) = gameStatusReceived;

            numberOfDataReceived++;
        }
        else if (messageTypeReceived == MessageType::INPUT_EVENTS)
        {
            static_cast<inputEvents *>(data)->deserialize(_Packet);
        }
        else if (messageTypeReceived == MessageType::OUTPUT_COMMANDS)
        {
            static_cast<outputCommands *>(data)->deserialize(_Packet);
        }
    }

    return numberOfDataReceived;
}

ClientNetwork::~ClientNetwork()
{
    _Server.disconnect();
}
