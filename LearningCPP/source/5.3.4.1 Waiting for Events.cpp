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

// For simplicity, I declare the queue and the mechanism for avoiding race conditions on that
// queue global to the producer and consumer:
class Message { // object to be communicated
				// ...
};
queue<Message> mqueue; // the queue of messages
condition_variable mcond; // the var iable communicating events
mutex mmutex; // the locking mechanismvoid consumer()
{
	while (true) {
		unique_lock<mutex> lck{ mmutex }; // acquire mmutex
		while (mcond.wait(lck)) /* do nothing */; // release lck and wait;
												  // re-acquire lck upon wakeup
		auto m = mqueue.front(); // get the message
		mqueue.pop();
		lck.unlock(); // release lck
					  // ... process m ...
	}
}// Here, I explicitly protect the operations on the queue and on the condition_variable with a
// unique_lock on the mutex.Waiting on condition_variable releases its lock argument until the wait is
// over(so that the queue is non - empty) and then reacquires it.

// The corresponding producer looks like this:
void producer()
{
	while (true) {
		Message m;
		// ... fill the message ...
		unique_lock<mutex> lck{ mmutex }; // protect operations
		mqueue.push(m);
		mcond.notify_one(); // notify
	} // release lock (at end of scope)
}
// Using condition_variables supports many forms of elegant and efficient sharing, but can be rather
// tricky(§42.3.4).

int main()
{
	int q(0);

	auto t0 = high_resolution_clock::now();
	this_thread::sleep_for(milliseconds{ 20 });
	auto t1 = high_resolution_clock::now();
	cout << duration_cast<nanoseconds>(t1-t0).count() << " nanoseconds passed\n";
// Note that I didn’t even hav e to launch a thread; by default, this_thread refers to the one and only
// thread(§42.2.6).

	cin >> q; //just to stop at the command window
}