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

// In the example in §5.3.2, I pass the arguments by non-const reference. I only do that if I expect the
// task to modify the value of the data referred to(§7.7).That’s a somewhat sneaky, but not uncommon,
// way of returning a result.A less obscure technique is to pass the input data by const reference
// and to pass the location of a place to deposit the result as a separate argument :

void f(const vector<double>& v, double* res);// take input from v; place result in *res
class F {
public:
	F(const vector<double>& vv, double* p) :v{ vv }, res{ p } { }
	void operator()(); // place result in *res
private:
	const vector<double>& v; // source of input
	double* res; // target for output
};
int main()
{
	int q(0);

	vector<double> some_vec{ 1,2,3,4,5,6,7,8,9 };
	vector<double> vec2{ 10,11,12,13,14 };
	// ...
	double res1;
	double res2;
	thread t1{ f,some_vec,&res1 }; // f(some_vec,&res1) executes in a separate thread
	thread t2{ F{ vec2,&res2 } }; // F{vec2,&res2}() executes in a separate thread
	t1.join();
	t2.join();
	cout << res1 << ' ' << res2 << '\n';

	cin >> q; //just to stop at the command window
}