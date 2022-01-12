#include <iostream>
#include <vector>
#include <list>
#include <complex>
#include <memory>
#include <cstddef>

using namespace std; // make std members visible

void f()
{
	cout << 10;
}

void h(int i)
{
	cout << "the value of i is ";
	cout << i;
	cout << '\n';
}
// For h(10), the output will be:
// the value of i is 10
// it can also be written as
void h2(int i)
{
	cout << "the value of i is " << i << '\n';
}

void k()
{
	int b = 'b'; // note: char implicitly converted to int
	char c = 'c';
	cout << 'a' << b << c;
}
// The integer value of the character 'b' is 98 
// (in the ASCII encoding used on the C++ implementation that I used),
// so this will output a98c

int main()
{
	int q(0);



	cin >> q; //just to stop at the command window
}