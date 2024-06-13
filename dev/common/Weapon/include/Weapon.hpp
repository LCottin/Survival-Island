#ifndef __WEAPON_HPP__
#define __WEAPON_HPP__

#include <iostream>
#include <fstream>
#include <SFML/Graphics.hpp>
#include <nlohmann/json.hpp>

#include "WeaponPub.hpp"
#include "Character.hpp"

using namespace std;
using namespace sf;
using json = nlohmann::json;

class Character;

class Weapon
{
    protected:
        WeaponAttributes _Attributes;
        string           _Name;
        WeaponType       _Type;

        Texture          _Texture;
        Sprite           _Sprite;
        Vector2f         _Size;
        Vector2f         _Scale;
        Vector2f         _Position;
        Vector2f         _PreviousPosition;

        IntRect          _UpFrame;
        IntRect          _DownFrame;
        IntRect          _LeftFrame;
        IntRect          _RightFrame;
        IntRect         *_CurrentFrame;

        json _initCommon(const WeaponType type);
        json _loadFromJson(const WeaponType type) const;

    public:
        /* Constructors */
        Weapon();
        Weapon(const string &name);

        /* Destructor */
        virtual ~Weapon() = 0;

        uint32_t   getDamage()           const;
        uint32_t   getAccuracy()         const;
        uint32_t   getRange()            const;
        uint32_t   getDurability()       const;
        Vector2f   getPosition()         const;
        Vector2f   getPreviousPosition() const;
        Vector2f   getScale()            const;
        Vector2f   getSize()             const;
        WeaponType getType()             const;
        Sprite&    getSprite();

        virtual bool isUsable() const;

        virtual void updatePosition(const Vector2f &playerPosition, const DirectionType &frameDirection, const uint32_t frameIndex) = 0;
        virtual bool performAttack(Character &target) = 0;

        void setPosition(const Vector2f position);
        void setPosition(const float_t x, const float_t y);
        void setFrame(const DirectionType direction);
};

#endif
