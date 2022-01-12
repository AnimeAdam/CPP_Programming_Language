#include <iostream>
using namespace std;

class Vector {
private:
	double* elem; // pointer to the elements
	int sz; // the number of elements
public:
	Vector(int s) :elem( new double[s] ), sz( s ) { } // construct a Vector, and defines how objects of type Vector are constructed.
	double& operator[](int i) { return elem[i]; } // element access: subscripting(subscript function), Access to elements is provided by a subscript function, called operator[]. It returns a reference to the appropriate element (a double&)
	int size() { return sz; }
};

double read_and_sum(int s);

int main()
{
	int q(0);

	Vector v(6); // a Vector with 6 elements

	cout << read_and_sum(6);

	cin >> q; //just to stop at the command window
}

double read_and_sum(int s)
{
	Vector v(s); // make a vector of s elements
	for (int i = 0; i != v.size(); ++i)
		cin >> v[i]; //read into elements
	double sum = 0;
	for (int i = 0; i != v.size(); ++i)
		sum += v[i]; //take the sum of the elements
	return sum;
}