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
    string path = "../assets/images/NPC_" + _Color + ".png";
    bool load   = _Texture.loadFromFile(path);
    if (load == false)
    {
        cerr << "Error loading NPC texture" << endl;
        exit(EXIT_FAILURE);
    }
    _Sprite.setTexture(_Texture);
}
