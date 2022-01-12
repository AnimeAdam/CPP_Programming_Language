#include <iostream>
#include <vector>
#include <list>
#include <complex>

using namespace std; // make std members visible

template<typename Container, typename Value> 
Value sum(const Container& c, Value v)
// This sum() is a simplified version of the standard-library accumulate()
{
	for (auto x : c)
		v += x;
	return v;
}

// The Value template argument and the function argument v are there to allow 
// the caller to specify the type and initial value of the accumulator
// (the variable in which to accumulate the sum) : look at user()


int main()
{
	int q(0);



	cin >> q; //just to stop at the command window
}

void user(std::vector<int>& vi, std::list<double>& ld, std::vector<complex<double>>& vc)
{
	int x = sum(vi, 0); // the sum of a vector of ints (add ints)
	double d = sum(vi, 0.0); // the sum of a vector of ints (add doubles)
	double dd = sum(ld, 0.0); // the sum of a list of doubles
	auto z = sum(vc, complex<double>{}); // the sum of a vector of complex<double>
										 // the initial value is {0.0,0.0}
}

// The point of adding ints in a double would be to gracefully handle a 
// number larger than the largest int.Note how the types of the template 
// arguments for sum<T, V> are deduced from the function arguments.
// Fortunately, we do not need to explicitly specify those types