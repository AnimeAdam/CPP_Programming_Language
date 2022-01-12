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

namespace Estd {
	using namespace std;
	template<class C>
	void sort(C& c)
	{
		sort(c.begin(), c.end());
	}
	template<class C, class Pred>
	void sort(C& c, Pred p)
	{
		sort(c.begin(), c.end(), p);
	}
	// ...
}
// I put the container versions of sort() (and other algorithms) into their own namespace Estd
// (‘‘extended std’’) to avoid interfering with other programmers’ uses of namespace std

int main()
{
	int q(0);



	cin >> q; //just to stop at the command window
}