#pragma once

namespace Chapter5_3
{

	//TIME

	void time_example() {
		auto t0 = std::chrono::high_resolution_clock::now();
		//do_work();
		auto t1 = std::chrono::high_resolution_clock::now();
		std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(t1-t0).count() << "msec\n"; 
		//The clock returns a time_point (a point in time). Subtracting two time_points gives a duration (a	period of time).
		//Various clocks give their results in various units of time (the clock I used measures nanoseconds), 
		//so it is usually a good idea to convert a duration into a known unit.That’s what duration_cast does.				
	}

	//TYPE FUNCTIONS

	constexpr float min = std::numeric_limits<float>::min(); // smallest positive float (§40.2)
	constexpr int szi = sizeof(int); // the number of bytes in an int

	/*The standard-library sort() takes a pair of iterators supposed to define a sequence (§4.5). Furthermore,
	those iterators must offer random access to that sequence, that is, they must be random access
	iterators like the following containers.*/
	template<class C>
	void sort_simple(C& c)
	{
		std::sort(c.begin(), c.end()); 
	}
	void test(std::vector<std::string>& v, std::forward_list<int>& lst)
	{
		sort_simple(v); // sort the vector
		sort_simple(lst); // sort the singly-linked list
	}

	//The standard library provides a mechanism, iterator_traits that allows us to check which kind of iterator is supported.
	//Helper functions that take an extra argument indicating whether they are to be used for random - access iterators or forward iterators.
	template<typename Ran> // for random-access iterators
	void sort_helper(Ran beg, Ran end, std::random_access_iterator_tag) // we can subscript into [beg:end)
	{
		std::sort(beg, end); // just sort it
	}
	template<typename For> // for forward iterators
	void sort_helper(For beg, For end, std::forward_iterator_tag) // we can traverse [beg:end)
	{
		vector<decltype(*beg)> v{ beg,end }; // initialize a vector from [beg:end) 
		//decltype() is a built-in type function that returns the declared type of its argument, thus v is a vector<X> where X is the element type of the input sequence
		std::sort(v.begin(), v.end());
		std::copy(v.begin(), v.end(), beg); // copy the elements back
	}
	template<typename C>
	void sort(C& c)
	{
		using Iter = Iterator_type<C>;
		sort_helper(c.begin(), c.end(), Iterator_category<Iter>{});
		//Iterator_type<C> returns the iterator type of C (that is, C::iterator) and
		//then Iterator_category<Iter>{} constructs a ‘‘tag’’ value indicating the kind of iterator provided
	}
	//This technique, called tag dispatch is one of several used in the standard libraryand elsewhere to improve flexibility and performance.


	//A standard - library type predicate is a simple type function that answers a fundamental question about types.For example :	
	bool b1 = std::is_arithmetic<int>(); // yes, int is an arithmetic type
	bool b2 = std::is_arithmetic<std::string>(); // no, std::string is not an arithmetic type

	//Example for when type predicates are useful
	template<typename Scalar>
	class Complex1 {
		Scalar re, im;
	public:
		static_assert(std::is_arithmetic<Scalar>(), "Sorry, I only support complex of arithmetic types");
		// ...
	};
		
	template<typename T>
	constexpr bool Is_arithmetic()
	{
		return std::is_arithmetic<T>::value;
	}

	//pair and tuple

	struct Record 
	{
		std::string str;

		Record(std::string stra) : str(stra) {}
		std::string name() { return str; }
	};

	//we could let the standard library write the definition for us. For example,
	//the standard library algorithm equal_range(§32.6.1) returns a pair of iterators specifying a sub-sequence meeting a predicate :
	template<typename Forward_iterator, typename T, typename Compare>
	std::pair<Forward_iterator, Forward_iterator> bounds = std::equal_range(Forward_iterator first, Forward_iterator last, const T & val, Compare cmp);
	//The first member of a pair is called first and the second member is called second.

	auto rec_eq = [](const Record& r1, const Record& r2) { return r1.name < r2.name; };// compare names
	void f(const std::vector<Record>& v) // assume that v is sorted on its "name" field
	{
		auto er = equal_range(v.begin(), v.end(), Record{ "Reg" }, rec_eq);
		for (auto p = er.first; p != er.second; ++p) // print all equal records
			std::cout << *p->name; //assume that << is defined for Record
	}

	//The make_pair() function makes it easy to create a pair without explicitly mentioning its type(§34.2.4.1).For example :
	void f(std::vector<std::string>& v)
	{
		auto pp = make_pair(v.begin(), 2); // pp is a pair<vector<str ing>::iterator,int>
		// ...
	}

	//If you need more than two elements(or less), you can use tuple(from <utility>; §34.2.4.2).A tuple
	//is a heterogeneous sequence of elements; for example:
	std::tuple<std::string, int, double> t2("Sild", 123, 3.14); // the type is explicitly specified
	auto t = make_tuple(string("Herring"), 10, 1.23); // the type is deduced
	// t is a tuple<string,int,double>
	std::string s = get<0>(t); // get first element of tuple
	int x = get<1>(t);
	double d = get<2>(t);



	//REGULAR EXPRESSIONS
	//Example of a regular expression
	void regX() {
		std::regex pat(R"(\w{2}\s∗\d{5}(−\d{4})?)"); // ZIP code pattern: XXddddd-dddd and variants	
		int lineno = 0;
		for (std::string line; std::getline(std::cin, line);) { // read into line buffer
			++lineno;
			std::string smatch; 
			std::string matches; //matched strings go here
			if (std::regex_search(line, matches, pat)) // search for pat in line
				std::cout << lineno << ": " << matches[0] << '\n';
			//regex_search(line ,matches,pat) searches the line for anything that matches the regular expression
			//stored in patand if it finds any matches, it stores them in matches.If no match was found,
			//regex_search(line, matches, pat) returns false.The matches variable is of type smatch.
		}
	}


	//MATH
	//Example of accumlate
	void f()
	{
		std::list<double> lst{ 1, 2, 3, 4, 5, 9999.99999 };
		auto s = accumulate(lst.begin(), lst.end(), 0.0); // calculate the sum
		std::cout << s << '\n'; // print 10014.9999
	}

	//Example of Random Number Generator
	using my_engine = std::default_random_engine; // type of engine
	using my_distribution = std::uniform_int_distribution<>; // type of distribution

	my_engine re{}; // the default engine
	my_distribution one_to_six{ 1,6 }; // distribution that maps to the ints 1..6
	auto die = bind(one_to_six, re); // make a generator
	int x = die(); // roll the die: x becomes a value in [1:6]
	//The standard - library function bind() makes a function object that will invoke its first argument
	//(here, one_to_six) giv en its second argument(here, re) as its argument(§33.5.1).Thus a call die() is
	//equivalent to a call one_to_six(re).
	//Alternative
	auto die = bind(std::uniform_int_distribution<>{1, 6}, std::default_random_engine{});

	//Simple random number generator
	class Rand_int {
	public:
		Rand_int(int low, int high) :dist{ low,high } { }
		int operator()() { return dist(re); } // draw an int
	private:
		std::default_random_engine re;
		std::uniform_int_distribution<> dist;
	};
	Rand_int rnd{ 1,10 }; // make a random number generator for [1:10]
	int x = rnd(); // x is a number in [1:10]
	void test_random()
	{
		Rand_int rnd{ 0,4 }; // make a unifor m random number generator
		std::vector<int> histogram(5); // make a vector of size 5
		for (int i = 0; i != 200; ++i)
			++histogram[rnd()]; // fill histogram with the frequencies of numbers [0:4]
		for (int i = 0; i != histogram.size(); ++i) { // write out a bar graph
			std::cout << i << '\t';
			for (int j = 0; j != histogram[i]; ++j) std::cout << '*';
			std::cout << std::endl;
		}
	}

	//Example use of valarray
	void f(std::valarray<double>& a1, std::valarray<double>& a2)
	{
		std::valarray<double> a = a1*3.14 + a2 / a1; // numer ic array operators *, +, /, and =
		a2 += a1*3.14;
		a = abs(a);
		double d = a2[7];
		// ...
	}

	//Example of numeric_limits
	static_assert(std::numeric_limits<char>::is_signed, "unsigned characters!");
	static_assert(100000 < std::numeric_limits<int>::max(), "small ints!");
}