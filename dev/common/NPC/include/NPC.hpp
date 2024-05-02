#ifndef __NPC_HPP__
#define __NPC_HPP__

#include "Character.hpp"
#include "NPCPub.hpp"

class NPC: public Character
{
    private:
        string _Color;

        void _initNPC();

    public:
        /* Constructors */
        NPC();
        NPC(const string &name);
        NPC(const string &name, const string &color);

        /* Member functions (setters) */

        /* Member functions (getters) */
        string getColor() const;

        /* Member functions (others) */
};

#endif
