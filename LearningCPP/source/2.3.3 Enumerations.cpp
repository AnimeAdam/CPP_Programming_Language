#include <iostream>
using namespace std;

// By default, an enum class has only assignment, initialization, and comparisons 
// (e.g., == and <; §2.2.2) defined.
enum class Color { red, blue, green };
enum class Traffic_light { green, yellow, red };
//The class after the enum specifies that an enumeration is strongly typed and that its enumerators
//are scoped.Being separate types, enum classes help prevent accidental misuses of constants.

Traffic_light& operator++(Traffic_light& t);

int main()
{
	int q(0);

	Color col = Color::red; // Note that enumerators (e.g., red) are in the scope of their 
							// enum class, so that they can be used repeatedly in different enum 
							// classes without confusion For example, Color::red is Color’s red 
							// which is different from Traffic_light::red.
	Traffic_light light = Traffic_light::red;

	Traffic_light next = ++light; // next becomes Traffic_light::green, light is the argument

	//Color x = red; // error : which red?
	//Color y = Traffic_light::red; // error : that red is not a Color
	//int i = Color::red; // error : Color ::red is not an int
	//Color c = 2; // error : 2 is not a Color
	Color z = Color::red; // OK
		
	cin >> q; //just to stop at the command window
}

Traffic_light& operator++(Traffic_light& t)
// prefix increment: ++
{
	switch (t) {
	case Traffic_light::green: return t = Traffic_light::yellow;
	case Traffic_light::yellow: return t = Traffic_light::red;
	case Traffic_light::red: return t = Traffic_light::green;
	}
}