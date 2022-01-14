#pragma once


namespace Chapter4
{
	//VECTOR
	//Example of a vector
	std::vector<Entry> phone_book = {
	{"David Hume",123456},
	{"Karl Popper",234567},
	{"Bertrand Arthur William Russell",345678}
	};
	
	//Vector subscripting example
	void print_book(const std::vector<Entry>& book)
	{
		for (int i = 0; i != book.size(); ++i)
			std::cout << book[i] << '\n';
	}
	
	//range-for loop example
	void print_book_loop (const std::vector<Entry>& book)
	{
		for (const auto& x : book) // for "auto" see §2.2.2
			std::cout << x << '\n';
	}

	std::vector<int> v1 = { 1, 2, 3, 4 }; // size is 4
	std::vector<std::string> v2; // size is 0
	std::vector<Chapter3::Shape*> v3(23); //size is 23; initial element value: nullptr
	std::vector<double> v4(32, 9.9); // size is 32; initial element value: 9.9

	//push_back example to add an element
	void input()
	{
		for (Entry e; std::cin >> e;)
			phone_book.push_back(e);
	}

	//copy assignment example
	std::vector<Entry> book2 = phone_book; //They hold separate copies of every Entry

	//Example of range error
	//void silly(std::vector<Entry>& book)
	//{
	//	int i = book[ph.size()].number; // book.size() is out of range
	//	// ...
	//}

	//range-checking alternative for vector
	//at() operation is a vector subscript operation that throws an exception of type out_of_range if its argument is out of the vector’s range(§2.4.3.1, §31.2.2).
	template<typename T> class Vec : public std::vector<T> {
	public:
		using std::vector<T>::vector; // use the constructors from vector (under the name Vec); see §20.3.5.1
		T& operator[](int i) // range check
		{
			return std::vector<T>::at(i);
		}
		const T& operator[](int i) const // range check const objects; §3.2.1.1
		{
			return std::vector<T>::at(i);
		}
	};
	void checked(Vec<Entry>& book) //Checks the out of range error check
	{
		try {
			book[book.size()] = { "Joe",999999 }; // will throw an exception
			// ...
		}
		catch (std::out_of_range) {
			std::cout << "range error\n";
		}
	}
	/*
	int main()
	try {
	// your code
	}
	catch (out_of_rang e) {
	cerr << "range error\n";
	}
	catch (...) {
	cerr << "unknown exception thrown\n";
	}
	*/

	//LIST
	std::list<Entry> phone_book_list = {
		{"David Hume",123456},
		{"Karl Popper",234567},
		{"Bertrand Arthur William Russell",345678}
	};

	//Simple search function for list 
	int get_number(const std::string& s)
	{
		for (const auto& x : phone_book_list)
			if (x.name == s)
				return x.number;
		return 0; // use 0 to represent "number not found"
	}
	int get_number_iterator(const std::string& s)
	{
		for (auto p = phone_book_list.begin(); p != phone_book_list.end(); ++p)
			if (p->name == s)
				return p->number;
		return 0; // use 0 to represent "number not found"
	}

	void f(const Entry& ee, std::list<Entry>::iterator p, std::list<Entry>::iterator q)
	{
		phone_book_list.insert(p, ee); // add ee before the element referred to by p
		phone_book_list.erase(q); // remove the element referred to by q
	}
	
	//MAP
	//map is a container of pairs of values optimized for lookup.
	std::map<std::string, int> phone_book_map{
	{"David Hume",123456},
	{"Karl Popper",234567},
	{"Ber trand Ar thur William Russell",345678}
	};

	int get_number_map(const std::string& s)
	{
		return phone_book_map[s];
	}

	//UNORDERED_MAP
	//it is called ‘‘unordered’’ because they don’t require an ordering function, instead it uses a default hash function
	std::unordered_map<std::string, int> phone_book_unordered_map
	{
	{"David Hume",123456},
	{"Karl Popper",234567},
	{"Bertrand Arthur William Russell",345678}
	};

	int get_number_unordered_map(const std::string& s)
	{
		return phone_book_unordered_map[s];
	}

	//ALGORITHMS
	//the following sorts a vector and places a copy of each unique vector element on a list: 
	bool operator<(const Entry& x, const Entry& y) // less than
	{
		return x.name < y.name; // order Entrys by their names
	}
	void b(std::vector<Entry>& vec, std::list<Entry>& lst)
	{	
		std::sort(vec.begin(), vec.end()); // use < for order
		//std::unique_copy(vec.begin(), vec.end(), lst.begin()); // don’t copy adjacent equal elements //MISSING SOMETHING
	}
	//If we wanted to place the unique elements in a new container
	std::list<Entry> p(std::vector<Entry>& vec)
	{
		std::list<Entry> res;
		std::sort(vec.begin(), vec.end());
		//std::unique_copy(vec.begin(), vec.end(), std::back_inserter(res)); // append to res //MISSING SOMETHING
		//You use std::back_inserter for example when you need to pass an input iterator to an std::algorithm.
		return res;
	}



	//the standard algorithm find looks for a value in a sequence and returns an iterator to the element found
	bool has_c(const std::string& s, char c) // does s contain the character c?
	{
		auto p = std::find(s.begin(), s.end(), c);
		if (p != s.end())
			return true;
		else
			return false;
	}
	//Like many standard-library search algorithms, find returns end() to indicate ‘‘not found.’’
	bool has_c_simple(const std::string& s, char c) // does s contain the character c? //Same as above in less code
	{
		return std::find(s.begin(), s.end(), c) != s.end();
	}
	//Find the location of all occurrences of a character in a string.
	//We can return the set of occurrences as a vector of string iterators.
	std::vector<std::string::iterator> find_all(std::string& s, char c) // find all occurrences of c in s
	{
		std::vector<std::string::iterator> res;
		for (auto p = s.begin(); p != s.end(); ++p)
			if (*p == c)
				res.push_back(p);
		return res;
	}
	void test() //tests the find_all()
	{
		std::string m{ "Mary had a little lamb" };
		for (auto p : find_all(m, 'a'))
			if (*p != 'a')
				std::cerr << "a bug!\n";
	}
	//Iterators and standard algorithms work equivalently on every standard container for which their use makes sense.
	template<typename C, typename V>
	std::vector<typename C::iterator> find_all_generalise(C& c, V v) // find all occurrences of v in c
	{
		std::vector<typename C::iterator> res;
		for (auto p = c.begin(); p != c.end(); ++p)
			if (*p == v)
				res.push_back(p);
		return res;
	}
	template<typename T>
	using Iterator = typename T::iterator; //introducing a type alias(§3.4.5) for Iterator:
	template<typename C, typename V>
	std::vector<Iterator<C>> find_all_alias(C& c, V v) // find all occurrences of v in c
	{
		std::vector<Iterator<C>> res;
		for (auto p = c.begin(); p != c.end(); ++p)
			if (*p == v)
				res.push_back(p);
		return res;
	}
	void test_find_all_alias()
	{
		std::string m{ "Mary had a little lamb" };
		for (auto p : find_all(m, 'a')) // p is a str ing::iterator
			if (*p != 'a')
				std::cerr << "string bug!\n";
		std::list<double> ld{ 1.1, 2.2, 3.3, 1.1 };
		for (auto p : find_all_alias(ld, 1.1))
			if (*p != 1.1)
				std::cerr << "list bug!\n";
		std::vector<std::string> vs{ "red", "blue", "green", "green", "orange", "green" };
		for (auto p : find_all_alias(vs, "green"))
			if (*p != "green")
				std::cerr << "vector bug!\n";
		for (auto p : find_all_alias(vs, "green"))
			*p = "ver t";
	}

	

	//To make an ostream_iterator, we need to specify which stream will be used and the type of objects written to it.	
	std::ostream_iterator<std::string> oo{ std::cout }; // write strings to cout
	void testOO()
	{
		*oo = "Hello, "; // meaning cout<<"Hello, "
		++oo;
		*oo = "world!\n"; // meaning cout<<"wor ld!\n"
	}
	//This is yet another way of writing the canonical message to standard output. The ++oo is done to mimic writing into an array through a pointer.
	
	//istream_iterator is something that allows us to treat an input stream as a read - only container. We must specify the stream to be usedand the type of values
	std::istream_iterator<std::string> ii{ std::cin };
	//Input iterators are used in pairs representing a sequence, so we must provide an istream_iterator to indicate the end of input.
	std::istream_iterator<std::string> eos{};
	//a simple program to read a file, sort the words read, eliminate duplicates, and write the result to another file
	int test_IOiterators()
	{
		std::string from, to;
		std::cin >> from >> to; // get source and target file names

		std::ifstream is{ from }; // input stream for file "from"
		std::istream_iterator<std::string> ii{ is }; // input iterator for stream
		std::istream_iterator<std::string> eos{}; // input sentinel

		std::ofstream os{ to }; // output stream for file "to"
		std::ostream_iterator<std::string> oo{ os,"\n" }; // output iterator for stream, the second argument is used to delimit output values

		std::vector<std::string> b{ ii,eos }; // b is a vector initialized from input [ii:eos)
		std::sort(b.begin(), b.end()); // sor t the buffer

		unique_copy(b.begin(), b.end(), oo); // copy buffer to output, discard replicated values

		return !is.eof() || !os; // return error state (§2.2.1, §38.3)
	}
	int test_IOiterators_simple()
	{
		std::string from, to;
		std::cin >> from >> to; // get source and target file names

		std::ifstream is{ from }; // input stream for file "from"
		std::ofstream os{ to }; // output stream for file "to"

		std::set<std::string> b{ std::istream_iterator<std::string>{is},std::istream_iterator<std::string>{} }; // read input
		std::copy(b.begin(), b.end(), std::ostream_iterator<std::string>{os, "\n"}); // copy to output

		return !is.eof() || !os; // return error state (§2.2.1, §38.3)
	}

	//Example of a predicate
	struct Greater_than {
		int val;
		Greater_than(int v) : val{ v } { }
		bool operator()(const std::pair<std::string, int>& r) { return r.second > val; }
	};
	void q(std::map<std::string, int>& m)
	{
		auto p = std::find_if(m.begin(), m.end(), Greater_than{ 42 });
		// ...
	}
	//Alternative lambda expression
	//int cxx = count_if(m.begin(), m.end(), [](const std::pair<std::string, int>& r) { return r.second > 42; });
}