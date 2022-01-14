#pragma once

namespace Chapter5_1
{
	//A task to be executed concurrently with other tasks is launched by constructing 
	//a std::thread(found in <thread>) with the task as its argument.
	//A task is a function or a function object.
	void f() { 1+1; } // function
	struct F { // function object
		void operator()() { 1-1; } // F’s call operator (§3.4.3)
	};
	void user()
	{
		std::thread t1{ f }; // f() executes in separate thread
		std::thread t2{ F() }; // F()() executes in separate thread
		t1.join(); // wait for t1
		t2.join(); // wait for t2
	}
	//The join()s ensure that we don’t exit user() until the threads have completed. To ‘‘join’’ means to
	//‘‘wait for the thread to terminate.’’
	//Threads of a program share a single address space.
	//Since threads share an address space, they can communicate through shared objects(§5.3.4),
	//such communication is typically controlled by locks or other
	//mechanisms to prevent data races(uncontrolled concurrent access to a variable).

	//Programming concurrent tasks can be very tricky, like the following example
	//This is an example of a bad error: Here, f and F() each use the object cout without any form of synchronization.
	void z() { std::cout << "Hello "; }
	struct Z {
		void operator()() { std::cout << "Parallel World!\n"; }
	};
	//So our aim is to keep tasks completely separate except where they communicate in simple and obvious ways.
	//We just have to pass arguments, get a result back, and make sure that there is no use of shared data in between(no data races).
		


	//A task needs data to work upon. We can easily pass data (or pointers or references to the data) as arguments.
	void x(std::vector<double>& v); // function do something with v
	struct X { // function object: do something with v
		std::vector<double>& v;
		X(std::vector<double>& vv) :v{ vv } { }
		void operator()(); // application operator ; §3.4.3
	};
	void test_passing_arguments()
	{
		std::vector<double> some_vec{ 1,2,3,4,5,6,7,8,9 };
		std::vector<double> vec2{ 10,11,12,13,14 };
		std::thread t1{ x,some_vec }; // f(some_vec) executes in a separate thread
		//{f,some_vec} uses a thread variadic template constructor that can accept an arbitrary sequence of arguments		
		std::thread t2{ X{vec2} }; // F(vec2)() executes in a separate thread
		t1.join();
		t2.join();
	}
	//X{ vec2 } saves a reference to the argument vector in X. X can now use that array and
	//hopefully no other task accesses vec2 while X is executing.Passing vec2 by value would eliminate that risk.
	//If X::operator()() and x() perform the same algorithm, the handling of the two tasks are
	//roughly equivalent : in both cases, a function object is constructed for the thread to execute.
	//This is a somewhat sneaky, but not uncommon, way of returning a result.
	
	//Pass the input data by const reference and to pass the location of a place 
	//to deposit the result as a separate argument for returning a result
	void y(const std::vector<double>& v, double* res);// take input from v; place result in *res
	class Y {
	public:
		Y(const std::vector<double>& vv, double* p) :v{ vv }, res{ p } { }
		void operator()(); // place result in *res
	private:
		const std::vector<double>& v; // source of input
		double* res; //target for output
	};
	void test_passing_result()
	{
		std::vector<double> some_vec;
		std::vector<double> vec2;
		// ...
		double res1;
		double res2;
		std::thread t1{ y,some_vec,&res1 }; // y(some_vec,&res1) executes in a separate thread
		std::thread t2{ Y{vec2,&res2} }; // Y{vec2,&res2}() executes in a separate thread
		t1.join();
		t2.join();
		std::cout << res1 << ' ' << res2 << '\n';
	}

	//MUTEX
		
	//Sometimes tasks need to share data, so the access has to be synchronized so that at most one task at a time has access.
	//The solution is a mutex, a ‘‘mutual exclusion object.’’ A thread acquires a mutex using a lock() operation
	std::mutex m; // controlling mutex
	int sh; // shared data
	void u()
	{
		std::unique_lock<std::mutex> lck{ m }; // acquire mutex
		sh += 7; // manipulate shared data
	} //release mutex implicitly
	//The unique_lock’s constructor acquires the mutex (through a call m.lock()). 
	//If another thread has already acquired the mutex, the thread waits(‘‘blocks’’) until the other thread completes its access.
	//Once a thread has completed its access to the shared data, the unique_lock releases the mutex(with a call m.unlock()).

	//the previous example is error-prone, because the programmer has to know which mutex is supposed to correspond to which data,
	//So we must make the correspondence clear through various language means.
	class Record {
	public:
		std::mutex rm;
		// ...
	};

	/*For simultaneously access of a shared resource
	  The standard library offers help in the form of an operation for acquiring several locks simultaneously :*/	
	void o()
	{
		std::mutex m1;
		std::mutex m2;
		std::mutex m3;
		// ...
		std::unique_lock<std::mutex> lck1{ m1,std::defer_lock }; // defer_lock: don’t yet try to acquire the mutex
		std::unique_lock<std::mutex> lck2{ m2,std::defer_lock };
		std::unique_lock<std::mutex> lck3{ m3,std::defer_lock };
		// ...
		std::lock(lck1, lck2, lck3); //acquire all three locks
		// ... manipulate shared data ...
	} // implicitly release all mutexes
	/*This lock() will only proceed after acquiring all its mutex arguments and will never block(‘‘go to
	sleep’’) while holding a mutex.The destructors for the individual unique_locks ensure that the
	mutexes are released when a thread leaves the scope.*/

	//WAITING FOR EVENTS
		
	//a thread needs to wait for some kind of external event, such as another thread completing
	//a task or a certain amount of time having passed like the following:
	void r() 
	{
		auto t0 = std::chrono::high_resolution_clock::now();
		std::this_thread::sleep_for(std::chrono::milliseconds(20)); //this_thread refers to the one and only thread
		auto t1 = std::chrono::high_resolution_clock::now();
		std::cout << std::chrono::duration_cast<std::chrono::nanoseconds>(t1-t0).count() << " nanoseconds passed\n";
		//duration_cast to adjust the clock’s units to the nanoseconds I wanted.
	}

	//A condition_variable is a mechanism allowing one thread to
	//wait for another.In particular, it allows a thread to wait for some condition(often called an event)
	//to occur as the result of work done by other threads.
	class Message { // object to be communicated
// ...
	};
	std::queue<Message> mqueue; // the queue of messages
	std::condition_variable mcond; // the variable communicating events
	std::mutex mmutex; // the locking mechanism
	bool processed = false; //condition variable 
	void consumer()
	{
		while (true) {
			std::unique_lock<std::mutex> lck{ mmutex }; // acquire mmutex
			while (processed)
			mcond.wait(lck, [] {return processed; }); // release lck and wait;
			// re-acquire lck upon wakeup
			auto m = mqueue.front(); // get the message
			mqueue.pop();
			lck.unlock(); //release lck
			// ... process m ...
		}
	}
	//Here, I explicitly protect the operations on the queue and on the condition_variable with a
	//unique_lock on the mutex. Waiting on condition_variable releases its lock argument until the wait is
	//over(so that the queue is non - empty) and then reacquires it.
	void producer()
	{
		while (true) {
			Message m;
			// ... fill the message ...
			std::unique_lock<std::mutex> lck{ mmutex }; // protect operations
			mqueue.push(m);
			mcond.notify_one(); // notify
		} // release lock (at end of scope)
	}

	//FUTUUUUURE
	/*The basic idea is simple : When a task wants to pass a value to another, it puts the value into a promise.	
	Somehow, the implementation makes that value appear in the corresponding future, from which it can be read(typically by the launcher of the task).*/
	struct P {}; //example function object
	std::future<P> px;
	P p = px.get(); // if necessary, wait for the value to get computed
	/*If the value isn’t there yet, our thread is blocked until it arrives. If the value couldn’t be computed,
	get() might throw an exception (from the system or transmitted from the task from which we were
	trying to get() the value).*/
	
	//A promise is to provide simple ‘‘put’’ operations (called set_value() and set_exception()) to match future’s get().
	//If you have a promise and need to send a result of type X to a future, you can do one of two
	//things: pass a value or pass an exception.For example :
	void test_promise(std::promise<P>& pp) // a task: place the result in pp
	{
		// ...
		try {
			P res;
			// ... compute a value for res ...
			pp.set_value(res);
		}
		catch (...) { // oops: couldn’t compute res
		// pass the exception to the future’s thread:
			pp.set_exception(std::current_exception()); //The current_exception() refers to the caught exception (§30.4.1.2).
		}
	}
	//To deal with an exception transmitted through a future, the caller of get() must be prepared to
	//catch it somewhere.For example :
	void q(std::future<P>& ppx) // a task: get the result from px
	{
		// ...
		try {
			P v = ppx.get(); // if necessary, wait for the value to get computed
			// ... use v ...
		}
		catch (...) { // oops: someone couldn’t compute v
		// ... handle error ...
		}
	}

	/*The packaged_task type is provided to simplify setting up
	tasks connected with futures and promises to be run on threads. A packaged_task provides wrapper
	code to put the return value or exception from the task into a promise (like the code shown in
	§5.3.5.1). If you ask it by calling get_future, a packaged_task will give you the future corresponding
	to its promise. For example, we can set up two tasks to each add half of the elements of a
	vector<double> using the standard-library accumulate() (§3.4.2, §40.6):*/
	double accum(double* beg, double* end, double init)
		// compute the sum of [beg:end) starting with the initial value init
	{
		return std::accumulate(beg, end, init);
	}
	double comp2(std::vector<double>& v)
	{
		using Task_type = double(double*, double*, double); // type of task
		std::packaged_task<Task_type> pt0{ accum }; // package the task (i.e., accum)
		std::packaged_task<Task_type> pt1{ accum };
		std::future<double> f0{ pt0.get_future() }; // get hold of pt0’s future
		std::future<double> f1{ pt1.get_future() }; // get hold of pt1’s future
		double* first = &v[0];
		std::thread t1{ move(pt0),first,first + v.size() / 2,0 }; // start a thread for pt0
		std::thread t2{ move(pt1),first + v.size() / 2,first + v.size(),0 }; // start a thread for pt1
		//move() operations are needed because a packaged_task cannot be copied.
		// ...
		return f0.get() + f1.get(); // get the results
	}
	//The packaged_task template takes the type of the task as its template argument (here Task_type, an
	//alias for double(double∗, double∗, double)) and the task as its constructor argument(here, accum).
	//The two tasks will be run on separate threads and thus potentially in parallel.

	double accumIterator(std::vector<double>::iterator beg, std::vector<double>::iterator end, double init)
		// compute the sum of [beg:end) starting with the initial value init
	{
		return std::accumulate(beg, end, init);
	}

	//To launch tasks to potentially run asynchronously(meaning to run out of synch with each other), we can use async() :
	double comp4(std::vector<double>& v) // spawn many tasks if v is large enough
	{
		if (v.size() < 10000) 
			return accumIterator(v.begin(), v.end(), 0.0);
		auto v0 = &v[0];
		auto sz = v.size();
		auto f0 = std::async(accum, v0, v0 + sz / 4, 0.0); // first quarter
		auto f1 = std::async(accum, v0 + sz / 4, v0 + sz / 2, 0.0); // second quarter
		auto f2 = std::async(accum, v0 + sz / 2, v0 + sz*3 / 4, 0.0); // third quarter
		auto f3 = std::async(accum, v0 + sz*3 / 4, v0 + sz, 0.0); // fourth quarter
		return f0.get() + f1.get() + f2.get() + f3.get(); // collect and combine the results
	}
	/*Basically, async() separates the ‘‘call part’’ of a function call from the ‘‘get the result part,’’ and separates
	both from the actual execution of the task. Using async(), you don’t hav e to think about
	threads and locks. Instead, you think just in terms of tasks that potentially compute their results
	asynchronously.*/
	//Don’t even think of using async() for tasks that
	//share resources needing locking – with async() you don’t even know how many threads will be used
	//because that’s up to async() to decide based on what it knows about the system resources available
	//at the time of a call.

}