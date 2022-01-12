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
#include <regex>
#include <random>

using namespace std; // make std members visible
using namespace std::chrono; // see §35.2

using my_engine = default_random_engine; // type of engine
using my_distribution = uniform_int_distribution<>; // type of distribution
my_engine re{}; // the default engine
my_distribution one_to_six{ 1,6 }; // distribution that maps to the ints 1..6
auto die = bind(one_to_six, re); // make a generator
int x = die(); // roll the die: x becomes a value in [1:6]
// The standard-library function bind() makes a function object that will invoke its first argument
// (here, one_to_six) giv en its second argument(here, re) as its argument(§33.5.1).Thus a call die() is
// equivalent to a call one_to_six(re).

// The using statements makes what is being done a bit more obvious. Instead, I could just have written :
auto die = bind(uniform_int_distribution<>{1, 6}, default_random_engine{});

class Rand_int {
public:
	Rand_int(int low, int high) :dist{ low,high } { }
	int operator()() { return dist(re); } // draw an int
private:
	default_random_engine re;
	uniform_int_distribution<> dist;
};

Rand_int rnd{ 1,10 }; // make a random number generator for [1:10]
int x = rnd(); // x is a number in [1:10]



int main()
{
	int q = 0;

	Rand_int rnd{ 0,4 }; // make a unifor m random number generator
	vector<int> histogram(5); // make a vector of size 5
	for (int i = 0; i != 200; ++i)
		++histogram[rnd()]; // fill histogram with the frequencies of numbers [0:4]
	for (int i = 0; i != mn.size(); ++i) { // write out a bar graph
		cout << i << '\t';
		for (int j = 0; j != mn[i]; ++j) cout << '*';
		cout << endl;
	}

	cin >> q; //just to stop at the command window
}