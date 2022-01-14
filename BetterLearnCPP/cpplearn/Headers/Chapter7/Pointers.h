#pragma once


namespace Chapter7
{
	//ARRAY
	int a1[10]; // 10 ints in static storage
	void q()
	{
		int a2[20]; // 20 ints on the stack
		int*p = new int[40]; // 40 ints on the free store
		// ...
	}

	//There is no built - in copy operation for arrays.You cannot initialize one array with another(not
	//even of exactly the same type), and there is no array assignment:
	//int v6[8] = v5; // error : can’t copy an array (cannot assign an int* to an array)
	//v6 = v5; // error : no array assignment
	//Similarly, you can’t pass arrays by value.

	int v[] = { 1, 2, 3, 4 };
	int* p1 = v; // pointer to initial element (implicit conversion)
	int* p2 = &v[0]; // pointer to initial element
	int* p3 = v + 4; // pointer to one-beyond-last element

	//Access example
	void fi(char v[])
	{
		for (int i = 0; v[i] != 0; ++i)
			int a = v[i];
	}
	void fc(char v[])
	{
		for (char* p = v; *p != 0; ++p)
			int a = *p;
	}
	//a[j] == ∗(&a[0] + j) == ∗(a + j) == ∗(j + a) == j[a]

	//moar access examples
	void fpp(char v[], int size)
	{
		for (int i = 0; i != size; ++i)
			int a = (v[i]);	// hope that v has at least size elements
		//for (int x : v)
		//	int a = (x); //error : range-for does not work for pointers
		const int N = 7;
		char v2[N];
		for (int i = 0; i != N; ++i)
			int a = (v2[i]);
		for (int x : v2)
			int a = (x); //range-for wor ks for arrays of known size
	}

	//access multidimensional array
	void print_m35(int m[3][5])
	{
		for (int i = 0; i != 3; i++) {
			for (int j = 0; j != 5; j++)
				std::cout << m[i][j] << '\t';
			std::cout << '\n';
		}
	}
	void print_mi5(int m[][5], int dim1)
	{
		for (int i = 0; i != dim1; i++) {
			for (int j = 0; j != 5; j++)
				std::cout << m[i][j] << '\t';
			std::cout << '\n';
		}
	}
	void print_mij(int* m, int dim1, int dim2)
	{
		for (int i = 0; i != dim1; i++) {
			for (int j = 0; j != dim2; j++)
				std::cout << m[i*dim2 + j] << '\t'; // obscure
			std::cout << '\n';
		}
	}
	int test()
	{
		int v[3][5] = {
		{0,1,2,3,4}, {10,11,12,13,14}, {20,21,22,23,24}
		};
		print_m35(v);
		print_mi5(v, 3);
		print_mij(&v[0][0], 3, 5);
	}

	//POINTERS
	int*pi; //pointer to int
	char** ppc; //pointer to pointer to char
	int* ap[15]; // array of 15 pointers to ints
	int (*fp)(char*); // pointer to function taking a char* argument; returns an int
	int* f(char*); //function taking a char* argument; returns a pointer to int

	//occasionally need to store or pass along an address of a memory location
	//without actually knowing what type of object is stored there
	//so use void* as ‘‘pointer to an object of unknown type.’’
	void f(int* pi)
	{
		void* pv = pi; // ok: implicit conversion of int* to void*
		//*pv; //error : can’t dereference void*
		//++pv; //error : can’t increment void* (the size of the object pointed to is unknown)
		int* pi2 = static_cast<int*>(pv); //explicit conversion back to int*
		//double* pd1 = pv; // error
		//double* pd2 = pi; // error
		double* pd3 = static_cast<double*>(pv); // unsafe (§11.5.2)
	}
	void* my_alloc(size_t n); // allocate n bytes from my special heap //Example of void* pointers function

	char *const cp; // const pointer to char
	char const* pc; //pointer to const char
	const char* pc2; //pointer to const char

	//const examples
	void f1(char* p)
	{
		char s[] = "Gorm";
		const char* pc = s; // pointer to constant
		//pc[3] = 'g'; // error : pc points to constant
		pc = p; // OK
		char *const cp = s; // constant pointer
		cp[3] = 'a'; // OK
		//cp = p; // error : cp is constant
		const char *const cpc = s; // const pointer to const
		//cpc[3] = 'a'; // error : cpc points to constant
		//cpc = p; // error : cpc is constant
	}

	//double& dr = 1; // error : lvalue needed
	const double& cdr{ 1 }; // OK
	//^
	//double temp = double{ 1 }; // first it creates a temporary with the right value
	//const double& cdr{ temp }; // then use the temporary as the initializer for cdr
	/*References to variables and references to constants are distinguished because introducing a temporary
	for a variable would have been highly error-prone; an assignment to the variable would
	become an assignment to the – soon-to-disappear – temporary. No such problem exists for references
	to constants, and references to constants are often important as function arguments (§18.2.4).*/

	//REFERENCES

	//References examples
	std::string var{ "Cambridge" };
	std::string f();
	//string& r1{ var }; // lvalue reference, bind r1 to var (an lvalue)
	//string& r2{ f() }; // lvalue reference, error : f() is an rvalue
	//string& r3{ "Princeton" }; // lvalue reference, error : cannot bind to temporary
	std::string&& rr1{ f() }; // rvalue reference, fine: bind rr1 to rvalue (a temporary)
	//string&& rr2{ var }; // rvalue reference, error : var is an lvalue
	std::string&& rr3{ "Oxford" }; // rr3 refers to a temporary holding "Oxford"
	const std::string& cr1 { "Harvard" }; // OK: make temporary and bind to cr1
	//The && declarator operator means ‘‘rvalue reference.’’

	template<class T>
	void swap(T& a, T& b) // "old-style swap", bad copying using too many resources
	{
		T tmp{ a }; // now we have two copies of a
		a = b; // now we have two copies of b
		b = tmp; // now we have two copies of tmp (aka a)
	}
	template<class T>
	void goodSwap(T& a, T& b) // "perfect swap" (almost), good passing by reference
	{
		T tmp{ static_cast<T&&>(a) }; // the initialization may write to a
		a = static_cast<T&&>(b); // the assignment may write to b
		b = static_cast<T&&>(tmp); // the assignment may write to tmp
	}
	template<class T>
	void perfectSwap(T& a, T& b) // "perfect swap" (almost), uses std version
	{
		T tmp{ move(a) }; // move from a
		a = move(b); // move from b
		b = move(tmp); // move from tmp
	}
	//move(x) means static_cast<X&&>(x) where X is the type of x
	
	//It you take a reference to a reference to a type, you get a reference to that type, rather than some
	//kind of special reference to reference type.
	using rr_i = int&&;
	using lr_i = int&;
	using rr_rr_i = rr_i&&; // ‘‘int && &&’’ is an int&&
	using lr_rr_i = rr_i&; // ‘‘int && &’’ is an int&
	using rr_lr_i = lr_i&&; // ‘‘int & &&’’ is an int&
	using lr_lr_i = lr_i&; // ‘‘int & &’’ is an int&
	//Reference to reference can only happen as the result of an alias (§3.4.5, §6.5) or a template type argument(§23.5.2.1).
	
}