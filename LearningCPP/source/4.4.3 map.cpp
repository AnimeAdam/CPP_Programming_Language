#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <complex>
#include <memory>
#include <cstddef>

using namespace std; // make std members visible

map<string, int> phone_book{
	{ "David Hume",123456 },
	{ "Karl Popper",234567 },
	{ "Ber trand Ar thur William Russell",345678 }
};

int get_number(const string& s)
{
	return phone_book[s];
}
// In other words, subscripting a map is essentially the lookup we called get_number()


int main()
{
	int q(0);



	cin >> q; //just to stop at the command window
}