#include <iostream>
#include <vector>
#include <string>
#include <list>
#include <map>
#include <unordered_map>
#include <complex>
#include <memory>
#include <algorithm>
#include <iterator>
#include <cstddef>
#include <thread>
#include <mutex>
#include <future>
#include <queue>
#include <numeric>
#include <chrono>
#include <forward_list>
#include <type_traits>

using namespace std; // make std members visible
using namespace std::chrono; // see §35.2

template<typename Forward_iterator, typename T, typename Compare>
pair<Forward_iterator, Forward_iterator>
equal_range(Forward_iterator first, Forward_iterator last, const T& val, Compare cmp);
// Given a sorted sequence [first:last), equal_range() will return the pair representing the subsequence
// that matches the predicate cmp

class Record
{
public:
	Record(string name);
	~Record();
	string name();

private:
	string rName;
};

Record::Record(string name)
{
	rName = name;
}

Record::~Record()
{
}

string Record::name()
{

}

//  We can use that to search in a sorted sequence of Records:
auto rec_eq = [](const Record& r1, const Record& r2) { return r1.name < r2.name; };// compare names
void f(const vector<Record>& v) // assume that v is sorted on its "name" field
{
	auto er = std::equal_range(v.begin(), v.end(), Record{ "Reg" }, rec_eq);
	for (auto p = er.first; p != er.second; ++p) // print all equal records
		cout << *p; // assume that << is defined for Record	
}

// The make_pair() function makes it easy to create a pair without explicitly mentioning its type(§34.2.4.1).For example :
void f(vector<string>& v)
{
	auto pp = make_pair(v.begin(), 2); // pp is a pair<vector<str ing>::iterator,int>
									   // ...
}

// If you need more than two elements (or less), you can use tuple (from <utility>; §34.2.4.2)
tuple<string, int, double> t2("Sild", 123, 3.14); // the type is explicitly specified
auto t = make_tuple(string("Herring"), 10, 1.23); // the type is deduced
												  // t is a tuple<str ing,int,double>
string s = get<0>(t); // get first element of tuple
int x = get<1>(t);
double d = get<2>(t);

int main()
{
	int q = 0;



	cin >> q; //just to stop at the command window
}