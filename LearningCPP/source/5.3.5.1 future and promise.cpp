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
#include <queue>

using namespace std; // make std members visible
using namespace std::chrono; // see §35.2

struct X
{
	int i = 0;
};
future<X> fx;
// If we have a future<X> called fx, we can get() a value of type X from it:
X v = fx.get(); // if necessary, wait for the value to get computed
// If the value isn’t there yet, our thread is blocked until it arrives
// If the value couldn’t be computed, get() might throw an exception
// (from the system or transmitted from the task from which we were
// trying to get() the value).

// If you have a promise and need to send a result of type X to a future, you can do one of two
// things: pass a value or pass an exception.For example :
void f(promise<X>& px) // a task: place the result in px
{
	// ...
	try {
		X res;
		// ... compute a value for res ...
		px.set_value(res);
	}
	catch (...) { // oops: couldn’t compute res
				  // pass the exception to the future’s thread:
		px.set_exception(current_exception());
	}
}

// To deal with an exception transmitted through a future, the caller of get() must be prepared to
// catch it somewhere.For example :
void g(future<X>& fx) // a task: get the result from fx
{
	// ...
	try {
		X v = fx.get(); // if necessary, wait for the value to get computed
						 // ... use v ...
	}
	catch (...) { // oops: someone couldn’t compute v
				  // ... handle error ...
	}
}

int main()
{
	int q = 0;



	cin >> q; //just to stop at the command window
}