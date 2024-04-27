#include "NPC.hpp"
#include "NPCPrv.hpp"
#include "Random.hpp"
#include "ConfigDev.hpp"

/* Constructors */
NPC::NPC() : Character()
{
    _Name  = CharacterDefaultName[static_cast<uint32_t>(_Type)];
    _Color = NPCColorsString[Random::getRandomInteger(0, static_cast<uint32_t>(NPCColors::COUNT) - 1U)];

    _initCommon(CharacterType::NPC);
    _initNPC();
}

NPC::NPC(const string &name) : Character(name)
{
    _Color = NPCColorsString[Random::getRandomInteger(0, static_cast<uint32_t>(NPCColors::COUNT) - 1U)];

    _initCommon(CharacterType::NPC);
    _initNPC();
}

NPC::NPC(const string &name, const string &color) : Character(name)
{
    /* Makes sure color exists among available ones */
    bool colorExists = false;
    for (size_t i = 0; i < static_cast<uint32_t>(NPCColors::COUNT); i++)
    {
        if (NPCColorsString[i] == color)
        {
            colorExists = true;
        }
    }

    if (colorExists == true)
    {
        _Color = color;
    }
    else
    {
        _Color = NPCColorsString[Random::getRandomInteger(0, static_cast<uint32_t>(NPCColors::COUNT) - 1U)];
    }

    _initCommon(CharacterType::NPC);
    _initNPC();
}

void NPC::_initNPC()
{
    /* Includes color in the path of the image */
    string path = ConfigDev::NPCImgPath;
    path.insert(ConfigDev::NPCImgPath.size() - strlen(".png"), string("_") + _Color);

    if (_Texture.loadFromFile(path) == false)
    {
        throw runtime_error("Error loading NPC texture");
    }

    _Scale = Vector2u(2U, 2U);
    _Size  = Vector2u(NPCSize::WIDTH * _Scale.x, NPCSize::HEIGHT * _Scale.y);

    _Sprite.scale(static_cast<Vector2f>(_Scale));
    _Sprite.setTexture(_Texture);
}
