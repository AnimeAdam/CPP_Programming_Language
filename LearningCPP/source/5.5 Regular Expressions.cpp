#include <iostream>
#include <vector>
#include <string>
#include <list>
#include <map>
#include <unordered_map>
#include <complex>
#include <memory>
#include <algorithm>
#include <iterator>
#include <cstddef>
#include <thread>
#include <mutex>
#include <future>
#include <queue>
#include <numeric>
#include <chrono>
#include <forward_list>
#include <type_traits>
#include <regex>

using namespace std; // make std members visible
using namespace std::chrono; // see §35.2



int main()
{
	int q = 0;

	//  To give a taste of the style of the regex library, let us define and print a pattern :
	regex pat(R"(\w{2}\s?\d{5}(?\d{4})?)"); // ZIP code pattern: XXddddd-dddd and var iants
	cout << "pattern: " << pat << '\n';

	int lineno = 0;
	for (string line; getline(cin, line);) { // read into line buffer
		++lineno;
		smatch matches; // matched strings go here
		if (regex_search(line, matches, pat)) // search for pat in line
			cout << lineno << ": " << matches[0] << '\n';
	}
// The regex_search(line ,matches,pat) searches the line for anything that matches the regular expression
// stored in pat and if it finds any matches, it stores them in matches
// If no match was found, regex_search(line, matches, pat) returns false



	cin >> q; //just to stop at the command window
}