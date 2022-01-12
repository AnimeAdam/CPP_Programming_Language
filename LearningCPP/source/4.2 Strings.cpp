#include <iostream>
#include <vector>
#include <list>
#include <complex>
#include <memory>
#include <cstddef>

using namespace std; // make std members visible

// The string type provides a variety of useful string operations, such as concatenation.
string compose(const string& name, const string& domain)
{
	return name + '@' + domain;
}

// Here, addr is initialized to the character sequence dmr@bell?labs.com
auto addr = compose("dmr", "bell?labs.com");

// In many applications, the most common form of concatenation is adding 
// something to the end of a string.This is directly supported by the += operation
void m2(string& s1, string& s2)
{
	s1 = s1 + '\n'; // append newline
	s2 += '\n'; // append newline
}

// Among other useful features, it provides the ability to manipulate substrings
string name = "Niels Stroustrup";
void m3()
{
	string s = name.substr(6, 10); // s = "Stroustrup"
	name.replace(0, 5, "nicholas"); // name becomes "nicholas Stroustrup"
	name[0] = toupper(name[0]); // name becomes "Nicholas Stroustrup"
}

// Naturally, strings can be compared against each other and against string literals
string incantation;
void respond(const string& answer)
{
	if (answer == incantation) {
		// perfor m magic
	}
	else if (answer == "yes") {
		// ...
	}
	// ...
}

int main()
{
	int q(0);

	

	cin >> q; //just to stop at the command window
}