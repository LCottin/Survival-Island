#include "Game.hpp"
#include "ConfigUser.hpp"
#include "ConfigDev.hpp"
#include "Random.hpp"

Game::Game(const string& configName)
{
    _ServerNetwork = make_unique<ServerNetwork>(configName);
    _Board         = make_shared<Board>();
    _NPCs          = make_shared<vector<shared_ptr<NPC>>>(10U * static_cast<uint32_t>(ConfigUser::difficulty));

    for (size_t i = 0; i < _NPCs->size(); i++)
    {
        _NPCs->at(i) = make_shared<NPC>("NPC_" + to_string(i), NPCColorsString[Random::getRandomInteger(0, static_cast<uint32_t>(NPCColors::COUNT) - 1U)]);
    }

    _Board->computeVertices(ConfigDev::tileSize, Vector2u(ConfigDev::imageSizeTileWidth, ConfigDev::imageSizeTileHeight));

    _sendInitData();
}

/**
 * @brief Send data to initialise the client
 *
 */
void Game::_sendInitData()
{
    /* Create a player after the name receive from client */
    string playerName;
    _ServerNetwork->receiveData<string>(&playerName, 1);
    _Player = make_shared<Player>(playerName);

    /* Send all NPCs to client */
    const uint32_t NPCSize = _NPCs->size();
    _ServerNetwork->sendData<uint32_t>(&NPCSize, 1U);

    for (size_t i = 0; i < NPCSize; i++)
    {
        _ServerNetwork->sendNPC(*(_NPCs->at(i)));
    }
}

/**
 * @brief Main loop of the game on server side
 *
 */
void Game::play()
{
    cout << "Server ready to play" << endl;
}
