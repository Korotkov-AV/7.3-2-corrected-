#include <iostream>
#include<deque>
#include<future>
#include<iterator>
#include <algorithm>

template<typename Iterator, typename Func, size_t size = 50>
void parallel_for_each(Iterator first, Iterator last, Func f) {
	size_t curr_size = std::distance(first, last);
	if (curr_size <= size)
	{
		std::for_each(first, last, f);
		return;
	}

	auto mid = first;
	std::advance(mid, curr_size / 2);
	std::async(parallel_for_each<Iterator, Func>, first, mid, f);
	parallel_for_each(mid, last, f);
}

int main()
{
	std::deque<int> list(51);

	std::deque<int>::iterator start = list.begin();
	std::deque<int>::iterator end = list.end();

	for (auto it = start; it != end; it++) {
		*it = std::rand();
		std::cout << *it << " ";
	}
	std::cout << "\n\n";

	parallel_for_each(start, end, [](int& n) { n++; });

	for (auto n : list) {
		std::cout << n << " ";
	}
}