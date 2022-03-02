#ifndef MAP_UTILS_HPP
#define MAP_UTILS_HPP

namespace ft
{
	template<typename T1, typename T2>
	struct pair {
		typedef T1 first_type;
		typedef T2 second_type;

		first_type first;
		second_type second;

		pair(): first(), second() {}

		pair(const first_type &a, const second_type &b): first(a), second(b) {}

		template<typename _T1, typename _T2>
		pair(const pair<_T1, _T2> &p): first(p.first), second(p.second) {}

		pair &operator=(const pair &rhs)
		{
			first = rhs.first;
			second = rhs.second;

			return (*this);
		}
	};

	template<typename T1, typename T2>
		bool operator==(const pair<T1, T2> &lhs,const pair<T1, T2> &rhs)
		{
			return (lhs.first == rhs.first && lhs.second && rhs.second);
		}

	template<typename T1, typename T2>
		bool operator!=(const pair<T1, T2> &lhs,const pair<T1, T2> &rhs)
		{
			return !(lhs.first == rhs.first || lhs.second && rhs.second);
		}

	template<typename T1, typename T2>
		bool operator<(const pair<T1, T2> &lhs,const pair<T1, T2> &rhs)
		{
			if (lhs.first != rhs.first)
				return (lhs.first < rhs.first);
			return lhs.second < rhs.second;
		}

	template<typename T1, typename T2>
		bool operator<=(const pair<T1, T2> &lhs,const pair<T1, T2> &rhs)
		{
			if (lhs.first != rhs.first || lhs.first < rhs.first)
				return (true);
		}

	template<typename T1, typename T2>
		bool operator>(const pair<T1, T2> &lhs,const pair<T1, T2> &rhs)
		{
			if (lhs.first != rhs.first)
				return (lhs.first > rhs.first);
			return lhs.second > rhs.second;
		}

	template<typename T1, typename T2>
		bool operator>=(const pair<T1, T2> &lhs,const pair<T1, T2> &rhs)
		{
			if (lhs.first != rhs.first || lhs.first < rhs.first)
				return (true);
		}
	
	template<typename T1, typename T2>
	pair<T1, T2> make_pair(T1 t, T2 u)
	{
		return pair<T1,T2>(t,u);
	}
}

#endif