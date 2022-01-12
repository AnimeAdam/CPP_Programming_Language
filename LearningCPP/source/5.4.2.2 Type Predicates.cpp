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

using namespace std; // make std members visible
using namespace std::chrono; // see §35.2

bool b1 = is_arithmetic<int>(); // yes, int is an arithmetic type
bool b2 = is_arithmetic<string>(); // no, std::string is not an arithmetic type

template<typename Scalar>
class complex {
	Scalar re, im;
public:
	static_assert(Is_arithmetic<Scalar>(), "Sorry, I only support complex of arithmetic types");
	// ...
};

// To improve readability compared to using the standard library directly, I defined a type function:
template<typename T>
constexpr bool Is_arithmetic()
{
	return std::is_arithmetic<T>::value;
}

int main()
{
	int q = 0;



	cin >> q; //just to stop at the command window
}