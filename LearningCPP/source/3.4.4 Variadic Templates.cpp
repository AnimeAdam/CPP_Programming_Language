#include <iostream>
#include <vector>
#include <list>
#include <complex>
#include <memory>

using namespace std; // make std members visible

template<typename T, typename ... Tail>
void f(T head, Tail... tail) 
{
	g(head); // do something to head
	f(tail...); // try again with tail
	// The ellipsis, ..., is used to indicate ‘‘the rest’’ of a list.
}

void f() { } // do nothing
// It seems that f() is a simple variant of printf() printing 
// arbitrary lists or values – implemented in 
// three lines of code plus their surrounding declarations

template<typename T>
void g(T x)
{
	cout << x << " ";
}

int main()
{
	int q(0);

	cout << "first: ";
	f(1, 2.2, "hello");
	cout << "\nsecond: ";
	f(0.2, 'c', "yuck!", 0, 1, 2);
	cout << "\n";
// This would call f(1,2.2,"hello"), which will call f(2.2,"hello"), 
// which will call f("hello"), which will call f()

	cin >> q; //just to stop at the command window
}