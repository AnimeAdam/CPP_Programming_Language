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
#include <numeric>
#include <chrono>

using namespace std; // make std members visible
using namespace std::chrono; // see §35.2

void do_work() {
	for (int f = 0; f < 1000000000; f++)
	int i = 0;
}

int main()
{
	int q = 0;

	auto t0 = high_resolution_clock::now();
	do_work();
	auto t1 = high_resolution_clock::now();
	cout << duration_cast<milliseconds>(t1-t0).count() << "msec\n";

	cin >> q; //just to stop at the command window
}
// The clock returns a time_point (a point in time).
// Subtracting two time_points gives a duration (a period of time)
// Various clocks give their results in various units of time (the clock I used measures
// nanoseconds), so it is usually a good idea to convert a duration into a known unit.
// That’s what duration_cast does

