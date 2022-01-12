#include <iostream>
using namespace std; // make std members visible

class Vector {
private:
	double* elem; // elem points to an array of sz doubles
	int sz;
public:
	// Vector’s constructor allocates some memory on the free store (also
	// called the heap or dynamic store) using the new operator
	Vector(int s) :elem( new double[s] ), sz( s ) // constructor: acquire resources
	{
		for (int i = 0; i != s; ++i) elem[i] = 0; // initialize elements
	}
	~Vector() { delete[] elem; } // destructor: release resources
	// The destructor cleans up by freeing that memory using the delete operator 

	double& operator[](int i);
	int size() const;
};

double& Vector::operator[](int i)
{
	if (i<0 || size() <= i) throw out_of_range{ "Vector::operator[]" };
	// The throw transfers control to a handler for exceptions of type out_of_range in some function that
	// directly or indirectly called Vector::operator[](). To do that, the implementation will unwind the
	//function call stack as needed to get back to the context of that caller
	return elem[i];
}

int Vector::size() const
{
	return sz;
}

int main()
{
	int q(0);



	cin >> q; //just to stop at the command window
}

void fct(int n)
{
	Vector v(n);
	// ... use v ...
	{
		Vector v2(2*n);
		// ... use v and v2 ...
	} // v2 is destroyed here
	  // ... use v ..
} // v is destroyed here