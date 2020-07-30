#include <iostream>
#include <cstdint>
#include <iomanip>
#include <limits>

using std::cout;
using std::endl;

// implementation https://en.wikipedia.org/wiki/Xorshift
class RandomNumberGenerator
{
    // state
    uint32_t a = 1;
public:
    constexpr RandomNumberGenerator(uint32_t seed) : a(seed) {};
    constexpr uint32_t get()
    {
        uint32_t x = a;
        x ^= x << 13;
        x ^= x >> 17;
        x ^= x << 5;
        a = x;
        return a;
    };
    constexpr double get_uniform(double a, double b)
    {
        uint32_t gen = get();
        uint32_t type_max = std::numeric_limits<uint32_t>::max()-1;
        double normalized = static_cast<double>(gen)/static_cast<double>(type_max);
        return normalized * (b-a) + a;
    };
};

constexpr double get_mean(int n)
{
    RandomNumberGenerator rng(20);
    double sum = 0;
    for(int i=0; i<n; ++i)
    {
        sum += rng.get_uniform(0.0, 1.0);
    }
    return sum/static_cast<double>(n);
}

int main()
{
    constexpr double mean = get_mean(100000);
    cout << std::fixed << std::setprecision(5) << "Mean is " << mean << endl;
    return 0;
}
