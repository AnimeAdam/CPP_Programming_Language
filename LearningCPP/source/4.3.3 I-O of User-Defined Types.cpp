#include <iostream>
#include <vector>
#include <list>
#include <complex>
#include <memory>
#include <cstddef>

using namespace std; // make std members visible

// consider a simple type Entry that we might use to
// represent entries in a telephone book :
struct Entry {
	string name;
	int number;
};

ostream& operator<<(ostream& os, const Entry& e)
{
	return os << "{\"" << e.name << "\", " << e.number << "}";
}

// The corresponding input operator is more complicated because 
// it has to check for correct formatting and deal with errors :
istream& operator>>(istream& is, Entry& e)
// read { "name" , number } pair. Note: for matted with { " " , and }
{
	char c, c2;
	if (is >> c && c == '{' && is >> c2 && c2 == '"') { // start with a { "
		string name; // the default value of a string is the empty string: ""
		while (is.get(c) && c != '"') // anything before a " is part of the name
			name += c;
		if (is >> c && c == ',') {
			int number = 0;
			if (is >> number >> c && c == '}') { // read the number and a }
				e = { name ,number }; // assign to the entry
				return is;
			}
		}
	}
	is.setf(ios_base::failbit); // register the failure in the stream
	return is;
}
// The is>>c skips whitespace by default, but is.g et(c) does not, so that this 
// Entry-input operator ignores(skips) whitespace outside the name string, but not within it



int main()
{
	int q(0);

	for (Entry ee; cin >> ee; ) // read from cin into ee
		cout << ee << '\n'; // write ee to cout
	// MUST BE WRITTEN LIKE THIS:
	// {"John Marwood Cleese", 123456}
	// {"Michael Edward Palin", 987654}

	cin >> q; //just to stop at the command window
}