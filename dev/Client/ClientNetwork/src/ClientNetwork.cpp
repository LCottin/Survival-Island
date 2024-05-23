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
 * @param numberOfElementReceived number of element received and decoded
 * @param maxNumberOfElement Maximum number of element that can be received in case of an array
 * @return true if successfully received from server, else false
 */
bool ClientNetwork::receive(void *data, int32_t *numberOfElementReceived, const uint32_t maxNumberOfElement)
{
    int32_t numberOfDataReceived = 0;

    _Packet.clear();
    const Socket::Status receiveStatus = _Server.receive(_Packet);

    if (receiveStatus != Socket::Done)
    {
        numberOfDataReceived = -1;
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
            while ((numberOfDataReceived < static_cast<int32_t>(maxNumberOfElement)) && (_Packet >> static_cast<uint32_t *>(data)[numberOfDataReceived]))
            {
                numberOfDataReceived++;
            }
        }
        else if (messageTypeReceived == MessageType::STRING)
        {
            while ((numberOfDataReceived < static_cast<int32_t>(maxNumberOfElement)) && (_Packet >> static_cast<string *>(data)[numberOfDataReceived]))
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
        else if (messageTypeReceived == MessageType::SERVER_STOP)
        {
            static_cast<outputCommands *>(data)->deserialize(_Packet);
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

    if (numberOfElementReceived != nullptr)
    {
        *numberOfElementReceived = numberOfDataReceived;
    }

    return (receiveStatus == Socket::Status::Done);
}

ClientNetwork::~ClientNetwork()
{
    _Server.disconnect();
}
