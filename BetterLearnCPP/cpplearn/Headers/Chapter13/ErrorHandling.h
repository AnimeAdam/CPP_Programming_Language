#pragma once


namespace Chapter13
{
	//Simple example of error handling
	int do_task()
	{
		int result;
		// ...
		if (result > 0)
			return result;
		else
			throw std::out_of_range("Result is not above 0"); //<stdexcept>
	}
	void taskmaster()
	{
		try {
			auto result = do_task();
			// use result
		}
		catch (...) {
			// failure to do_task: handle problem
		}
	}

	/*Exception throws should be infrequent compared to function calls or the structure of the system
	has been obscured. However, we should expect most large programs to throw and catch at least
	some exceptions in the course of a normal and successful run.*/

	/*where an exception is
		thrown, all memory allocated must be either deallocated or owned by some object, which in turn
		must ensure that the memory is properly deallocated.For example :*/
	void f(int i)
	{
		int* p = new int[10];
		// ...
		if (i < 0) {
			delete[] p; // delete before the throw or leak
			//throw Bad();
		}
		// ...
	}

	//Example of a handler for resource management with error handling
	class File_ptr {
		FILE* p;
	public:
		File_ptr(const char* n, const char* a) // open file n
			: p{ std::fopen(n,a) }
		{
			if (p == nullptr) throw std::runtime_error{ "File_ptr: Can't open file" };
		}
		File_ptr(const std::string& n, const char* a) // open file n
			:File_ptr{ n.c_str(),a }
		{ }
		explicit File_ptr(FILE* pp) //assume ownership of pp
			:p{ pp }
		{
			if (p == nullptr) throw std::runtime_error("File_ptr: nullptr");
		}
		// ... suitable move and copy operations ...
		~File_ptr() { fclose(p); }
		operator FILE*() { return p; }
		};	

	/*• We need to choose between compile-time asserts (evaluated by the compiler) and run-time
	asserts (evaluated at run time).
	• For run-time asserts we need a choice of throw, terminate, or ignore.
	• No code should be generated unless some logical condition is true. For example, some runtime
	asserts should not be evaluated unless the logical condition is true. Usually, the logical
	condition is something like a debug flag, a level of checking, or a mask to select among
	asserts to enforce.
	• Asserts should not be verbose or complicated to write (because they can be very common).*/
	void print_number(int* myInt) noexcept { //Specifies whether a function could throw exceptions. ALSO noexcept(expression) for IF true noexcept
		assert(myInt != NULL, "You see that magic, this appears when this equals NULL, so when the expression is false");
		printf("%d\n", *myInt);
	}
	template<typename T>
	T mul10(const T t)
	{
		static_assert(std::is_integral<T>::value, "Moar magic"); //compile-time assertion checking
		return (t << 3) + (t << 1);
	}

	int o = 1;
	bool j = noexcept(o == 1); 
	//The noexcept operator performs a compile-time check that returns true if an expression is declared to not throw any exceptions.

	//Specifies that a constructor or conversion function (since C++11) is explicit, that is, 
	//it cannot be used for implicit conversions and copy-initialization.
	struct B
	{
		explicit B(int) { }
		explicit B(int, int) { }
		explicit operator bool() const { return true; }
	};
}