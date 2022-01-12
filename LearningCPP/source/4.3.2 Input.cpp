#include <iostream>
#include <vector>
#include <list>
#include <complex>
#include <memory>
#include <cstddef>

using namespace std; // make std members visible

// This reads a number, such as 1234, from the standard input into the 
// integer variable i and a floating point number, such as 12.34e5, 
// into the double - precision floating - point variable d
void f()
{
	int i;
	cin >> i; // read an integer into i
	double d;
	cin >> d; // read a double-precision floating-point number into d
}

// Often, we want to read a sequence of characters.
// A convenient way of doing that is to read into a string.For example :
void hello()
{
	cout << "Please enter your name\n";
	string str;
	cin >> str;
	cout << "Hello, " << str << "!\n";
}
// If you type in Eric the response is: Hello, Eric!

void hello_line()
{
	cout << "Please enter your name\n";
	string str;
	getline(cin, str);
	cout << "Hello, " << str << "!\n";
}
// With this program, the input Eric Bloodaxe yields the desired output:
// Hello, Eric Bloodaxe!



int main()
{
	int q(0);



	cin >> q; //just to stop at the command window
}