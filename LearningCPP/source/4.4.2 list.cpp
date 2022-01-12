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

list<Entry> phone_book = {
	{ "David Hume",123456 },
	{ "Karl Popper",234567 },
	{ "Bertrand Ar thur William Russell",345678 }
};

int get_number(const string& s)
{
	for (const auto& x : phone_book)
		if (x.name == s)
			return x.number;
	return 0; // use 0 to represent "number not found"
}
// The search for s starts at the beginning of the list and proceeds until s is found or the end of
// phone_book is reached

// Using iterators explicitly, we can – less elegantly – write the
// get_number() function like this:
int get_number(const string& s)
{
	for (auto p = phone_book.begin(); p != phone_book.end(); ++p)
		if (p->name == s)
			return p->number;
	return 0; // use 0 to represent "number not found"
}
// In fact, this is roughly the way the terser and less error-prone range-for loop is implemented by the compiler

// Adding elements to a list and removing elements from a list is easy:
void f(const Entry& ee, list<Entry>::iterator p, list<Entry>::iterator q)
{
	phone_book.insert(p, ee); // add ee before the element referred to by p
	phone_book.erase(q); // remove the element referred to by q
}
// For a more complete description of insert() and erase(), see §31.3.7.

int main()
{
	int q(0);



	cin >> q; //just to stop at the command window
}

