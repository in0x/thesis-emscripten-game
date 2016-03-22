#include "rng.h"

RNG& RNG::get()
{
    static std::shared_ptr<RNG> instance = nullptr;

    if (instance == nullptr)
    {
        instance = std::make_shared<RNG>();
    }

    return *instance;
}

RNG::RNG()
{
    std::srand(time(nullptr));
}

int RNG::randomRange(int min, int max)
{
    return min + std::rand() % (max - min);
}

int RNG::random()
{
    return std::rand();
}
