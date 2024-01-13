#include "NPC.hpp"

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

    _Scale = Vector2f(2.0f, 2.0f);
    _Size  = Vector2f(NPC_WIDTH * _Scale.x, NPC_HEIGHT * _Scale.y);

    _Sprite.scale(_Scale);
    _Sprite.setTexture(_Texture);
}
