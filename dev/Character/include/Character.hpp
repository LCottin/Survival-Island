#ifndef __CHARACTER_HPP__
#define __CHARACTER_HPP__

#include <iostream>
#include <fstream>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <nlohmann/json.hpp>

#include "CharacterData.hpp"

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
        Vector2f            _Position;

        vector<IntRect>     _UpFrames;
        vector<IntRect>     _DownFrames;
        vector<IntRect>     _LeftFrames;
        vector<IntRect>     _RightFrames;

        vector<IntRect>   * _CurrentFrames;
        uint8_t             _CurrentFrameIndex;

        void _initAttributes(const string filename);
        json _loadFromJson(const string filename) const;

    public:
        // Constructors
        Character();
        Character(const string name);

        // Destructor
        ~Character();

        // Member functions (getters)
        string   getName()       const;
        uint32_t getAge()        const;
        uint32_t getHealth()     const;
        uint32_t getLevel()      const;
        uint32_t getExperience() const;
        uint32_t getStrength()   const;
        uint32_t getDefense()    const;
        uint32_t getSpeed()      const;
        Vector2f getPosition()   const;
        Sprite&  getSprite();
        Vector2f getScale()      const;
        bool     isAlive()       const;

        // Member functions (setters)
        void setName(const string name);
        virtual void setPosition(const Vector2f position, const bool changeFrame);
        virtual void setPosition(const float_t x, const float_t y, const bool changeFrame);

        // Member functions (others)
        void sayHello() const;
        void presentation() const;
        virtual void updateFrame(const uint32_t direction);
};

#endif // __CHARACTER_HPP__
