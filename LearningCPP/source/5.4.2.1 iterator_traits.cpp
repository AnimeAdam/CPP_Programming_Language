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

using namespace std; // make std members visible
using namespace std::chrono; // see §35.2

template<typename C>
using Iterator_type = typename C::iterator; // C’s iterator type

template<typename Iter>
using Iterator_category = typename std::iterator_traits<Iter>::iterator_category; // Iter’s category

template<typename Ran> // for random-access iterators
void sort_helper(Ran beg, Ran end, random_access_iterator_tag) // we can subscript into [beg:end)
{
	sort(beg, end); // just sort it
}

template<typname C>
void sort(C& c)
{
	using Iter = Iterator_type<C>;
	sort_helper(c.begin(), c.end(), Iterator_category<Iter>{});
}
// Here, I use two type functions: Iterator_type<C> returns the iterator type of C (that is, C::iterator) and
// then Iterator_category<Iter>{} constructs a ‘‘tag’’ value indicating the kind of iterator provided :
// std::random_access_iterator_tag if C’s iterator supports random access.
// std::forward_iterator_tag if C’s iterator supports forward iteration.

template<typename For> // for forward iterators
void sort_helper(For beg, For end, forward_iterator_tag) // we can traverse [beg:end)
{
	vector<decltype(*beg)> v{ beg,end }; // initialize a vector from [beg:end)
	sort(v.begin(), v.end());
	copy(v.begin(), v.end(), beg); // copy the elements back
}

void test(vector<string>& v, forward_list<int>& lst)
{
	sort(v); // sort the vector
	sort(lst); // sort the singly-linked list
}


int main()
{
	int q = 0;



	cin >> q; //just to stop at the command window
}