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

class X
{
public:
	X(int j);
	~X();
	void do_something();

private:
	int i;
};

X::X(int j)
{
	i = j;
}

X::~X()
{
}

void X::do_something() {
	int i(0);
	i += 5;
}

void Z() {
	out_of_range{ "Test" };
}

void f(int i, int j) // X* vs. unique_ptr<X>
{
	X* p = new X(i); // allocate a new X
	unique_ptr<X> sp{ new X(i) }; // allocate a new X and give its pointer to unique_ptr
							   // ...
	if (i<99) throw Z; // may throw an exception
	if (j<77) return; // may retur n "early"
	p->do_something(); // may throw an exception
	sp->do_something(); // may throw an exception
						// ...
	delete p; // destroy *p
}
// Here, we ‘‘forgot’’ to delete p if i<99 or if j<77. On the other hand, unique_ptr ensures that its object
// is properly destroyed whichever way we exit f() (by throwing an exception, by executing return, or
// by ‘‘falling off the end’’)

// Ironically, we could have solved the problem simply by not using a
// pointer and not using new:
void f(int i, int j) // use a local variable
{
	X x(i);
	// ...
}

// unique_ptr uses include passing free-store allocated objects in and out of functions:
unique_ptr<X> make_X(int i)
// make an X and immediately give it to a unique_ptr
{
	// ... check i, etc. ...
	return unique_ptr<X>{new X{ i }};
}

void No_file() {
	out_of_range{ "Test" };
}

void f(shared_ptr<fstream>);
void g(shared_ptr<fstream>);
void user(const string& name, ios_base::openmode mode)
{
	shared_ptr<fstream> fp{ new fstream(name ,mode) };
	if (!fp) throw No_file; // make sure the file was properly opened
	f(fp);
	g(fp);
	// ...
}
// Now, the file opened by fp’s constructor will be closed by the last function to (explicitly or implicitly)
// destroy a copy of fp
// Note that f() or g() may spawn a task holding a copy of fp or in some
// other way store a copy that outlives user()

int main()
{
	int q(0);



	cin >> q; //just to stop at the command window
}