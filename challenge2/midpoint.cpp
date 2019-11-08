#include <iostream>

template<typename T>
T avg(T a, T b)
{
    T helper = (a&b) + ((a ^ b) >> 1);
    return helper + ((a ^ b)&(b>a));
}

template<typename T>
void TEST(T a, T b, T e)
{
    if (avg(a, b) != e)
    {
        std::cout << "Error: " << "avg(" << a << ", " << b << ") is not " << e  << " but " << avg(a, b) << std::endl;  
    }
}

int main()
{
    TEST(3, 5, 4);
    TEST(3, 6, 5);
    TEST(6, 3, 4);
    return 0;
}
