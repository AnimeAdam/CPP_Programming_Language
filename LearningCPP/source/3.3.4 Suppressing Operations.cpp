#include <iostream>

using namespace std; // make std members visible

class Shape {
public:
	Shape(const Shape&) = delete; // no copy operations
	Shape& operator=(const Shape&) = delete;
	Shape(Shape&&) = delete; // no move operations
	Shape& operator=(Shape&&) = delete;
	~Shape();
	// ...
};

// When making a derived class the best thing to do is usually to delete 
// the default copy and move operations, that is, to eliminate 
// the default definitions of those two operations

// Now an attempt to copy a Shape will be caught by the compiler. If you need 
// to copy an object in a class hierarchy, write some kind of clone function



int main()
{
	int q(0);



	cin >> q; //just to stop at the command window
}