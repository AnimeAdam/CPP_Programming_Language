#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <unordered_map>
#include <complex>
#include <memory>
#include <cstddef>

using namespace std; // make std members visible

unordered_map<string, int> phone_book{
	{ "David Hume",123456 },
	{ "Karl Popper",234567 },
	{ "Bertrand Ar thur William Russell",345678 }
};

// As for a map, we can subscript an unordered_map:
int get_number(const string& s)
{
	return phone_book[s];
}

int main()
{
	int q(0);



	cin >> q; //just to stop at the command window
}