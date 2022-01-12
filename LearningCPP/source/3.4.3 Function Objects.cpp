#include <iostream>
#include <vector>
#include <list>
#include <complex>
#include <memory>

using namespace std; // make std members visible

template<typename T>
class Less_than {
	const T val; // value to compare against
public:
	Less_than(const T& v) :val(v) { }
	bool operator()(const T& x) const { return x<val; } // call operator
};

// We can count the occurrences of values for which a "predicate" returns true:
template<typename C, typename P>
int count(const C& c, P pred)
{
	int cnt = 0;
	for (const auto& x : c)
		if (pred(x))
			++cnt;
	return cnt;
};

template<class C, class Oper>
void for_all(C& c, Oper op) // assume that C is a container of pointers
{
	for (auto& x : c)
		op(?x); //pass op() a reference to each element pointed to
}

class Shape {
public:
	virtual double center() const = 0; // pure virtual
	virtual void move(double to) = 0;

	virtual void draw() const = 0; // draw on current "Canvas"
	virtual void rotate(int angle) = 0;

	virtual ~Shape() {} // destructor
						// ...
};

class Circle : public Shape {
public:
	Circle(double p, int rr); // constructor

	double center() const { return x; }
	void move(double to) { x = to; }

	void draw() const;
	void rotate(int) {} // nice simple algorithm
private:
	double x; // center
	int r; // radius
};

enum class Kind { circle, triangle, smiley };

//We can define named variables of type Less_than for some argument type :
Less_than<int> lti{ 42 }; // lti(i) will compare i to 42 using < (i<42)
Less_than<string> lts{ "Backus" }; // lts(s) will compare s to "Backus" using < (s<"Backus")

Kind k;
double p(5.248);
int r(6);


int main()
{
	int q(0);

	
	cin >> q; //just to stop at the command window
}

//We can call such an object, just as we call a function:
void fct(int n, const string & s)
{
	bool b1 = lti(n); // true if n<42
	bool b2 = lts(s); // true if s<"Backus"
					  // ...
}

void f(const vector<int>& vec, const list<string>& lst, int x, const string& s)
{
	cout << "number of values less than " << x
		<< ": " << count(vec, Less_than<int>{x})
// Here, Less_than<int>{x} constructs an object for which the call operator
// compares to the int called x
		<< '\n';
	cout << "number of values less than " << s
		<< ": " << count(lst, Less_than<string>{s})
// Less_than<string>{s} constructs an object that compares to the string called s		
		<< '\n';
}

// The beauty of these function objects is that they carry the value to be compared against with them.
// We don’t have to write a separate function for each value(and each type), 
// and we don’t have to introduce nasty global variables to hold values.
// Also, for a simple function object like Less_than inlining is simple, 
// so that a call of Less_than is far more efficient than an indirect function call.


// We have to define Less_than separately from its use.That could be seen as inconvenient.
// Consequently, there is a notation for implicitly generating function objects :
void f(const vector<int>& vec, const list<string>& lst, int x, const string& s)
{
	cout << "number of values less than " << x
		<< ": " << count(vec, [&](int a) { return a<x; })
// The notation [&](int a){ return a<x; } is called a lambda expression
// It generates a function object exactly like Less_than<int>{x}.
		<< '\n';
	cout << "number of values less than " << s
		<< ": " << count(lst, [&](const string& a) { return a<s; })
		<< '\n';
}

unique_ptr<Shape> read_shape(istream& is) // read shape descriptions from input stream is
{
	// read shape header from is and find its Kind k
	switch (k)
	{
	case Kind::circle:
		// read circle data {Point,int} into p and r
		return unique_ptr<Shape>{new Circle{ p,r }}; // §5.2.1
													 // ...
	}
}

void user()
{
	vector<unique_ptr<Shape>> v;
	while (cin)
		v.push_back(read_shape(cin));
	for_all(v, [](Shape& s) { s.draw(); }); // draw_all()
	for_all(v, [](Shape& s) { s.rotate(45); }); // rotate_all(45)
}

// I pass a reference to Shape to a lambda so that the lambda doesn’t 
// have to care exactly how the objects are stored in the container.
// In particular, those for_all() calls would still work if I changed v
// to a vector<Shape*>