#include "Types.hpp"

/**
 * @brief Serialize data
 *
 * @param packet Packet to serialize
 */
void inputEvents::serialize(Packet &packet) const
{
    packet << isGamePaused;
    packet << isWindowClosed;
    packet << movePlayerUp;
    packet << movePlayerDown;
    packet << movePlayerLeft;
    packet << movePlayerRight;
}

/**
 * @brief Deserialize data
 *
 * @param packet Packet to deserialize
 */
void inputEvents::deserialize(Packet &packet)
{
    packet >> isGamePaused;
    packet >> isWindowClosed;
    packet >> movePlayerUp;
    packet >> movePlayerDown;
    packet >> movePlayerLeft;
    packet >> movePlayerRight;
}

/**
 * @brief Serialize data
 *
 * @param packet Packet to serialize
 */
void outputCommands::serialize(Packet &packet) const
{
    packet << static_cast<uint32_t>(gameStatus);

    packet << playerCommand.isAlive;
    packet << playerCommand.health;
    packet << playerCommand.hasMoved;
    packet << playerCommand.position.x;
    packet << playerCommand.position.y;

    for (size_t i = 0; i < NPCsCommands.size(); i++)
    {
        packet << NPCsCommands[i].isAlive;
        packet << NPCsCommands[i].health;
        packet << NPCsCommands[i].hasMoved;
        packet << NPCsCommands[i].position.x;
        packet << NPCsCommands[i].position.y;
    }
}

/**
 * @brief Deserialize data
 *
 * @param packet Packet to deserialize
 */
void outputCommands::deserialize(Packet &packet)
{
    uint32_t gameStatus_tmp;
    packet >> gameStatus_tmp;
    gameStatus = static_cast<GameStatus>(gameStatus_tmp);

    packet >> playerCommand.isAlive;
    packet >> playerCommand.health;
    packet >> playerCommand.hasMoved;
    packet >> playerCommand.position.x;
    packet >> playerCommand.position.y;

    for (size_t i = 0; i < NPCsCommands.size(); i++)
    {
        packet >> NPCsCommands[i].isAlive;
        packet >> NPCsCommands[i].health;
        packet >> NPCsCommands[i].hasMoved;
        packet >> NPCsCommands[i].position.x;
        packet >> NPCsCommands[i].position.y;
    }
}
