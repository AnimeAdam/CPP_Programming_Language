#include <iostream>
#include "Vector.h"
using namespace std; // make std members visible

int main()
{
	int q(0);



	cin >> q; //just to stop at the command window
}

void test()
{
	try {
		Vector v(-27);
	}
	catch (std::length_error) {
		// handle negative size
	}
	catch (std::bad_alloc) {
		// handle memory exhaustion
	}
}