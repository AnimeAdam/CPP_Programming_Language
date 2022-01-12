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

using namespace std; // make std members visible
using namespace std::chrono; // see §35.2

template<typename Scalar>
class complex {
public:
	complex(const Scalar& re = {}, const Scalar& im = {});
	// ...
};

// The usual arithmetic operations and the most common mathematical functions are supported for complex numbers.For example :
void f(complex<float> fl, complex<double> db)
{
	complex<long double> ld{ fl + sqrt(db) };
	db += fl*3;
	fl = pow(1 / fl, 2);
	// ...
}
// The sqrt() and pow() (exponentiation) functions are among the usual mathematical functions defined
// in <complex>.For more details, see §40.4.

int main()
{
	int q = 0;



	cin >> q; //just to stop at the command window
}