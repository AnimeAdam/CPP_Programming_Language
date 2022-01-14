#pragma once


namespace Chapter4
{

	//Example output and it's equivalent
	void f()
	{
		std::cout << 10;
	}
	void g()
	{
		int i{ 10 };
		std::cout << i;
	}
	void h(int i)
	{
		std::cout << "the value of i is ";
		std::cout << i;
		std::cout << '\n';
	}
	void h2(int i)
	{
		std::cout << "the value of i is " << i << '\n';
	}
	void k()
	{
		int b = 'b'; // note: char implicitly converted to int
		char c = 'c';
		std::cout << 'a' << b << c;
	}
	//will output a98c

	//Input example
	void f2()
	{
		int i;
		std::cin >> i; // read an integer into i
		double d;
		std::cin >> d; // read a double-precision floating-point number into d
	}

	void hello()
	{
		std::cout << "Please enter your name\n";
		std::string str;
		std::cin >> str;
		std::cout << "Hello, " << str << "!\n";
	}
	//By default, a whitespace character (§7.3.2), such as a space, terminates the read, so if you enter 
	//Eric Bloodaxe pretending to be the ill - fated king of York, the response is still :  Hello, Eric!
	
	//getline() example for keeping white spaces and endline
	void hello_line()
	{
		std::cout << "Please enter your name\n";
		std::string str;
		std::getline(std::cin, str);
		std::cout << "Hello, " << str << "!\n";
	}

	//Example of creating user-defined input output streams
	struct Entry {
		std::string name;
		int number;
	};
	std::ostream& operator<<(std::ostream& os, const Entry& e)
	{
		return os << "{\"" << e.name << "\", " << e.number << "}";
	}
	std::istream& operator>>(std::istream& is, Entry& e)
		// read { "name" , number } pair. Note: for matted with { " " , and }
		//An input operation returns a reference to its istream which can be used to test if the operation succeeded.
	{
		char c, c2;
		if (is >> c && c == '{' && is >> c2 && c2 == '"') { // start with a { "
			std::string name; // the default value of a string is the empty string: ""
			while (is.get(c) && c != '"') // anything before a " is part of the name, The is>>c skips whitespace by default, but is.g et(c) does not
				name += c;
			if (is >> c && c == ',') {
				int number = 0;
				if (is >> number >> c && c == '}') { // read the number and a }
					e = { name ,number }; // assign to the entry
					return is;
				}
			}
		}
		is.setf(std::ios_base::failbit); // register the failure in the stream
		return is;
	}
	//We can read such a pair of values from input into an Entry like this:
	//for (Entry ee; std::cin >> ee;  ) // read from cin into ee
	//{
	//	std::cout << ee << '\n'; // write ee to cout
	//}
}