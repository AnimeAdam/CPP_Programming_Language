#pragma once


namespace Chapter8
{

	/*A union is a struct in which all members are allocated at the same address so that the union occupies
	only as much space as its largest member. Naturally, a union can hold a value for only one
	member at a time.*/
	/*[1] A union cannot have virtual functions.
	[2] A union cannot have members of reference type.
	[3] A union cannot have base classes.
	[4] If a union has a member with a user-defined constructor, a copy operation, a move operation,
	or a destructor, then that special function is deleted (§3.3.4, §17.6.4) for that union;
	that is, it cannot be used for an object of the union type.
	[5] At most one member of a union can have an in-class initializer (§17.4.4).
	[6] A union cannot be used as a base class.*/
	//Consider a symbol table entry that holds a name and a value:
	enum Type { str, num };
	struct Entry {
		char* name;
		Type t;
		char* s; // use s if t==str
		int i; // use i if t==num
	};
	void f(Entry* p)
	{
		if (p->t == str)
			std::cout << p->s;
		// ...
	}
	//The members s and i can never be used at the same time, so space is wasted. It can be easily recovered
	//by specifying that both should be members of a union, like this:
	union Value {
		char* s;
		int i;
	};
	//The language doesn’t keep track of which kind of value is held by a union, so the programmer must do that:
	struct EntryV {
		char* name;
		Type t;
		Value v; // use v.s if t==str; use v.i if t==num
	};
	void f(EntryV* p)
	{
		if (p-> t == str)
			std::cout << p-> v.s;
		// ...
	}
	
	//When using unions that are sometimes misused for type conversions so it's important to use 
	//explicit type conversions in such cases
	int* cheat2(int i)
	{
		return reinterpret_cast<int*>(i); // obviously ugly and dangerous
	}

	//Because of the rules of Unions it is easy to create and copy a Union without one but if it contains
	//a member with a constructor it causes errors.
	union U {
		int m1;
		std::complex<double> m2; // complex has a constructor
		std::string m3; // string has a constructor (maintaining a serious invariant)
	};
	void f2(U x)
	{
		//U u; // error : which default constructor?
		//U u2 = x; // error : which copy constr uctor?
		x.m1 = 1; // assign to int member
		//string s = u.m3; // disaster : read from string member
		//return; //error : which destructors are called for x, u, and u2?
	}
	//It is possible to specify an in-class initializer for at most one member. If so, this initializer will
	//be used for default initialization.For example :
	union U2 
	{
		int a;
		const char* p{ "" };
	};
	U2 x1; // default initialized to x1.p == ""
	U2 x2{ 7 }; // x2.a == 7

	//Encapsulating a Union
	class Entry2 { // two alter native representations represented as a union
	private:
		enum class Tag { number, text };
		Tag type; // discriminant
		union { // That makes it an anonymous union.
			//An anonymous union is an object, not a type, 
			//and its members can be accessed without mentioning an object name.
			int i;
			std::string s; // string has default constructor, copy operations, and destructor
		};
	public:
		struct Bad_entry { }; // used for exceptions
		std::string name;
		~Entry2();
		Entry2& operator=(const Entry2&); // necessary because of the string variant
		Entry2(const Entry2&);
		// Getters
		int number() const;
		std::string text() const;
		// Setters
		void set_number(int n);
		void set_text(const std::string&);
		// ...
	};
	/*These access functions check the type tag, and if it is the one that correctly corresponds to the
	access we want, it returns a reference to the value; otherwise, it throws an exception. Such a union
	is often called a tagged union or a discriminated union.*/
	int Entry2::number() const
	{
		if (type != Tag::number) throw Bad_entry{};
		return i;
	};
	std::string Entry2::text() const
	{
		if (type != Tag::text) throw Bad_entry{};
		return s;
	};
	/*The write-access functions basically do the same checking of the type tag, but note how setting
	a new value must take the previous value into account:*/
	void Entry2::set_number(int n)
	{
		if (type == Tag::text) {
			s.~basic_string(); // explicitly destroy string (§11.2.4)
			type = Tag::number;
		}
		i = n;
	}
	void Entry2::set_text(const std::string& ss)
	{
		if (type == Tag::text)
			s = ss;
		else {
			new(&s) std::string{ ss }; // placement new: explicitly construct string (§11.2.4)
			type = Tag::text;
		}
	}
	/*The use of a union forces us to use otherwise obscure and low-level language facilities (explicit
	construction and destruction) to manage the lifetime of the union elements. This is another reason
	to be wary of using unions.*/
	Entry2& Entry2::operator=(const Entry2& e) // necessary because of the string variant
	{
		if (type == Tag::text && e.type == Tag::text) {
			s = e.s; // usual string assignment
			return *this;
		}
		if (type == Tag::text) s.~basic_string(); // explicit destroy (§11.2.4)
		switch (e.type) {
		case Tag::number:
			i = e.i;
			break;
		case Tag::text:
			s = e.s; 
			type = e.type;
			break;
		}
		return *this;
	}

	Entry2::~Entry2()
	{
		if (type == Tag::text) s.~basic_string(); // explicit destroy (§11.2.4)
	}
}