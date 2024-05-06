#ifndef __CLIENTNETWORK_TEMPLATE_HPP__
#define __CLIENTNETWORK_TEMPLATE_HPP__

#include "ClientNetwork.hpp"

/**
 * @brief Send data to server
 *
 * @param data Array of data to send
 * @param sizeOfArray size max of the array
 */
template<typename T>
void ClientNetwork::sendData(const T *data, const uint32_t sizeOfArray)
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
}

/**
 * @brief Receive data from server
 *
 * @param data data received
 * @param sizeOfArray size max of the array
 * @return uint32_t number of data received
 */
template<typename T>
uint32_t ClientNetwork::receiveData(T *data, const uint32_t sizeOfArray)
{
    uint32_t numberOfDataReceived = 0;

    _Packet.clear();

    if (_Server.receive(_Packet) != Socket::Done)
    {
        throw runtime_error("Failed to receive data from server.");
    }

    while ((numberOfDataReceived < sizeOfArray) && (_Packet >> data[numberOfDataReceived]))
    {
        numberOfDataReceived++;
    }

    return numberOfDataReceived;
}

#endif
