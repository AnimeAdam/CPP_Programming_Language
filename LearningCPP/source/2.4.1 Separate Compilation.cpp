#include <iostream>
#include "Vector.h" // get Vector’s interface
#include <cmath> // get the the standard-librar y math function interface including sqrt()
using namespace std; // make std members visible

double sqrt_sum(Vector& v);

int main()
{
	int q(0);

	Vector v(4);

	cout << sqrt_sum(v) << endl;

	cin >> q; //just to stop at the command window
}

double sqrt_sum(Vector& v)
{
	double sum = 0;
	for (int i = 0; i != v.size(); ++i)
		sum += sqrt(v[i]); // sum of square roots
	return sum;
}