#include <iostream>
using namespace std; // make std members visible

class Vector {
public:
	Vector(std::initializer_list<double>); // initialize with a list
										   // ...
// The std::initializer_list used to define the initializer-list constructor is a standard-library type
// known to the compiler : when we use a{}-list, such as{ 1,2,3,4 }, the compiler will create an object 
// of type initializer_list to give to the program. So, we can write:
// Vector v1 = { 1,2,3,4,5 }; // v1 has 5 elements
// Vector v2 = { 1.23, 3.45, 6.7, 8 }; // v2 has 4 elements

	void push_back(double); // add element at end increasing the size by one
							// ...
};

// Vector’s initializer - list constructor might be defined like this:
//Vector::Vector(std::initializ er_list<double> lst) // initialize with a list
//	:elem{ new double[lst.siz e()] }, sz{ lst.siz e() }
//{
//	copy(lst.begin(), lst.end(), elem); // copy from lst into elem
//}

int main()
{
	int q(0);



	cin >> q; //just to stop at the command window
}

/*
Vector read(istream& is)
{
	Vector v;
	for (double d; is >> d;) // read floating-point values into d
		v.push_back(d); // add d to v
	return v;
}*/ 
// The input loop is terminated by an end-of-file or a formatting error.