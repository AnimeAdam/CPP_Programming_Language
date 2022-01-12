#include <iostream>
#include <vector>
#include <list>
#include <complex>
#include <memory>
#include <cstddef>

using namespace std; // make std members visible

struct Entry {
	string name;
	int number;
};

ostream& operator<<(ostream& os, const Entry& e)
{
	return os << "{\"" << e.name << "\", " << e.number << "}";
}

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

// The standard - library vector does not guarantee range checking(§31.2.2).For example :
void silly(vector<Entry>& book)
{
	int i = book[book.size()].number; // book.size() is out of range
// That initialization will place some random value in i rather than giving an error
// This is undesirable, and out - of - range errors are a common problem
}

// I often use a simple range - checking adaptation of vector :
template<typename T>
class Vec : public std::vector<T> {
public:
	using vector<T>::vector; // use the constructors from vector (under the name Vec); see §20.3.5.1
	T& operator[](int i) // range check
	{
		return vector<T>::at(i);
	}
	const T& operator[](int i) const // range check const objects; §3.2.1.1
	{
		return vector<T>::at(i);
	}
};
// Vec inherits everything from vector except for the subscript operations 
// that it redefines to do range checking

// For Vec, an out-of-range access will throw an exception that the user can catch
void checked(Vec<Entry>& book)
{
	try {
		book[book.size()] = { "Joe",999999 }; // will throw an exception
											  // ...
	}
	catch (out_of_range) {
		cout << "range error\n";
	}
}
// The exception will be thrown, and then caught (§2.4.3.1, Chapter 13)

// One way to minimize surprises from uncaught exceptions is to use a main()
// with a try - block as its body.For example :
int main()
{
	int q(0);

	try {
		// your code
	}
	catch (out_of_range) {
		cerr << "range error\n";
	}
	catch (...) {
		cerr << "unknown exception thrown\n";
	}

	cin >> q; //just to stop at the command window
}
// This provides default exception handlers so that if we fail to catch some exception, an error message
// is printed on the standard error - diagnostic output stream cerr(§38.1).