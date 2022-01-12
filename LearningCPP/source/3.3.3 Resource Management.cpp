#include <iostream>
#include <vector>
#include <thread>
#include "Vector.h"

using namespace std; // make std members visible

bool heartbeat(false);

int main()
{
	int q(0);



	cin >> q; //just to stop at the command window
}

std::vector<thread> my_threads;
Vector init(int n)
{
	thread t{ heartbeat }; // run hear tbeat concurrently (on its own thread)
	my_threads.push_back(move(t)); // move t into my_threads
								   // ... more initialization ...
	Vector vec(n);
	for (int i = 0; i<vec.size(); ++i) vec[i] = 777;
	return vec; // move res out of init()
}

auto v = init(0); // star t hear tbeat and initialize v

// This makes resource handles, such as Vector and thread, an 
// alternative to using pointers in many cases

// I used the standard - library vector to hold the threads because 
// we don’t get to parameterize Vector with an element type