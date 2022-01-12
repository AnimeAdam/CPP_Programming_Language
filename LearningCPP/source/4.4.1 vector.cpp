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

// We can initialize a vector with a set of values of its element type:
vector<Entry> phone_book = {
	{ "David Hume",123456 },
	{ "Karl Popper",234567 },
	{ "Bertrand Arthur William Russell",345678 }
};

// Elements can be accessed through subscripting:
void print_book(const vector<Entry>& book)
{
for (int i = 0; i!=book.size(); ++i)
cout << book[i] << '\n';
}

// The elements of a vector constitute a range, 
// so we can use a range-for loop (§2.2.5):
void print_book2(const vector<Entry>& book)
{
	for (const auto& x : book) // for "auto" see §2.2.2
		cout << x << '\n';
}

class Shape {
public:
	virtual double center() const = 0; // pure virtual
	virtual void move(double to) = 0;

	virtual void draw() const = 0; // draw on current "Canvas"
	virtual void rotate(int angle) = 0;

	virtual ~Shape() {} // destructor
						// ...
};

// When we define a vector, we giv e it an initial size (initial number of elements):
vector<int> v1 = { 1, 2, 3, 4 }; // size is 4
vector<string> v2; // size is 0
vector<Shape*> v3(23); //size is 23; initial element value: nullptr
vector<double> v4(32, 9.9); // size is 32; initial element value: 9.9
// An explicit size is enclosed in ordinary parentheses, 
// for example, (23), and by default the elements are initialized to the element type’s 
// default value (e.g., nullptr for pointers and 0 for numbers)

void input()
{
	for (Entry e; cin >> e;)
		phone_book.push_back(e);
}
// This reads Entrys from the standard input into phone_book until either the 
// end-of-input (e.g., the end of a file) is reached or the input operation 
// encounters a format error

// A vector can be copied in assignments and initializations. For example:
vector<Entry> book2 = phone_book;
// Thus, after the initialization
// of book2, book2 and phone_book hold separate copies of every Entry in the phone book



int main()
{
	int q(0);

	print_book(phone_book);
	print_book2(phone_book);

	cin >> q; //just to stop at the command window
}