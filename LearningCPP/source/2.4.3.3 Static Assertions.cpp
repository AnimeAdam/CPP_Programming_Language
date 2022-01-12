#include <iostream>
#include "Vector.h"
using namespace std; // make std members visible

constexpr double C = 299792.458; // km/s

int main()
{
	int q(0);

	static_assert(4 <= sizeof(int), "integers are too small"); // check integer size
	// This will write integers are too small if 4<=sizeof(int) does not hold, that is, if an int on this 
	// system does not have at least 4 bytes.We call such statements of expectations assertions.

	cin >> q; //just to stop at the command window
}

void f(double speed)
{
	constexpr double local_max = 160.0 / (60*60); //160 km/h == 160.0/(60*60) km/s
	//static_assert(speed<C, "can't go that fast"); // error : speed must be a constant
	static_assert(local_max<C, "can't go that fast"); // OK
													  // ...
}