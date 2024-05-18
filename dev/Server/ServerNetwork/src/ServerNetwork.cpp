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
 * @brief Receive and decode data from client
 *
 * @param data Data to receive
 * @param maxNumberOfElement Maximum number of element that can be received in case of an array
 * @return Number of data received
 */
uint32_t ServerNetwork::receive(void *data, const uint32_t maxNumberOfElement)
{
    uint32_t numberOfDataReceived = 0;

    _Packet.clear();

    if (_Client.receive(_Packet) != Socket::Done)
    {
        throw runtime_error("Failed to receive data from client.");
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

    return numberOfDataReceived;
}

ServerNetwork::~ServerNetwork()
{
    _Client.disconnect();
    _Listener.close();
}
