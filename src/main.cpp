#include <iostream>

#include "Character.hpp"

using namespace std;

int main()
{
    Character character;
    character.sayHello();
    character.setName("John Doe");
    character.presentation();
    return 0;
}
