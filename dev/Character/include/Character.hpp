#ifndef __CHARACTER_HPP__
#define __CHARACTER_HPP__

#include <iostream>
#include <fstream>
#include <string>
#include <nlohmann/json.hpp>

#include "CharacterData.hpp"

using namespace std;
using json = nlohmann::json;

class Character
{
    protected:
        bool                _IsAlive;
        string              _Name;
        CharacterType       _Type;
        CharacterAttributes _Attributes;

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
        bool     isAlive()       const;

        // Member functions (setters)
        void setName(const string name);

        // Member functions (others)
        void sayHello() const;
        void presentation() const;
};

#endif // __CHARACTER_HPP__
