#include <iostream>
#include <complex> //for complex numbers
#include <vector> //for vectors
using namespace std;

int main() // size of fundamental data types in bytes (8 bits), they are signed by default
{
	int q(5);
	char q2('A'); //A = 

	cout << "Size of a bool = " << sizeof(bool) << " bytes\n";
	cout << "Size of a signed char = " << sizeof(char) << " bytes\n";
	cout << "Size of a unsigned char = " << sizeof(unsigned char) << " bytes\n";
	cout << "Size of a wide char = " << sizeof(wchar_t) << " bytes\n";
	cout << "Size of a UTF-16 char = " << sizeof(char16_t) << " bytes\n";
	cout << "Size of a UTF-32 char = " << sizeof(char32_t) << " bytes\n";
	cout << "Size of a signed short int = " << sizeof(short int) << " bytes\n";
	cout << "Size of a unsigned short int = " << sizeof(unsigned short int) << " bytes\n";
	cout << "Size of a signed int = " << sizeof(int) << " bytes\n";
	cout << "Size of a unsigned int = " << sizeof(unsigned int) << " bytes\n";
	cout << "Size of a signed long int = " << sizeof(long int) << " bytes\n";
	cout << "Size of a unsigned long int = " << sizeof(unsigned long int) << " bytes\n";
	cout << "Size of a signed long long int = " << sizeof(long long int) << " bytes\n";
	cout << "Size of a unsigned long long int = " << sizeof(unsigned long long int) << " bytes\n";
	cout << "Size of a signed float = " << sizeof(float) << " bytes\n";
	cout << "Size of a signed double = " << sizeof(double) << " bytes\n"; //like float for 64-bit
	cout << "Size of a signed long double = " << sizeof(long double) << " bytes\n"; //like float for 128-bit

	cout << q << " A unary minus will convert the value to " << -q;
	cout << endl << "A unary plus will convert the A to " << +q2;

	cin >> q; //just to stop at the command window
}

/*void some_function() // function that doesn’t return a value
{
	double d = 2.2; // initialize floating-point number
	int i = 7; // initialize integer
	d = d + i; //assign sum to d
	i = d*i; //assign product to i (truncating the double d*i to an int)

	 //explainations
	double d1 = 2.3; //assignment
	double d2{ 2.3 }; //assignment

	complex<double> z = 1; // a complex number with double-precision floating-point scalars
	complex<double> z2{ d1,d2 };
	complex<double> z3 = { 1,2 }; // the = is optional with { ... }
	vector<int> v{ 1,2,3,4,5,6 }; // a vector of ints

	//The = form is traditional and dates back to C, but if in doubt, 
	//use the general{}-list form(§6.3.5.2).
	//If nothing else, it saves you from conversions that lose 
	//information(narrowing conversions; §10.5) :

	/*
	int i1 = 7.2; // i1 becomes 7
	int i2{ 7.2 }; // error : floating-point to integer conversion
	int i3 = { 7.2 }; // error : floating-point to integer conversion (the = is redundant)
	*/
/*
	auto b = true; // a bool
	auto ch = 'x'; // a char
	auto i = 123; // an int
	auto d = 1.2; // a double
	//auto z = sqrt(y); // z has the type of whatever sqr t(y) returns

}*/