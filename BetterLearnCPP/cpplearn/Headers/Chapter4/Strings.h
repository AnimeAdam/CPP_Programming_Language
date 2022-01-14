#pragma once

//"folder\\file" //implementation character set string
//R"(folder\file)" // implementation character raw set string
//u8"folder\\file" // UTF-8 string
//u8R"(folder\file)" // UTF-8 raw string
//u"folder\\file" // UTF-16 string
//uR"(folder\file)" //UTF-16 raw string
//U"folder\\file" // UTF-32 string
//UR"(folder\file)" //UTF-32 raw string
//L"A"				//wchar_t string literal

namespace Chapter4
{
	//Example of a raw string, meaning a backslash is just a backslash
	std::string s = R"(\w\\w)"; // I’m pretty sure I got that right

	//The empty string is written as a pair of adjacent double quotes, "", and has the type const
	//char[1].The one character of the empty string is the terminating '\0'.

	//A string with the prefix L, such as L"angst", is a string of wide characters (§6.2.3). Its type is const wchar_t[].
	//Similarly, a string with the prefix LR, such as LR"(angst)", is a raw string


	//Examples of concatenation.
	std::string compose(const std::string& name, const std::string& domain)
	{
		return name + '@' + domain;
	}
	auto addr = compose("dmr", "belllabs.com");
	void m2(std::string& s1, std::string& s2)
	{
		s1 = s1 + '\n'; // append newline
		s2 += '\n'; // append newline
	}

	//Example of using the substr() which returns a string that is a copy of the substring indicated by its arguments.
	//first argument is an index into the string (a position), and the second is the length of the desired substring.
	std::string name = "Niels Stroustrup";
	void m3()
	{
		std::string s = name.substr(6, 10); // s = "Stroustrup"
		name.replace(0, 5, "nicholas"); // name becomes "nicholas Stroustrup"
		name[0] = toupper(name[0]); // name becomes "Nicholas Stroustrup"
	}

	//String comparision example
	std::string incantation;
	void respond(const std::string& answer)
	{
		if (answer == incantation) {
			// perform magic
		}
		else if (answer == "yes") {
			// ...
		}
		// ...
	}

	//A string literal is statically allocated so that it is safe to return one from a function.For example :
	const char* error_message(int i)
	{
		// ...
		return "range error";
	}
	//The memory holding "range error" will not go away after a call of error_message().

	const char* y = "Heraclitus";
	const char* w = "Heraclitus";
	void g()
	{
		if (y == w) std::cout << "one!\n"; // the result is implementation-defined
		// ...
	}
	//Note that == compares addresses(pointer values) when applied to pointers, and not the values
	//pointed to.

}