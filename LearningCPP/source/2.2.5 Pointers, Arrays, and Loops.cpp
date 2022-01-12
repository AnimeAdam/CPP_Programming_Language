#include <iostream>
using namespace std;

void copy_fct();
void print();
int count_x(char* p, char x);

int main()
{
	int q;

	char v[6]{ 'h', 'e', 'l', 'l', 'o', 'o' }; // array of 6 characters
	char* p; //pointer to character

	char* p1 = &v[3]; // p points to v’s four th element
	char x = *p1; //*p is the object that p points to

	double* pd = nullptr; // points to nothing
	//Link<Record>* lst = nullptr; // pointer to a Link to a Record
	//int x = nullptr; // error : nullptr is a pointer not an integer
	
	copy_fct();
	print();
	cout << count_x(p1, x);

	
	cin >> q; //just to stop at the command window
}

void copy_fct() // simple for loop
{
	int v1[10] { 0,1,2,3,4,5,6,7,8,9 };
	int v2[10]; // to become a copy of v1
	for (auto i = 0; i != 10; ++i) // copy elements
		v2[i] = v1[i];
	// ...
}

void print() // quicker for loop
{
	int v[] = { 0,1,2,3,4,5,6,7,8,9 };
	for (auto x : v) // for each x in v
		cout << x << '\n';
	for (auto x : { 10,21,32,43,54,65 })
		cout << x << '\n';
	// ...
} // The range-for-statement can be used for any sequence of elements

void increment()
{
	int v[] = { 0,1,2,3,4,5,6,7,8,9 };
	for (auto& x : v)
		++x;
	// ...
}

int count_x(char* p, char x) //assumes that the char? is a C-style string, that is, that the pointer points to a zero-terminated array of char.
// count the number of occurrences of x in p[]
// p is assumed to point to a zero-ter minated array of char (or to nothing)
{
	if (p == nullptr) return 0; // always check if the pointer is pointing to something
	int count = 0;
	for (; *p != 0; ++p) // we can leave out the initializer in a for-statement if we don’t need it.
		if (*p == x)
			++count;
	return count;
}