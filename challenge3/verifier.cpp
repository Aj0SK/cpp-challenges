
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

template <typename A, typename B>
struct Implies {};

////////////////////////////////////////////////////////////////////////////////

template <typename... ArgT, typename Statement>
struct IsTrue<AllOf<ArgT...>, Statement> {
 static constexpr bool value = false;
};

////////////////////////////////////////
// modus ponens
template <typename T, typename Statement>
struct IsTrue<AllOf<T, Implies<T, Statement> >, Statement> {
 static constexpr bool value = true;
};

template <typename T, typename Statement>
struct IsTrue<AllOf<Implies<T, Statement>, T>, Statement> {
 static constexpr bool value = true;
};

template <typename Statement>
struct IsTrue<AllOf<>, Statement> {
 static constexpr bool value = false;
};

////////////////////////////////////////
//  axioms
//  A -> (B -> A)
//  A -> (B -> C) -> [(A->B) -> (A -> C)]
// (!B -> !A) -> (A -> B)

template <typename T, typename Statement1, typename Statement2>
struct IsTrue<T, Implies<Statement1, Implies<Statement1, Statement2> > > {
 static constexpr bool value = true;
};


int main() {
 printf("%s should equal false\n", IsTrue<AllOf<>, A>::value ? "true" : "false");
 printf("%s should equal true\n", IsTrue<AllOf<Implies<A, B>, A>, B>::value ? "true" : "false");
 printf("%s should equal true\n", IsTrue<AllOf<A, Implies<A, B> >, B>::value ? "true" : "false");
}
