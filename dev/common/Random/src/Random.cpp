#include "Random.hpp"

random_device Random::_Rd;

/**
 * @brief Returns a random integer between min and max
 *
 * @param min Minimum value to return
 * @param max Maximum value to return
 * @return Random integer generated
 */
int32_t Random::getRandomInteger(const int32_t min, const int32_t max)
{
    mt19937 gen(_Rd());
    uniform_int_distribution<int32_t> distribution(min, max);
    return distribution(gen);
}

/**
 * @brief Returns a random float between min and max
 *
 * @param min Minimum value to return
 * @param max Maximum value to return
 * @return Random float generated
 */
float_t Random::getRandomFloat(const float_t min, const float_t max)
{
    mt19937 gen(_Rd());
    uniform_real_distribution<float_t> distribution(min, max);
    return distribution(gen);
}
