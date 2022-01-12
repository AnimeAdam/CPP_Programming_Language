#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <unordered_map>
#include <complex>
#include <memory>
#include <algorithm>
#include <iterator>
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

//the following sorts a vector and places a copy of each unique vector element on a list :
bool operator < (const Entry& x, const Entry& y) // less than
{
	return x.name<y.name; // order Entrys by their names
}
void f(vector<Entry>& vec, list<Entry>& lst)
{
	sort(vec.begin(), vec.end()); // use < for order
	unique_copy(vec.begin(), vec.end(), lst.begin()); // don’t copy adjacent equal elements
}

// If we wanted to place the unique elements in a new container, we could have written:
list<Entry> f(vector<Entry>& vec)
{
	list<Entry> res;
	sort(vec.begin(), vec.end());
	unique_copy(vec.begin(), vec.end(), back_inserter(res)); // append to res
	return res;
}

int main()
{
	int q(0);

	

	cin >> q; //just to stop at the command window
}