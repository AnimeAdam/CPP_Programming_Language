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

// the standard algorithm find looks for a value in a sequence and returns an iterator to the
// element found :
bool has_c0(const string& s, char c) // does s contain the character c?
{
	auto p = find(s.begin(), s.end(), c);
	if (p != s.end())
		return true;
	else
		return false;
}

// An equivalent, shorter, definition of has_c() is:
bool has_c1(const string& s, char c) // does s contain the character c?
{
	return find(s.begin(), s.end(), c) != s.end();
}

// Assuming that we would like to modify the locations found, we pass a non - const string :
vector<string::iterator> find_all(string& s, char c) // find all occurrences of c in s
{
	vector<string::iterator> res;
	for (auto p = s.begin(); p != s.end(); ++p)
		if (*p == c)
			res.push_back(p);
	return res;
}
// We iterate through the string using a conventional loop, moving the iterator p forward one element
// at a time using ++ and looking at the elements using the dereference operator ?.

// Iterators and standard algorithms work equivalently on every standard container for which their use
// makes sense.Consequently, we could generalize find_all() :
template<typename C, typename V>
vector<typename C::iterator> find_all(C& c, V v) // find all occurrences of v in c
{
	vector<typename C::iterator> res;
	for (auto p = c.begin(); p != c.end(); ++p)
		if (?p == v)
			res.push_back(p);
	return res;
}
// The typename is needed to inform the compiler that C’s iterator is supposed to be a type and not a
// value of some type, say, the integer 7

// We can hide this implementation detail by introducing a type
// alias(§3.4.5) for Iterator:
template<typename T>
using Iterator<T> = typename T::iterator;
template<typename C, typename V>
vector<Iterator<C>> find_all(C& c, V v) // find all occurrences of v in c
{
	vector<Iterator<C>> res;
	for (auto p = c.begin(); p != c.end(); ++p)
		if (?p == v)
			res.push_back(p);
	return res;
}

void test()
{
	string m{ "Mary had a little lamb" };
	for (auto p : find_all(m, 'a')) // p is a string::iterator
		if (*p != 'a')
		{cerr << "string bug!\n";
	list<double> ld{ 1.1, 2.2, 3.3, 1.1 };
	for (auto p : find_all(ld, 1.1))
		if (*p != 1.1)
			cerr << "list bug!\n";
	vector<string> vs{ "red", "blue", "green", "green", "orange", "green" };
	for (auto p : find_all(vs, "green"))
		if (*p != "green")
			cerr << "vector bug!\n";
	for (auto p : find_all(vs, "green"))
		*p = "ver t";
}

void test2()
{
	string m{ "Mary had a little lamb" };
	for (auto p : find_all(m, 'a'))
		if (*p != 'a')
			cerr << "a bug!\n";
}

int main()
{
	int q(0);



	cin >> q; //just to stop at the command window
}