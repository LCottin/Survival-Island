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

    acceptClient();
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
 * @brief Create a character from a given packet
 *
 * @param packet Received data
 * @return shared_ptr<Character> Character created
 */
void ServerNetwork::createCharacter(Packet &packet, shared_ptr<Player> player, shared_ptr<vector<shared_ptr<NPC>>> NPClist) const
{
    string   characterName;
    uint32_t characterType;
    uint32_t characterColor;
    static int i = 0;

    packet >> characterName >> characterType >> characterColor;

    if (static_cast<CharacterType>(characterType) == CharacterType::PLAYER)
    {
        player = make_shared<Player>(characterName);
    }
    else if (static_cast<CharacterType>(characterType) == CharacterType::NPC)
    {
        NPClist->at(i) = make_shared<NPC>(characterName, NPCColorsString[characterColor]);
        i++;
    }
}

/**
 * @brief wait for a character to connect
 *
 * @param player Player of the game
 * @param NPClist List of all NPCs
 */
void ServerNetwork::waitForCharacter(shared_ptr<Player> player, shared_ptr<vector<shared_ptr<NPC>>> NPClist)
{
    const string confirmation = "OK";

    _Packet.clear();

    if (_Client.receive(_Packet) != Socket::Done)
    {
        throw runtime_error("Failed to receive data from client.");
    }

    createCharacter(_Packet, player, NPClist);

    _Packet.clear();
    _Packet << confirmation;

    if (_Client.send(_Packet) != Socket::Done)
    {
        throw runtime_error("Failed to send data to client.");
    }
}

ServerNetwork::~ServerNetwork()
{
    _Client.disconnect();
    _Listener.close();
}
