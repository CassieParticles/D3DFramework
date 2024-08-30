#include "Random.h"

Random* Random::instance = nullptr;

Random* Random::Instance()
{
    if (instance == nullptr)
    {
        instance = new Random();
    }
    return instance;
}

float Random::genRand()
{
    float returnVal = static_cast<float>(rand()) / rand.max();
    return returnVal;
}

float Random::genRand(float a, float b)
{
    float delta = b - a;
    return a + genRand() * delta;
}

int Random::genRand(int a, int b)
{
    int delta = b - a;
    return a + genRand() * delta;
}

void Random::setSeed(unsigned int seed)
{
    rand.seed(seed);
}
