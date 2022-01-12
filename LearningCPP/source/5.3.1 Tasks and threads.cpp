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

/*void f(); // function
struct F 
{ // function object
	void operator()(); // F’s call operator (§3.4.3)
};*/
/*void user()
{
	thread t1{ f }; // f() executes in separate thread
	thread t2{ F() }; // F()() executes in separate thread
	t1.join(); // wait for t1
	t2.join(); // wait for t2
}*/

// Consider possible implementations of the
// tasks x(a function) and X(a function object) :
void x() { cout << "Hello "; }
struct X {
	void operator()() { cout << "Parallel World!\n"; }
};
// This is an example of a bad error: Here, x and X() 
// each use the object cout without any form of synchronization.
// The resulting output would be unpredictable and could vary between different executions
// of the program because the order of execution of the individual operations in the two tasks is
// not defined

int main()
{
	int q(0);

	x();
	X();

	cin >> q; //just to stop at the command window
}