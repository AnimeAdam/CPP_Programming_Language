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

using namespace std; // make std members visible
using namespace std::chrono; // see §35.2

// For example, we can set up two tasks to each add half of the elements of a
// vector<double> using the standard - library accumulate() (§3.4.2, §40.6) :
double accum(double* beg, double * end, double init)
// compute the sum of [beg:end) starting with the initial value init
{
	return accumulate(beg, end, init);
}

double comp2(vector<double>& v)
{
	using Task_type = double(double*, double*, double); // type of task
	packaged_task<Task_type> pt0{ accum }; // package the task (i.e., accum)
	packaged_task<Task_type> pt1{ accum };
	future<double> f0{ pt0.get_future() }; // get hold of pt0’s future
	future<double> f1{ pt1.get_future() }; // get hold of pt1’s future
	double* first = &v[0];
	thread t1{ move(pt0),first,first + v.size() / 2,0 }; // star t a thread for pt0
	thread t2{ move(pt1),first + v.size() / 2,first + v.size(),0 }; // star t a thread for pt1
																	  // ...
	return f0.get() + f1.get(); // get the results
}
// The packaged_task template takes the type of the task as its template argument (here Task_type, an
// alias for double(double?, double?, double)) and the task as its constructor argument(here, accum).
// The move() operations are needed because a packaged_task cannot be copied.

// Please note the absence of explicit mention of locks in this code: we are able to concentrate on
// tasks to be done, rather than on the mechanisms used to manage their communication.The two
// tasks will be run on separate threads and thus potentially in parallel.

int main()
{
	int q = 0;



	cin >> q; //just to stop at the command window
}