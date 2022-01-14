#pragma once


namespace Chapter6
{
	//Documentating for code
	unsigned char c1 = 64; // well defined: a char has at least 8 bits and can always hold 64
	unsigned char c2 = 1256; // implementation-defined: truncation if a char has only 8 bits
	
	//implementation-defined features can be checked
	//by stating them as static assertions(§2.4.3.3).For example :
	static_assert(4 <= sizeof(int), "sizeof(int) too small");

	//Example of undefined behavior
	const int size = 4*1024;
	char page[size];
	void f()
	{
		page[size + size] = 7; // undefined
	}

	//BOOL
	void f(int a, int b)
	{
		bool b1{ a == b }; //If a and b have the same value, b1 becomes true; otherwise, b1 becomes false.
		// ...
	}
	bool greater(int a, int b) { return a > b; }

	bool b1 = 7; // 7!=0, so b becomes true
	//bool b2{ 7 }; // error : narrowing (§2.2.2, §10.5)
	int i1 = true; // i1 becomes 1
	int i2{ true }; // i2 becomes 1 //use the {}-initializer syntax to prevent narrowing 

	//A pointer can be implicitly converted to a bool (§10.5.2.5). A non-null pointer converts to true;
	//pointers with the value nullptr convert to false.For example :
	void g(int* p)
	{
		bool b = p; // narrows to true or false
		bool b2{ p != nullptr }; // explicit test against nullptr
		if (p) { // equivalent to p!=nullptr
		// ...
		}
	}

	//CHAR
	char c = 255; // 255 is ‘‘all ones,’ ’ hexadecimal 0xFF
	int i = c; //i is undefined
	/*On a machine where a char is unsigned, the i is 255. On a machine where a char
	is signed, the i is −1. In this case, the compiler might warn about the 
	conversion of the literal 255 to the char value −1.*/

	/*void f(char c, signed char sc, unsigned char uc)
	{
		char* pc = &uc; // error : no pointer conversion
		signed char* psc = pc; // error : no pointer conversion
		unsigned char* puc = pc; // error : no pointer conversion
		psc = puc; // error : no pointer conversion
	}*/

	void g(char c, signed char sc, unsigned char uc)
	{
		c = 255; // implementation-defined if plain chars are signed and have 8 bits
		c = sc; // OK
		c = uc; // implementation-defined if plain chars are signed and if uc’s value is too large
		sc = uc; // implementation defined if uc’s value is too large
		uc = sc; // OK: conversion to unsigned
		sc = c; // implementation-defined if plain chars are unsigned and if c’s value is too large
		uc = c; // OK: conversion to unsigned
	}

	void p()
	{
		signed char sc = -160;
		unsigned char uc = sc; // uc == 116 (because 256-160==116)
		std::cout << uc; // print 't'
		char count[256]; // assume 8-bit chars
		++count[sc]; // likely disaster: out-of-range access
		++count[uc]; // OK
	}

	char v1[] = "a\xah\129"; // 6 chars: 'a' '\xa' 'h' '\12' '9' '\0'
	char v2[] = "a\xah\127"; // 5 chars: 'a' '\xa' 'h' '\127' '\0'
	char v3[] = "a\xad\127"; // 4 chars: 'a' '\xad' '\127' '\0'
	char v4[] = "a\xad\0127"; // 5 chars: 'a' '\xad' '\012' '7' '\0'

	//Examples of unicode
	//U'\UFADEBEEF'
	//u'\uDEAD'
	//u'\xDEAD'

	//size_t is an implementation-defined unsigned integer type that can hold the
	//size in bytes of every object.Consequently, it is used where we need to hold an object size.
	void* allocate(size_t n); // get n bytes

	//ALIGNMENT
	//The alignof() operator returns the alignment of its argument expression.For example :
	auto ac = alignof('c'); // the alignment of a char
	auto ai = alignof(1); // the alignment of an int
	auto ad = alignof(2.0); // the alignment of a double
	int a[20];
	auto aa = alignof(a); // the alignment of an int

	//Specifies the alignment requirement of a type or an object.
	// Every object of type sse_t will be aligned to 16-byte boundary
	struct alignas(16) sse_t
	{
		float sse_data[4];
	};
	// The array "cacheline" will be aligned to 128-byte boundary
	alignas(128) char cacheline[128];

	//EXTERN
	//any source file that includes this header will be able to use "global_x"
	extern int global_x;
	//it tells the compiler that an object of type int called x exists somewhere.

	//extern int error_number;
	//extern short error_number; // error : type mismatch
	//extern int error_number;
	//extern int error_number; // OK: redeclaration

	struct A { double x; };
	const A* q;
	int v() { return 1; }
	void e(int x) { x++; }
	//Examples of decltype specifiers
	decltype(q->x) y;       // type of y is double (declared type)
	decltype((q->x)) z = y; // type of z is const double& (lvalue expression)
	decltype(v) b; // the type of f function, even a lambda function
	decltype(e(x)); //(the return type of a call e(x);

	//WAYS TO DECLARE MULTIPLE IDENTIFIERS
	int x, j; // int x; int j;
	int* r, m; // int* r; int y; NOT int* y;
	int t, *l; //int t; int* l;
	int s[10], *sv; // int v[10]; int* pv;

	//INITIALIZATION
	int a1{ 1 }; //used in every context, uses the list initialization, does not allow narrowing
	int a2 = { 1 }; //C form
	int a3 = 1;		//C form
	int a4(1);
	auto z1{ 99 }; // z1 is an initializer_list<int>
	auto z2 = 99; // z2 is an int
	std::vector<std::string> v1{ "hello!" }; // v1 is a vector of 1 element with the value "hello!"
	//std::vector<std::string> v2("hello!"); // error : no vector constructor takes a string literal
	int x4{}; // x4 becomes 0
	double d4{}; // d4 becomes 0.0
	char* cp{}; //cp becomes nullptr
	std::vector<int> v4{}; // v4 becomes the empty vector
	std::string s4{}; // s4 becomes ""

	//The only really good case for an uninitialized variable is a large input buffer.For example :
	constexpr int max = 1024*1024;
	char buf[max];
	//char buf[max]{}; // initialize every char to 0, this causesa performance hit which just might have been significant
	
	void f()
	{
		int x; // x does not have a well-defined value
		char buf[1024]; // buf[i] does not have a well-defined value
		//int* p{ newint }; //*p does not have a well-defined value
		char* q{ new char[1024] }; // q[i] does not have a well-defined value
		std::string s; // s=="" because of string’s default constructor
		std::vector<char> v; // v=={} because of vector’s default constructor
		std::string* ps{ new std::string }; // *ps is "" because of string’s default constructor
		// ...
	}

	//int a[] = { 1, 2 }; // array initializer
	//struct S { int v, std::string h };
	//S s = { 1, "Helios" }; // struct initializer
	//std::complex<double> z = { 0, pi }; // use constructor
	//std::vector<double> v = { 0.0, 1.1, 2.2, 3.3 }; // use list constructor

	//AUTO

	auto y1 = { 1,2,3,4 }; // x1 is an initializer_list<int>
	auto y2 = { 1.0, 2.25, 3.5 }; // x2 is an initializer_list of<double>
	//auto y3 = { 1.0,2 }; // error : cannot deduce the type of {1.0,2} (§6.3.6.2)

	template<class T> void f1(std::vector<T>& arg)
	{
		for (std::vector<T>::iterator p = arg.begin(); p != arg.end(); ++p)
			*p = 7;
		for (auto p = arg.begin(); p != arg.end(); ++p)
			*p = 7;
	}
	/*The loop using auto is the more convenient to write and the easier to read. Also, it is more resilient
	to code changes. For example, if I changed arg to be a list, the loop using auto would still work correctly
	whereas the first loop would need to be rewritten. So, unless there is a good reason not to,
	use auto in small scopes.*/

	//We can decorate a deduced type with specifiers and modifiers (§6.3.1), such as const and & (reference;	
	void n(std::vector<int>& v)
	{
		for (const auto& x : v) { // x is a const int&
		// ...
		}
	}

	//Note that the type of an expression is never a reference because references are implicitly dereferenced
	//in expressions(§7.7).For example :
	void w(int& v)
	{
		auto x = v; // x is an int (not an int&)
		auto& y = v; // y is an int&
	}

	auto vv1 = 12345; // v1 is an int
	auto vv2 = 'c'; // v2 is a char
	//auto vv3 = f(); // v3 is of some appropriate type

	auto v1{ 12345 }; // v1 is a list of int
	auto v2{ 'c' }; // v2 is a list of char
	//auto v3{ f() }; // v3 is a list of some appropriate type of f


}

//SCOPE
int u;
void f2()
{
	int u = 1; // hide global x
	::u = 2; // assign to global x
	u = 2; // assign to local x
	// ...
}
int p = { 97 };
void f3()
{
	int p = p; // perverse: initialize x with its own (uninitialized) value
}