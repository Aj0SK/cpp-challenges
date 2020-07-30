#include <iostream>
#include <cstdint>
#include <iomanip>
#include <limits>
#include <type_traits>

using std::cout;
using std::endl;

constexpr int kLnAccuracy = 15;
constexpr int kSinAccuracy = 15;
constexpr double kPi = 3.14159;

constexpr double get_uniform(uint32_t gen, double a = 0.0, double b = 1.0)
{
    uint32_t type_max = std::numeric_limits<uint32_t>::max()-1;
    double normalized = static_cast<double>(gen)/static_cast<double>(type_max);
    return normalized * (b-a) + a;
};

// implementation https://en.wikipedia.org/wiki/Xorshift
constexpr uint32_t gen_random(uint32_t prev)
{
    uint32_t curr = prev;
    curr ^= curr << 13;
    curr ^= curr >> 17;
    curr ^= curr << 5;
    return curr;
};

constexpr double ln_fast(double x, double point = 1.0)
{
    double sum = 0, num = x-point;

    for(int i=0; i<kLnAccuracy; ++i)
    {
        double sign = 1 - 2 * (i%2);
        sum += sign * num/(i+1);
        num *= x-point;
    }

    return sum;
}

double constexpr sqrt_fast(double x)
{
    if (x < 0 || x >= std::numeric_limits<double>::infinity())
    {
        return std::numeric_limits<double>::quiet_NaN();
    }

    double curr = x, prev = 0.0;

    while(curr != prev)
    {
        double temp = 0.5 * (curr + x / curr);
        prev = curr;
        curr = temp;
    }

    return curr;
}

constexpr double sin_fast(double x)
{
    double sum = 0, a = x, b = 1, mult = 2;

    for(int i=0; i<kSinAccuracy; ++i)
    {
        double sign = 1 - 2 * (i%2);
        sum += sign*a/b;
        a *= x*x;
        b *= mult*(mult+1);
        mult += 2;
    }

    return sum;
}

constexpr double generate_normal(double u1, double u2)
{
    double first = sqrt_fast(-2.0*ln_fast(u1));
    double angle = 2.0*kPi*u2;
    double second = sin_fast(angle);

    return first * second;
}

constexpr double generate_normals(int n, int seed = 20)
{
    double sum = 0;
    uint32_t state = seed;
    for(int i=0; i<n; ++i)
    {
        double a = 0.0, b = 0.0;
        state = gen_random(state);
        a = state;
        state = gen_random(state);
        b = state;

        a = get_uniform(a);
        b = get_uniform(b);

        double x = generate_normal(a, b);
        sum += x;
    }
    return sum/static_cast<double>(n);
}

constexpr double abs_const(double x)
{
    if (x >= 0.0) return x;
    else return -x;
}

void test()
{
    constexpr double test_inf = 0.0000001;

    static_assert(abs_const(ln_fast(0.75) - (-0.28768207245)) < test_inf, "Problem with ln accuracy.");
    static_assert(abs_const(sqrt_fast(0.2) - (0.447213595)) < test_inf, "Problem with sqrt accuracy.");
    static_assert(abs_const(sin_fast(0.2) - (0.19866933079)) < test_inf, "Problem with sin accuracy.");
}

int main()
{
    test();
    constexpr double mean = generate_normals(10'000);
    cout << std::fixed << std::setprecision(10) << "Mean is " << mean << endl;
    return 0;
}
