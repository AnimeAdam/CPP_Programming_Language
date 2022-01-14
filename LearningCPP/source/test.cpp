#pragma once

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

using namespace std; // make std members visible

class MyClass
{
public:
	MyClass();
	~MyClass();
	int i = 0;
	void a(int j) { i = j; }
	int b() { return i; }

private:
	
};

MyClass::MyClass()
{
}

MyClass::~MyClass()
{
}

class MyClass2 : public MyClass
{
public:
	MyClass2();
	~MyClass2();
	int i = 5;

private:

};

MyClass2::MyClass2()
{
}

MyClass2::~MyClass2()
{
}

//Test file for custom classes
int testMain()
{
	int y(0);

	MyClass q;
	MyClass2 w;

	w.a(1);

	cout << w.i;

	cin >> y; //just to stop at the command window

	return 0;
}