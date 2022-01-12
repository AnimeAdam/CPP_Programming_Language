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

double accum(double* beg, double * end, double init)
// compute the sum of [beg:end) starting with the initial value init
{
	return accumulate(beg, end, init);
}

// To launch tasks to potentially run asynchronously, we can use async():
double comp4(vector<double>& v)
// spawn many tasks if v is large enough
{
	if (v.size()<10000) return accum(v.begin(), v.end(), 0.0);
	auto v0 = &v[0];
	auto sz = v.size();
	auto f0 = async(accum, v0, v0 + sz / 4, 0.0); // first quarter
	auto f1 = async(accum, v0 + sz / 4, v0 + sz / 2, 0.0); // second quarter
	auto f2 = async(accum, v0 + sz / 2, v0 + sz*3 / 4, 0.0); // third quarter
	auto f3 = async(accum, v0 + sz*3 / 4, v0 + sz, 0.0); // four th quar ter
	return f0.get() + f1.get() + f2.get() + f3.get(); // collect and combine the results
}



int main()
{
	int q = 0;



	cin >> q; //just to stop at the command window
}