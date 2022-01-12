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

struct Greater_than {
	int val;
	Greater_than(int v) : val{ v } { }
	bool operator()(const pair<string, int>& r) { return r.second>val; }
};

// A map allows us to
// access its elements as a sequence of(key, value) pairs, so we can search a map<string, int>’s sequence
// for a pair<const string, int> where the int is greater than 42:
void f(map<string, int>& m)
{
	auto p = find_if(m.begin(), m.end(), Greater_than{ 42 });
	//Alternatively, we could use a lambda expression(§3.4.3) :
	int cxx = count_if(m.begin(), m.end(), [](const pair<string, int>& r) { return r.second>42; });
	// ...
}




int main()
{
	int q(0);

	cin >> q; //just to stop at the command window
}