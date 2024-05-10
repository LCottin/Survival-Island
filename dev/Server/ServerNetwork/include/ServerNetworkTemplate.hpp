#ifndef __SERVERNETWORK_TEMPLATE_HPP__
#define __SERVERNETWORK_TEMPLATE_HPP__

#include "ServerNetwork.hpp"

/**
 * @brief Send data to client
 *
 * @param data Array of data to send
 * @param sizeOfArray size max of the array
 */
template<typename T>
void ServerNetwork::sendData(const T *data, const uint32_t sizeOfArray)
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
}

/**
 * @brief Send a structure to client
 *
 * @param data structure to send
 */
template<typename T>
void ServerNetwork::sendStructure(const T *data)
{
    _Packet.clear();

    data->serialize(_Packet);

    if (_Client.send(_Packet) != Socket::Done)
    {
        throw runtime_error("Failed to send structure to client.");
    }
}

/**
 * @brief Receive a structure from client
 *
 * @param data structure to receive
 */
template<typename T>
void ServerNetwork::receiveStructure(T *data)
{
    _Packet.clear();

    if (_Client.receive(_Packet) != Socket::Done)
    {
        throw runtime_error("Failed to receive data from client.");
    }

    data->deserialize(_Packet);
}

/**
 * @brief Receive data from client
 *
 * @param data data received
 * @param sizeOfArray size max of the array
 * @return uint32_t number of data received
 */
template<typename T>
uint32_t ServerNetwork::receiveData(T *data, const uint32_t sizeOfArray)
{
    uint32_t numberOfDataReceived = 0;

    _Packet.clear();

    if (_Client.receive(_Packet) != Socket::Done)
    {
        throw runtime_error("Failed to receive data from client.");
    }

    while ((numberOfDataReceived < sizeOfArray) && (_Packet >> data[numberOfDataReceived]))
    {
        numberOfDataReceived++;
    }

    return numberOfDataReceived;
}

#endif
