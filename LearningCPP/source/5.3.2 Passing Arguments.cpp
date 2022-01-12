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
#include <thread>
#include <mutex>
#include <future>

using namespace std; // make std members visible

void f(vector<double>& v); // function do something with v

struct F { // function object: do something with v
	vector<double>& v;
	F(vector<double>& vv) : v{ vv } { }
	void operator()(); // application operator ; §3.4.3
};



int main()
{
	int q(0);

	vector<double> some_vec{ 1,2,3,4,5,6,7,8,9 };
	vector<double> vec2{ 10,11,12,13,14 };
	thread t1{ f,some_vec }; // f(some_vec) executes in a separate thread
	thread t2{ F{ vec2 } }; // F(vec2)() executes in a separate thread
	t1.join();
	t2.join();

	cin >> q; //just to stop at the command window
}
// Obviously, F{vec2} saves a reference to the argument vector in F. F can now use that array and
// hopefully no other task accesses vec2 while F is executing.
// Passing vec2 by value would eliminate that risk.

// The initialization with {f,some_vec} uses a thread variadic template constructor that can accept
// an arbitrary sequence of arguments(§28.6). The compiler checks that the first argument can be
// invoked given the following arguments and builds the necessary function object to pass to the thread

// Thus, if F::operator()() and f() perform the same algorithm, the handling of the two tasks are
// roughly equivalent : in both cases, a function object is constructed for the thread to execute.