#pragma once


namespace Chapter8
{
	/*An enumeration is a type that can hold a set of integer values specified by the user (§iso.7.2).
	Some of an enumeration’s possible values are named and called enumerators.*/
	/*[1] enum classes, for which the enumerator names (e.g., red) are local to the enum and their
	values do not implicitly convert to other types
	[2] ‘‘Plain enums,’’ for which the enumerator names are in the same scope as the enum and
	their values implicitly convert to integers*/
	/*An enumeration is represented by some integer type and each enumerator by some integer
	value. We call the type used to represent an enumeration its underlying type. The underlying type
	must be one of the signed or unsigned integer types (§6.2.4); the default is int.*/

	//A plain enum can be unnamed.For example :
	enum { arrow_up = 1, arrow_down, arrow_sideways };

	//In global scope, or enum's scope
	enum States { 
		state1,
		state2
	};
	States sta1 = state1;

	//In class scope
	enum class privateStates {
		state1,
		state2
	};
	privateStates sta2 = privateStates::state1;

	enum class Warning : int { green, yellow, orange, red }; // sizeof(Warning)==sizeof(int)
	enum class Warning : char { green, yellow, orange, red }; // sizeof(Warning)==1

	//BITWISE FLAG ENUMS
	enum class Printer_flags {
		acknowledge = 0x1,		// 1 << 0	//1
		paper_empty = 0x2,		// 1 << 1	//2
		busy = 0x4,				// 1 << 2	//4
		out_of_black = 0x8,		// 1 << 3	//8
		out_of_color = 0x10		// 1 << 4	//16
		//
	};
	//The explicit conversions are necessary because a class enum does not support implicit conversions.
	constexpr Printer_flags operator|(Printer_flags a, Printer_flags b)
	{
		return static_cast<Printer_flags>(static_cast<int>(a) | static_cast<int>(b));
	}
	constexpr Printer_flags operator&(Printer_flags a, Printer_flags b)
	{
		return static_cast<Printer_flags>(static_cast<int>(a) & static_cast<int>(b));
	}
	void try_to_print(Printer_flags x)
	{
		if (static_cast<int>(x & Printer_flags::acknowledge)) {
			// ...
		}
		else if (static_cast<int>(x & Printer_flags::busy)) {
			// ...
		}
		else if (static_cast<int>(x & (Printer_flags::out_of_black | Printer_flags::out_of_color))) {
			// either we are out of black or we are out of color
			// ...
		}
		 //...
	}
	//It is possible to declare an enum class without defining it (§6.3) until later. For example:
	enum class Color_code : char; // declaration
	void foobar(Color_code* p); // use of declaration
	// ...
	enum class Color_code : char { // definition
		red, yellow, green, blue
	};

	//int conversions
	enum class Flag : char { x = 1, y = 2, z = 4, e = 8 };
	Flag f0{}; //f0 gets the default value 0
	//Flag f1 = 5; // type error: 5 is not of type Flag
	//Flag f2 = Flag{ 5 }; //error : no narrowing conversion to an enum class
	Flag f3 = static_cast<Flag>(5); // brute force
	//Flag f4 = static_cast<Flag>(999); // error : 999 is not a char value (maybe not caught)

	//Each enumerator has an integer value.We can extract that value explicitly.For example :
	int i = static_cast<int>(Flag::y); // i becomes 2
	char c = static_cast<char>(Flag::e); // c becomes 8

	//REGULAR ENUMS
	enum Traffic_light { tl_red, tl_yellow, tl_green }; //was red, yellow, green
	enum Warning { green, yellow, orange, red }; // fire alert levels
	// error : two definitions of yellow (to the same value)
	// error : two definitions of red (to different values)

	//Warning a1 = 7; // error : no int->Warning conversion
	int a2 = green; // OK: green is in scope and converts to int
	int a3 = (int)Warning::green; // OK: Warning->int conversion
	Warning a4 = Warning::green; // OK
	void f(Traffic_light x)
	{
		if (x == 9) { /* ... */ } // OK (but Traffic_light doesn’t have a 9)
		//if (x == red) { /* ... */ } // error : two reds in scope
		if (x == (int)Warning::red) { /* ... */ } // OK (Ouch!)
		if (x == Traffic_light::tl_red) { /* ... */ } // OK
	}

	enum Traffic_light_char : char { tl_red, tl_yellow, tl_green }; // underlying type is char
	enum Color_code_char : char; // declaration
	void foobar(Color_code_char* p); // use of declaration
	// ...
	enum Color_code_char : char { red, yellow, green, blue }; // definition

	/*range of the enumeration is [0:2k-1] where 2k is the smallest power of 2 for which all
	enumerators are within the range. If there are negative enumerators, the range is [-2k:2k-1]. This
	defines the smallest bit-field capable of holding the enumerator values using the conventional two’s
	complement representation. For example:*/
	enum E1 { dark, light }; // range 0:1
	enum E2 { a = 3, b = 9 }; // range 0:15
	enum E3 { min = -10, max = 1000000 }; // range -1048576:1048575

	//Moar conversions
	enum Flager { x = 1, y = 2, z = 4, e = 8 }; // range 0:15
	Flager f0{}; //f0 gets the default value 0
	//Flager f1 = 5; // type error: 5 is not of type Flager
	//Flager f2 = Flag{ 5 }; //error : no explicit conversion from int to Flager
	Flager f2 = static_cast<Flager>(5); // OK: 5 is within the range of Flager
	Flager f3 = static_cast<Flager>(z | e); // OK: 12 is within the range of Flager
	Flager f4 = static_cast<Flager>(99); // undefined: 99 is not within the range of Flager	
}