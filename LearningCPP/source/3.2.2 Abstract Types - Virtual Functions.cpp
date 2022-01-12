#include <iostream>
#include <list>
#include "Vector.h"
using namespace std; // make std members visible

class Container {
public:
// The curious =0 syntax says the function is pure virtual; that is, some class derived
// from Container must define the function
	virtual double& operator[](int) = 0; // pure virtual function	
	virtual int size() const = 0; // const member function (§3.2.1.1)
// members operator[]() and size() are said to override the corresponding members in base class Container
	virtual ~Container() {} // destructor (§3.2.1.2)
};
// It is not possible to define an object that is just a Container; 
// a Container can only serve as the interface to a class that implements its operator[]() and
// size() functions

class Vector_container : public Container { // Vector_container implements Container
	Vector v;
public:
	Vector_container(int s) : v(s) { } // Vector of s elements
	~Vector_container() {}
// The destructor (˜Vector_container()) overrides the base class destructor (˜Container())
// The member destructor (˜Vector()) is implicitly invoked by its class destructor(˜Vector_container())
	double& operator[](int i) { return v[i]; }
	int size() { return v.size(); } //can't be const because it's not compatiable with Vector::Size() qualifiers
};

class List_container : public Container { // List_container implements Container
	std::list<double> ld; // (standard-library) list of doubles (§4.4.2)
// Here, the representation is a standard-library list<double>
public:
	List_container() { } // empty List
	List_container(initializer_list<double> il): ld{ il } { }
	~List_container() {}
	double& operator[](int i);
	int size() const { return ld.size(); }
};

double& List_container::operator[](int i)
{
	for (auto& x : ld) {
		if (i == 0) return x;
		--i;
	}
	throw out_of_range("List container");
}


int main()
{
	int q(0);



	cin >> q; //just to stop at the command window
}

void use(Container& c)
// Note how use() uses the Container interface in complete ignorance of implementation details
{
	const int sz = c.size(); 
	for (int i = 0; i != sz; ++i)
		cout << c[i] << '\n';
	// It uses size() and [] without any idea of exactly which type provides their implementation
}

/*void g() //When g() calls use(), Vector_container’s operator[]() must be called
{
	Vector_container vc{ 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0 };
	use(vc);
}*/
// Since use() doesn’t know about Vector_containers but only knows the Container interface, it will
// work just as well for a different implementation of a Container

void h() // When h() calls use(), List_container’s operator[]() must be called.
{
	List_container lc = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	use(lc);
}
// The point is that use(Container&) has no idea if its argument is a Vector_container, a List_container,
// or some other kind of container; it doesn’t need to know.It can use any kind of Container.It knows
// only the interface defined by Container.Consequently, use(Container&) needn’t be recompiled if the
// implementation of List_container changes or a brand - new class derived from Container is used

// The flip side of this flexibility is that objects must be manipulated through pointers or references