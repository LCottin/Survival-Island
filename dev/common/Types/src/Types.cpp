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
    packet << isClientStopped;
    packet << movePlayerUp;
    packet << movePlayerDown;
    packet << movePlayerLeft;
    packet << movePlayerRight;
    packet << playerAttack;
    packet << mousePosition.x;
    packet << mousePosition.y;
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
    packet >> isClientStopped;
    packet >> movePlayerUp;
    packet >> movePlayerDown;
    packet >> movePlayerLeft;
    packet >> movePlayerRight;
    packet >> playerAttack;
    packet >> mousePosition.x;
    packet >> mousePosition.y;
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
    packet << playerCommand.weaponPosition.x;
    packet << playerCommand.weaponPosition.y;

    for (size_t i = 0; i < NPCsCommands.size(); i++)
    {
        packet << NPCsCommands[i].isAlive;
        packet << NPCsCommands[i].health;
        packet << NPCsCommands[i].hasMoved;
        packet << NPCsCommands[i].position.x;
        packet << NPCsCommands[i].position.y;
        packet << NPCsCommands[i].weaponPosition.x;
        packet << NPCsCommands[i].weaponPosition.y;
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
    packet >> playerCommand.weaponPosition.x;
    packet >> playerCommand.weaponPosition.y;

    for (size_t i = 0; i < NPCsCommands.size(); i++)
    {
        packet >> NPCsCommands[i].isAlive;
        packet >> NPCsCommands[i].health;
        packet >> NPCsCommands[i].hasMoved;
        packet >> NPCsCommands[i].position.x;
        packet >> NPCsCommands[i].position.y;
        packet >> NPCsCommands[i].weaponPosition.x;
        packet >> NPCsCommands[i].weaponPosition.y;
    }
}
