/*#include <iostream>

int main() // the minimal C++ program
{
	int q;
	std::cout << "Hello, World!\n"; //<< (‘‘put to’’)
	std::cin >> q; //just to stop at the command window
}*/

#include <iostream>
using namespace std; // make names from std visible without std:: (§2.4.2)

double square(double x) // square a double precision floating-point number
{
	return x*x;
}
void print_square(double x)
{
	cout << "the square of " << x << " is " << square(x) << "\n";
}
int main()
{
	int q;
	print_square(1.234); // print: the square of 1.234 is 1.52276
	cin >> q; //just to stop at the command window
}

// Hello world again 2