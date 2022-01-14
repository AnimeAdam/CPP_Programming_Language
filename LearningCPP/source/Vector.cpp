#pragma once
// Vector.cpp:
#include <iostream>
#include "Vector.h" // get the interface

using namespace std;

Vector::Vector(int s)
/*:elem( new double[s] ), sz( s )
{
}*/ //a simplier why to create a constructor
{
	if (s<0) throw length_error{"Vector::Vector(int s)"};
	// Use the standard-library exception length_error to report a non-positive number of elements
	// because some standard - library operations use that exception to report problems of this kind
	elem = new double[s];
	sz = s;
}

double& Vector::operator[](int i)
{
	if (i<0 || size() <= i) throw out_of_range{ "Vector::operator[]" };
	// The throw transfers control to a handler for exceptions of type out_of_range in some function that
	// directly or indirectly called Vector::operator[](). To do that, the implementation will unwind the
	//function call stack as needed to get back to the context of that caller
	return elem[i];
}
int Vector::size() 
{
	return sz;
}