#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <unordered_map>
#include <complex>
#include <memory>
#include <algorithm>
#include <iterator>
#include <cstddef>

using namespace std; // make std members visible

// To make an ostream_iterator, we need to specify which stream will be used and the type of
// objects written to it.For example :
ostream_iterator<string> oo{ cout }; // write strings to cout

// Again, we must specify the stream to be used and the type of values expected:
istream_iterator<string> ii{ cin };

// This is the default istream_iterator:
istream_iterator<string> eos{};

// The effect of assigning to ?oo is to write the assigned value to cout. For example:
int main()
{
	int q(0);

	*oo = "Hello, "; // meaning cout<<"Hello, "
	++oo;
	*oo = "world!\n"; // meaning cout<<"wor ld!\n"
// This is yet another way of writing the canonical message to standard output. The ++oo is done to
// mimic writing into an array through a pointer

	cin >> q; //just to stop at the command window
}

// For example, we can write a simple program to read a file, sort the words
// read, eliminate duplicates, and write the result to another file :
/*int main()
{
	string from, to;
	cin >> from >> to; // get source and target file names
	ifstream is{ from }; // input stream for file "from"
	istream_iterator<string> ii{ is }; // input iterator for stream
	istream_iterator<string> eos{}; // input sentinel
	ofstream os{ to }; // output stream for file "to"
	ostream_iterator<string> oo{ os,"\n" }; // output iterator for stream
	// The ostream_iterator’s second argument is used to delimit output values
	vector<string> b{ ii,eos }; // b is a vector initialized from input [ii:eos)
	sort(b.begin(), b.end()); // sor t the buffer
	unique_copy(b.begin(), b.end(), oo); // copy buffer to output, discard replicated values
	return !is.eof() || !os; // return error state (§2.2.1, §38.3)
}*/
// Actually, this program is longer than it needs to be. We read the strings into a vector, then we
// sort() them, and then we write them out, eliminating duplicates


// we could replace the two lines using a
// vector with one using a set and replace unique_copy() with the simpler copy() :
/*int main()
{
	string from, to;
	cin >> from >> to; // get source and target file names
	ifstream is{ from }; // input stream for file "from"
	ofstream os{ to }; // output stream for file "to"
	set<string> b{ istream_iterator<string>{is},istream_iterator<string>{} }; // read input
	copy(b.begin(), b.end(), ostream_iterator<string>{os, "\n"}); // copy to output
	return !is.eof() || !os; // return error state (§2.2.1, §38.3)
}*/