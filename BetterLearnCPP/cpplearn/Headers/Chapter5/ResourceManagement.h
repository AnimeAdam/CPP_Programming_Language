#pragma once


namespace Chapter5
{
	//Example of a lock Class
	std::mutex m; // used to protect access to shared data
	// mutex class is used to protect shared data from being simultaneously accessed by multiple threads.
// ...
	void q()
	{
		std::unique_lock<std::mutex> lck{ m }; // acquire the mutex m
		// ... manipulate shared data ...
		//A std::thread will not proceed until lck’s constructor has acquired its std::mutex m

		//In this example, unique_lock’s destructor releases the mutex when the thread of control leaves f() 
		//(through a return, by ‘‘falling off the end of the function, ’’ or through an exception throw).			
	}
	//calling std::thread owns a std::mutex from the time that it successfully calls either std::lock or std::try_lock until it calls unlock
	//When a std::thread owns a std::mutex, all other threads will block (for calls to std::lock) or receive a false return value (for std::try_lock) if they attempt to claim ownership of the std::mutex.
	//calling std::thread must not own the std::mutex prior to calling std::lock or std::try_lock.



	//unique_ptr and shared_ptr
	struct X
	{
		void do_something() {};
	};
	void w(int i, int j) // X* vs. unique_ptr<X>
	{
		X* p = new X; // allocate a new X
		std::unique_ptr<X> sp{ new X }; // allocate a new X and give its pointer to unique_ptr
		// ...
		if (i < 99) throw 20; // may throw an exception
		if (j < 77) return; // may return "early"
		p->do_something(); // may throw an exception
		sp->do_something(); // may throw an exception
		// ...
		delete p; // destroy *p
	}
	//unique_ptr ensures that its object is properly destroyed whichever way we exit f() 
	//(by throwing an exception, by executing return, or by ‘‘falling off the end’’).	
	std::unique_ptr<X> make_X(int i)
		// make an X and immediately give it to a unique_ptr
	{
		// ... check i, etc. ...
		return std::unique_ptr<X>{new X}; //{new X{ i }}
	}

	//The shared_ptrs for an object share ownership of an object and that object is destroyed when the
	//last of its shared_ptrs is destroyed.
	/*void f(std::shared_ptr<std::fstream>);
	void g(std::shared_ptr<std::fstream>);
	void user(const std::string& name, std::ios_base::openmode mode)
	{
		std::shared_ptr<std::fstream> fp{ new std::fstream(name ,mode) };
		if (!*fp) throw 20; // make sure the file was properly opened //No_file{}
		f(fp);
		g(fp);
		// ...
	}*/
	//The file opened by fp’s constructor will be closed by the last function to (explicitly or implicitly) destroy a copy of fp.
	//Note that f() or g() may spawn a task holding a copy of fp or in some
	//other way store a copy that outlives user().Thus, shared_ptr provides a form of garbage collection
	//that respects the destructor - based resource management of the memory - managed objects.
}