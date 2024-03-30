#ifndef __QUEST_HPP__
#define __QUEST_HPP__

#include <string>
#include <shared_ptr>

#include "Player.hpp"

using namespace std;

class Quest
{
    protected:
        string             _Name;
        shared_ptr<Player> _Player;
        uint32_t           _CurrentStep;

        _initCommon();
        
    public:
        Quest();
        Quest(const string &name);

        bool start(shared_ptr<Player> player);
        void end();
        void abort();
        virtual void reward() const;
};

#endif
