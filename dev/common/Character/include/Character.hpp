#ifndef __CHARACTER_HPP__
#define __CHARACTER_HPP__

#include <iostream>
#include <fstream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <nlohmann/json.hpp>

#include "CharacterPub.hpp"
#include "Weapon.hpp"

using namespace std;
using namespace sf;
using json = nlohmann::json;

class Character
{
    protected:
        bool                _IsAlive;
        string              _Name;
        CharacterType       _Type;
        CharacterAttributes _Attributes;

        Texture             _Texture;
        Sprite              _Sprite;
        Vector2u            _Size;
        Vector2u            _Scale;
        Vector2f            _Position;
        Vector2f            _PreviousPosition;
        RectangleShape      _HealthBar;
        Clock               _DamageCooldown;
        Time                _DamageTimer;

        vector<IntRect>     _UpFrames;
        vector<IntRect>     _DownFrames;
        vector<IntRect>     _LeftFrames;
        vector<IntRect>     _RightFrames;

        vector<IntRect>    *_CurrentFrames;
        uint8_t             _CurrentFrameIndex;

        unique_ptr<Weapon>  _CurrentWeapon;

        void _initCommon(const CharacterType type);
        json _loadFromJson(const CharacterType type) const;
        void _restartTimer();

    public:
        /* Constructors */
        Character();
        Character(const string &name);

        /* Destructor */
        virtual ~Character();

        /* Member functions (getters) */
        string          getName()             const;
        uint32_t        getAge()              const;
        uint32_t        getHealth()           const;
        uint32_t        getMaxHealth()        const;
        uint32_t        getLevel()            const;
        uint32_t        getExperience()       const;
        uint32_t        getStrength()         const;
        uint32_t        getDefense()          const;
        uint32_t        getSpeed()            const;
        Vector2f        getPosition()         const;
        Vector2f        getPreviousPosition() const;
        Vector2u        getScale()            const;
        Vector2u        getSize()             const;
        CharacterType   getType()             const;
        Sprite&         getSprite();
        Sprite&         getWeaponSprite();
        RectangleShape& getHealthBar();
        bool            isAlive()             const;
        bool            isCooldownElapsed()   const;

        /* Member functions (setters) */
        void setName(const string &name);
        void setAlive(const bool isAlive);
        void setHealth(const uint32_t health);
        void setPosition(const Vector2f position);
        void setPosition(const float_t x, const float_t y);

        /* Member functions (others) */
        void sayHello() const;
        void presentation() const;
        void updateHealthBar();
        bool attack(Character &defender);
        bool takeDamage(const uint32_t damage);
};

#endif // __CHARACTER_HPP__
