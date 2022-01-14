#pragma once


namespace Chapter8
{
	/*An array is an aggregate of elements of the same type.In its simplest form, a struct is an aggregate
		of elements of arbitrary types.For example :*/
	//An object of a struct holds its members in the order they are declared.
	struct Address {
		const char* name; // "Jim Dandy"
		int number; // 61
		const char* street; // "South St"
		const char* town; //"New Providence"
		char state[2]; // 'N' 'J' //Strings are terminated by a zero character, '\0', so "NJ" has three characters – one more than will fit		
		const char* zip; //"07974"

		Address(const std::string n, int nu, const std::string& s, 
			const std::string& t, const std::string& st, int z);
		//Constructors are needed if you need to reorder arguments, validate arguments, modify arguments, establish invariants		
	};

	//You can minimize wasted memeory space by simply ordering members by size (largest member first).
	//For example :
	struct Readout {
		int value;
		char hour; // [0:23]
		char seq; // sequence mark ['a':'z']
	};

	//The name of a type becomes available for use immediately after it has been encountered and not
	//just after the complete declaration has been seen.For example:
	//However, it is not possible to declare new objects of a struct until its complete declaration has been seen.	
	struct Link {
		Link* previous;
		Link* successor;
		//Link linker;	//error because the compiler is not able to determine the size
	};

	//To allow two (or more) structs to refer to each other, we can declare a name to be the name of a struct. For example:
	struct List; // struct name declaration: List to be defined later
	struct LinkList {
		LinkList* pre;
		LinkList* suc;
		List* member_of;
		int data;
	};
	struct List {
		LinkList* head;
	};
	
	struct S; // ‘‘S’’ is the name of some declared type
	S* h(S* struc) { return struc; }
	void k(S* p)
	{
		//S a; // error : S not defined; size needed to allocate
		//f(); //error : S not defined; size needed to return value
		//g(a); //error : S not defined; size needed to pass argument
		//p− > m = 7; // error : S not defined; member name not known
		S* q = h(p); // ok: pointers can be allocated and passed
		//q− > m = 7; // error : S not defined; member name not known
	}

	//For reasons that reach into the prehistory of C, it is possible to declare a struct and a non-struct with
	//the same name in the same scope.For example :
	struct stat { /* ... */ };
	int stat(char* name, struct stat* buf);

	//You do not need to define a constructor simply to initialize members in order. For example:
	struct Point {
		int x, y;
	};
	Point p0; // danger : uninitialized if in local scope (§6.3.5.1)
	Point p1{}; // default construction: {{},{}}; that is {0.0}
	Point p2{ 1 }; // the second member is default constructed: {1,{}}; that is {1,0}
	Point p3{ 1,2 }; // {1,2}

	/*So, a POD(‘‘Plain Old Data’’) is an object that can be manipulated as ‘‘just data’’ without worrying
	about complications of class layouts or user - defined semantics for construction, copy, and
	move.For example :*/
	struct S0 { }; // a POD
	struct S1 { int a; }; // a POD
	struct S2 { int a; S2(int aa) : a(aa) { } }; // not a POD (no default constructor)
	struct S3 { int a; S3(int aa) : a(aa) { } S3() {} }; // a POD (user-defined default constructor)
	struct S4 { int a; S4(int aa) : a(aa) { } S4() = default; }; // a POD
	struct S5 { virtual void f(); /* ... */ }; // not a POD (has a virtual function)
	struct S6 : S1 { }; // a POD
	struct S7 : S0 { int b; }; // a POD
	struct S8 : S1 { int b; }; // not a POD (data in both S1 and S8)
	struct S9 : S0, S1 {}; // a POD

	//Standard copy for a POD
	template<typename T>
	void mycopy(T* to, const T* from, int count)
	{
		if (std::is_pod<T>::value)
			memcpy(to, from, count∗sizeof(T));
		else
			for (int i = 0; i != count; ++i)
				to[i] = from[i];
	}
	/*The is_pod is a standard-library type property predicate (§35.4.1) defined in <type_traits> allowing
	us to ask the question ‘‘Is T a POD?’’ in our code. The best thing about is_pod<T> is that it saves
	us from remembering the exact rules for what a POD is.*/

	//FIELDS
	//Example of a bit-field layout
	struct PPN { // R6000 Physical Page Number
		unsigned int PFN : 22; // Page Frame Number
		int : 3; // unused
		unsigned int CCA : 3; // Cache Coherency Algorithm
		bool nonreachable : 1;
		bool dirty : 1;
		bool valid : 1;
		bool global : 1;
	};
	
	void part_of_VM_system(PPN* p)
	{
		// ...
		if (p->dirty) { // contents changed
			// copy to disk
			//(p−>dirty = 0;
		}
	}

	/*Surprisingly, using fields to pack several variables into a single byte does not necessarily save
	space. It saves data space, but the size of the code needed to manipulate these variables increases
	on most machines. Programs have been known to shrink significantly when binary variables were
	converted from bit-fields to characters! Furthermore, it is typically much faster to access a char or
	an int than to access a field. Fields are simply a convenient shorthand for using bitwise logical
	operators (§11.1.1) to extract information from and insert information into part of a word.*/



}