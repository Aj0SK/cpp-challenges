
#include <cstdio>
#include <memory>

struct A {};
struct B {};

template<typename...>
struct AllOf {};

template<typename T, typename... ArgT>
struct AllOf<T, ArgT...> {
 using First = T;
 using Remaining = AllOf<ArgT...>;
};

template <typename T>
struct Not {
 using Arg = T;
};

template <typename T, typename Statement>
struct IsTrue {
};

template <typename... ArgT, typename Statement>
struct IsTrue<AllOf<ArgT...>, Statement> {
 // TODO
 static constexpr bool value = true;
};

template <typename Statement>
struct IsTrue<AllOf<>, Statement> {
 static constexpr bool value = false;
};

template <typename A, typename B>
struct Implies {};

int main() {
 printf("%s\n", IsTrue<AllOf<>, A>::value ? "true" : "false");
 printf("%s\n", IsTrue<AllOf<Implies<A, B>, A>, B>::value ? "true" : "false");
}
