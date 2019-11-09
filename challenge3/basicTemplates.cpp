#include <iostream>
#include <vector>
#include <algorithm>
#include <typeinfo>
#include <memory>

using std::cin;
using std::cout;
using std::endl;
using std::vector;

////////////////////////////////////////////////////////////////////////////////
template <int N> struct Factorial {
    static constexpr int result = N * Factorial<N-1>::result;  
};

template <> struct Factorial<0> {
    static constexpr int result = 1;  
};

////////////////////////////////////////////////////////////////////////////////
template <int N> struct Fib {
    static constexpr int result = Fib<N-1>::result + Fib<N-2>::result;  
};

template <> struct Fib<1> {
    static constexpr int result = 0;  
};

template <> struct Fib<2> {
    static constexpr int result = 1;  
};

////////////////////////////////////////////////////////////////////////////////
template <int A, int B> struct Frac {
    static constexpr int num = A;
    static constexpr int den = B;
};

template <typename X, typename Y> struct FracMult {
    static constexpr int num = X::num * Y::num;
    static constexpr int den = X::den * Y::den;
};

////////////////////////////////////////////////////////////////////////////////
template <typename T, typename F>
void forEach(vector<T>& arg, const F& f) {
    for(T& x : arg) {
        x = f(x);
    }
}

int basicFunc(int x) {
    return x*x;
}

////////////////////////////////////////////////////////////////////////////////
template <int x, int y> struct GCD {
    static constexpr int res = GCD<std::max(x, y)%std::min(x, y), std::min(x, y)>::res;
};

template <int x> struct GCD <0, x> {
    static constexpr int res = x;
};

////////////////////////////////////////////////////////////////////////////////
template <int N, int i = N> struct FindDiv {
    static constexpr int result = (N%i==0) + FindDiv<N, i-1>::result;  
};

template <int N> struct FindDiv<N, 0> {
    static constexpr int result = 0;  
};

////////////////////////////////////////////////////////////////////////////////
template <int N> struct IsPrime {
    static const bool result = (FindDiv<N>::result == 2);
};

////////////////////////////////////////////////////////////////////////////////
template<class T>
void swap(T& a, T& b) {
    T helper(std::move(a));
    a = std::move(b); 
    b = std::move(helper);
}

////////////////////////////////////////////////////////////////////////////////
template<typename T>
int addHelper(const T& x)
{
   return 0;
}

template<>
int addHelper(const int& x)
{
   return x;
}
template<typename... ArgT>
int sumInts(ArgT... args);
template<typename T, typename... ArgT>
int sumInts(T&& t, ArgT && ... args)
{
   return addHelper(std::move(t)) + sumInts(args...);
}
template<>
int sumInts()
{
   return 0;
}

////////////////////////////////////////////////////////////////////////////////


int main()
{
    cout << Factorial<10>::result << endl;
    
    cout << Fib<5>::result << endl;
    
    cout << Frac<7, 10>::num << endl;
    
    vector<int> transform = {1, 2, 3, 4};
    forEach(transform, basicFunc);
    forEach(transform, [](int x) -> int { return x+1; });
    cout << "Printing:"; 
    for(int x : transform) {
        cout <<  " " << x;
    }
    cout << endl;
    
    using frac1 = Frac<1, 5>;
    using frac2 = Frac<2, 3>;
    using resMult = FracMult<frac1, frac2>;
    using resMult2 = FracMult<resMult, frac2>;
    cout << resMult::num << "/" << resMult::den << endl;
    cout << resMult2::num << "/" << resMult2::den << endl;
    
    cout << "gcd(10, 20) = " << GCD<10, 20>::res << endl;
    
    cout << "Number of divisors of " << 20 << " is " << FindDiv<20>::result << endl;
    
    cout << "Primality of 2: " << IsPrime<2>::result << endl;
    cout << "Primality of 10: " << IsPrime<10>::result << endl;
    cout << "Primality of 97: " << IsPrime<97>::result << endl;
    
    long long num1 = 400, num2 = 300;
    cout << "a: " << num1 << " b: " << num2 << endl;
    swap(num1, num2);
    cout << "Swapped: " << "a: " << num1 << " b: " << num2 << endl;
    
    cout << "1+2+3 = " << sumInts(1, 2, 3) << endl;
    cout << "pes+3 = " << sumInts("dog", 3) << endl;
    cout << "macka+0.0+1+2 = " << sumInts(0.0, "cat", 1, 2) << endl;
    cout << "7+8+9 = " << sumInts(std::make_unique<int>(7), std::make_unique<int>(8), std::make_unique<int>(9)) << endl;

    return 0;
}
