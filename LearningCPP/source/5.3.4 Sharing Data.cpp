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

mutex m; // controlling mutex
int sh; // shared data
void f()
{
	unique_lock<mutex> lck{ m }; // acquire mutex
	sh += 7; // manipulate shared data
} // release mutex implicitly
// The unique_lock’s constructor acquires the mutex (through a call m.lock())

class Record {
public:
	mutex rm;
	// ...
};
// It doesn’t take a genius to guess that for a Record called rec, rec.rm is a mutex that you are supposed
// to acquire before accessing the other data of rec, though a comment or a better name might have
// helped a reader

mutex m1; // controlling mutex
mutex m2; // controlling mutex
mutex m3; // controlling mutex

void f2()
{
	// ...
	unique_lock<mutex> lck1{ m1,defer_lock }; // defer_lock: don’t yet try to acquire the mutex
	unique_lock<mutex> lck2{ m2,defer_lock };
	unique_lock<mutex> lck3{ m3,defer_lock };
	// ...
	lock(lck1, lck2, lck3); // acquire all three locks
							// ... manipulate shared data ...
} // implicitly release all mutexes

// This lock() will only proceed after acquiring all its mutex arguments and will never block (‘‘go to
// sleep’’) while holding a mutex

int main()
{
	int q(0);



	cin >> q; //just to stop at the command window
}