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
 * @brief Receive and decode data from client
 *
 * @param data Data to receive
 * @param maxNumberOfElement Maximum number of element that can be received in case of an array
 * @return Number of data received
 */
bool ServerNetwork::receive(void *data, int32_t *numberOfElementReceived, const uint32_t maxNumberOfElement)
{
    int32_t numberOfDataReceived = 0;

    _Packet.clear();
    const Socket::Status receiveStatus = _Client.receive(_Packet);

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

            numberOfDataReceived++;
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

    if (numberOfElementReceived != nullptr)
    {
        *numberOfElementReceived = numberOfDataReceived;
    }

    return (receiveStatus == Socket::Done);
}

ServerNetwork::~ServerNetwork()
{
    _Client.disconnect();
    _Listener.close();
}
