#include <iostream>
#include <stdexcept>

using namespace std; // make std members visible

class Vector {
// ...
public:
Vector(int s);

Vector(const Vector& a); // copy constructor
Vector& operator=(const Vector& a); // copy assignment

Vector(Vector&& a); // move constructor
Vector& operator=(Vector&& a); // move assignment

double& operator[](int i);
int size();
private:
	double* elem; // elem points to an array of sz doubles
	int sz;
};

Vector::Vector(int s) // constructor
/*:elem( new double[s] ), sz( s )
{
}*/ //a simplier why to create a constructor
{
	if (s<0) throw length_error{ "Vector::Vector(int s)" };
	// Use the standard-library exception length_error to report a non-positive number of elements
	// because some standard - library operations use that exception to report problems of this kind
	elem = new double[s];
	sz = s;
}

Vector::Vector(Vector&& a) //move constructor
	:elem{ a.elem }, // "grab the elements" from a
	sz{ a.sz }
{
	a.elem = nullptr; // now a has no elements
	a.sz = 0;
}

double& Vector::operator[](int i)
{
	if (i<0 || size() <= i) throw out_of_range{ "Vector::operator[]" };	
	return elem[i];
}

int Vector::size()
{
	return sz;
}


int main()
{
	int q(0);



	cin >> q; //just to stop at the command window
}

Vector operator+(Vector& a, Vector& b)
{
	if (a.size() != b.size())
		throw runtime_error("Vector sizes are unequal");
	Vector res(a.size());
	for (int i = 0; i != a.size(); ++i)
		res[i] = a[i] + b[i];
	return res;
}

void f(Vector& x, Vector& y, Vector& z)
{
	Vector r(1);
	// ...
	r = x + y + z;
	// ...
}
// That would be copying a Vector at least twice 
// (one for each use of the + operator)

Vector f()
{
	Vector x(1000);
	Vector y(1000);
	Vector z(1000);
	// ...
	z = x; // we get a copy
	y = std::move(x); // we get a move
					  // ...
	return z; // we get a move
};