#include <ctime>
#include <memory>
#include <random>

// Guarantees that rng is seeded when a numbers is generated
class RNG
{
public:
    RNG();
    int randomRange(int min, int max);
    int random();

    static RNG& get();
};
