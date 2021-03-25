#ifndef RANDOM_ENGINE_H
#define RANDOM_ENDINE_H

#include <algorithm>
#include <random>

class RandomEngine
{
public:
    RandomEngine() {}
    static int randomInt(int a, int b);
    static float randomFloat(float a, float b);
};

#endif