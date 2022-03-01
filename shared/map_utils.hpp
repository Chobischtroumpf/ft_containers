#ifndef MAP_UTILS_HPP
#define MAP_UTILS_HPP

namespace ft
{
	template<typename It1, typename It2>
	struct pair {
		typedef It1 first_type;
		typedef It2 second_type;

		first_type first;
		second_type second;

		pair(): first(), second() {}

		pair(const first_type &a, const second_type &b): first(a), second(b) {}

		template<typename _It0, typename _It1>
		pair(const pair<_It0, _It1> &p): first(p.first), second(p.second) {}

		pair &operator=(const pair &rhs)
		{
			first = rhs.first;
			second = rhs.second;

			return (*this);
		}
	};

	template<typename It1, typename It2>
}

#endif