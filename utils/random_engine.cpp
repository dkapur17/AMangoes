#include "random_engine.hpp"

int RandomEngine::randomInt(int a, int b)
{
    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution<> dist(a, b);
    return dist(rng);
}

float RandomEngine::randomFloat(float a, float b)
{
    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_real_distribution<> dist(a, b);
    return dist(rng);
}