#include "NPC.hpp"

// Constructors
NPC::NPC() : Character()
{
    _Type  = CHARACTER_TYPE_NPC;
    _Name  = CharacterDefaultName[_Type];
    _Color = "blue";

    _initAttributes(CharacterTypeString[_Type]);
    _initNPC();
}

NPC::NPC(const string name) : Character(name)
{
    _Type  = CHARACTER_TYPE_NPC;
    _Color = "blue";

    _initAttributes(CharacterTypeString[_Type]);
    _initNPC();
}

NPC::NPC(const string name, const string color) : Character(name)
{
    _Type  = CHARACTER_TYPE_NPC;
    if ((color != "blue") && (color != "red") && (color != "green"))
    {
        _Color = "blue";
    }
    else
    {
        _Color = color;
    }

    _initAttributes(CharacterTypeString[_Type]);
    _initNPC();
}

void NPC::_initNPC()
{
    /* Includes color in the path of the image */
    string path = ConfigDev::NPCImgPath;
    path.insert(ConfigDev::NPCImgPath.size() - string(".png").size(), string("_") + _Color);

    bool load   = _Texture.loadFromFile(path);
    if (load == false)
    {
        cerr << "Error loading NPC texture" << endl;
        exit(EXIT_FAILURE);
    }
    _Scale = Vector2f(2.0f, 2.0f);
    _Size  = Vector2f(NPC_WIDTH * _Scale.x, NPC_HEIGHT * _Scale.y);

    _Sprite.scale(_Scale);
    _Sprite.setTexture(_Texture);
}
