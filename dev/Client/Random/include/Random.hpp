#ifndef __RANDOM_HPP__
#define __RANDOM_HPP__

#include <random>

using namespace std;

class Random
{
    private:
        static random_device _Rd;

    public:
        static int32_t getRandomInteger(const int32_t min, const int32_t max);
        static float_t getRandomFloat(const float_t min, const float_t max);
};

#endif
