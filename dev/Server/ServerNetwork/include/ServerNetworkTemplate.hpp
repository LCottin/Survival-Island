#ifndef __SERVERNETWORK_TEMPLATE_HPP__
#define __SERVERNETWORK_TEMPLATE_HPP__

#include "ServerNetwork.hpp"

/**
 * @brief Encode and send data to client
 *
 * @param data Data to send
 * @param numberOfElement Number of data to send in case of an array
 * @return true if successfully sent, else false
 */
template<MessageType T>
bool ServerNetwork::send(const void *data, const uint32_t numberOfElement)
{
    _Packet.clear();

    _Packet << static_cast<uint32_t>(T);

    if constexpr (T == MessageType::DATA)
    {
        for (size_t i = 0; i < numberOfElement; i++)
        {
            _Packet << static_cast<const uint32_t *>(data)[i];
        }
    }
    else if constexpr (T == MessageType::STRING)
    {
        const string *strArray = static_cast<const string *>(data);
        for (size_t i = 0; i < numberOfElement; i++)
        {
            _Packet << strArray[i];
        }
    }
    else if constexpr (T == MessageType::STATUS)
    {
        const uint32_t statusToSend = *static_cast<const uint32_t *>(data);
        _Packet << statusToSend;
    }
    else if constexpr (T == MessageType::SERVER_STOP)
    {
        static_cast<const outputCommands *>(data)->serialize(_Packet);
    }
    else if constexpr (T == MessageType::INPUT_EVENTS)
    {
        static_cast<const inputEvents *>(data)->serialize(_Packet);
    }
    else if constexpr (T == MessageType::OUTPUT_COMMANDS)
    {
        static_cast<const outputCommands *>(data)->serialize(_Packet);
    }

    const Socket::Status sendStatus = _Client.send(_Packet);

    return (sendStatus == Socket::Status::Done);
}

#endif
