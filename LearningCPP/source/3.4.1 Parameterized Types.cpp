#include <iostream>
#include <string>
#include <list>

using namespace std; // make std members visible

template<typename T> class Vector {
private:
	T* elem; // elem points to an array of sz elements of type T
	int sz;
public:
	Vector(int s); // constructor: establish invariant, acquire resources
	˜Vector() { delete[] elem; } // destructor: release resources
								 // ... copy and move operations ...
	T& operator[](int i);
	const T& operator[](int i) const;
	int size() const { return sz; }
	T* begin(Vector<T>& x);
	T* end(Vector<T>& x);
};

template<typename T>
Vector<T>::Vector(int s) // member function definition 
{
	if (s<0) throw Negative_siz e{};
	elem = new T[s];
	sz = s;
}

template<typename T>
const T& Vector<T>::operator[](int i) const // member function definition
{
	if (i<0 || size() <= i)
		throw out_of_rang e{ "Vector::operator[]" };
	return elem[i];
}

// To support the range-for loop for our Vector,
// we must define suitable begin() and end() functions
template<typename T> T* Vector<T>::begin(Vector<T>& x)
{
	return &x[0]; // pointer to first element
}

template<typename T> T* Vector<T>::end(Vector<T>& x)
{
	return x.begin() + x.size(); // pointer to one-past-last element
}

/*template<typename T> // There is another way
T? begin(Vector<T>& x)
{
	return &x[0]; // pointer to first element
}
template<typename T>
T? end(Vector<T>& x)
{
	return x.begin() + x.size(); // pointer to one-past-last element
}*/

int main()
{
	int q(0);



	cin >> q; //just to stop at the command window
}

// Examples of uses for temeplates
Vector<char> vc(200); // vector of 200 characters
Vector<string> vs(17); // vector of 17 strings
Vector<list<int>> vli(45); // vector of 45 lists of integers
// The >> in Vector<list<int>> terminates the nested template arguments;
// it is not a misplaced input operator.
// It is not (as in C++98) necessary to place a space between the two >s.

void write(const Vector<string>& vs) // Vector of some strings
{
	for (int i = 0; i != vs.size(); ++i)
		cout << vs[i] << '\n';
}

void f2(const Vector<string>& vs) // Vector of some strings
{
	for (auto& s : vs)
		cout << s << '\n';
}