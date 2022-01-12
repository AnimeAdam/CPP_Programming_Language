#include <iostream>
#include "Vector.h"

using namespace std; // make std members visible

int main()
{
	int q(0);

	Vector v(2);

	cin >> q; //just to stop at the command window
}

void f(Vector& v)
{
	// ...
	try { // exceptions here are handled by the handler defined below
		v[v.size()] = 7; // try to access beyond the end of v
	}
	catch (out_of_range) { // oops: out_of_range error
							// ... handle range error ...
	}
	// ...
}
// We put code for which we are interested in handling exceptions into a try-block. That attempted
// assignment to v[v.siz e()] will fail.Therefore, the catch - clause providing a handler for out_of_range
// will be entered.The out_of_range type is defined in the standard library and is in fact used by some
// standard - library container access functions.
