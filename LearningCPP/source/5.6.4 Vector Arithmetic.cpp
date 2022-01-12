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
#include <valarray>

using namespace std; // make std members visible
using namespace std::chrono; // see §35.2

template<typename T>
class valarray {
	// ...
};

// The usual arithmetic operations and the most common mathematical functions are supported for valarrays.For example :
void f(valarray<double>& a1, valarray<double>& a2)
{
	valarray<double> a = a1*3.14 + a2 / a1; // numer ic array operators *, +, /, and =
	a2 += a1*3.14;
	a = abs(a);
	double d = a2[7];
	// ...
}




int main()
{
	int q = 0;



	cin >> q; //just to stop at the command window
}