#pragma once

#define PI 3.1416
#define debug(...)   fprintf(stderr, __VA_ARGS__)
#define SUM(a,b) (a + b)
#define SQR(s)  ((s) * (s))
#define PRNT(a,b) \
  printf("value 1 = %d\n", a); \
  printf("value 2 = %d\n", b);
#define CHECK(x, ...) if ((x)) { printf(__VA_ARGS__); }
#define HASHTAG_PRINT( x ) printf_s( #x "\n" )
#define TOKENPASTE( n ) printf_s( "token" #n " = %d", token##n )
int token9 = 9;

#define WIDTH       80
#define LENGTH      ( WIDTH + 10 )

using size_t = unsigned int;

typedef unsigned long ulong;
long unsigned typedef int long ullong;
typedef int int_t, *intp_t, (&fp)(int, ulong), arr_t[10];
typedef struct { int a; int b; } S, * pS;
// the following two objects have the same type
int a1[10];
arr_t a2;
// the following two objects have the same type
pS ps1;
S* ps2;

template<typename C>
    using Iterator_type = typename C::iterator; // C’s iterator type
template<typename Iter>
    using Iterator_category = typename std::iterator_traits<Iter>::iterator_category; // Iter’s category


using Char = char;
//using Uchar = unsigned Char; // error
using Uchar = unsigned char; // OK

namespace X {
    int i, j, k;
}

void f1()
{
    int i = 0;
    using namespace X; // make names from X accessible
    i++; //local i
    j++; //X::j
    k++; 
    X::k++; //X’s k
}
void f2()
{
    using X::i;
    using X::j;
    using X::k; // hides global k
    i++;
    j++; //X::j
    k++; //X::k
}

//an unnamed namespace has an implied using-directive.
namespace  {
    int aq;
    void fd() { /* ... */ }
    int gq() { /* ... */ }
}

void UseDefines()
{
    int a = 3;
    int b = 1;
    int c = 2;

    debug("\nHello You");

    c = SUM(a,b);
    std::cout << c << std::endl;

    c = SQR(a);
    std::cout << c << std::endl;

    PRNT(a,b);

    CHECK(a, "Check this out \n");

    HASHTAG_PRINT(WOW);
    HASHTAG_PRINT("WOW");

    TOKENPASTE(9);

    std::cout << std::endl << LENGTH;
}

namespace Estd 
{
    template<class C>
    void sort(C& c)
    {
        std::sort(c.begin(), c.end());
    }

    template<class C, class Pred>
    void sort(C& c, Pred p)
    {
        std::sort(c.begin(), c.end(), p);
    }
    // ...
}