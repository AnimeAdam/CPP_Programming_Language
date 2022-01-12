#include <iostream>
#include <vector>
#include <list>
#include <complex>
#include <memory>
#include <cstddef>

using namespace std; // make std members visible
using size_t = unsigned int;
// The actual type named size_t is implementation-dependent, 
// so in another implementation size_t may be an unsigned long

// It is very common for a parameterized type to provide an alias for 
// types related to their template arguments.For example :

template<typename T>
class Vector 
{
public:
	using value_type = T;
	// ...
};

template<typename C>
using Element_type = typename C::value_type;
template<typename Container>
void algo(Container& c)
{
	Vector<Element_type<Container>> vec; // keep results here
										 // ...
};

// The aliasing mechanism can be used to define a new template by 
// binding some or all template arguments. For example :
template<typename Key, typename Value>
class Map {
	// ...
};
template<typename Value>
using String_map = Map<string, Value>;
String_map<int> m; // m is a Map<str ing,int>

int main()
{
	int q(0);



	cin >> q; //just to stop at the command window
}