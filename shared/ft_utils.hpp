#ifndef	FT_UTILS_HPP
#define FT_UTILS_HPP

namespace ft
{

	template<class T>
	struct non_const { 
	    typedef T type;
	};

	template<class T>
	struct non_const <const T> {
		typedef T type;
	};

	template<class InputIt1, class InputIt2>
	bool	equal(InputIt1 first, InputIt1 last, InputIt2 first2)
	{
		for (; first != last; ++first, ++first2)
		{
			if (!(*first == *first2))
				return (false);
		}
		return (true);
	}

	template< class InputIt1, class InputIt2, class BinaryPredicate >
	bool	equal( InputIt1 first1, InputIt1 last1,
					InputIt2 first2, BinaryPredicate p )
	{
		for ( ; first1 != last1; ++first1, ++first2 )
		{
			if ( !p( *first1, *first2 ) )
				return false;
		}
		return true;
	}

	/*
	** This `choose` struct is needed for non-const and const iterator
	** implementation without duplicating the code.
	** copyright - Matt Austern. Generic Programming and the STL
	*/

	template<bool flag, class IsTrue, class IsFalse>
	struct choose;

	template<class IsTrue, class IsFalse>
	struct choose<true, IsTrue, IsFalse> {
		typedef IsTrue type;
	};

	template<class IsTrue, class IsFalse>
	struct choose<false, IsTrue, IsFalse> {
		typedef IsFalse type;
	};

	template<typename T, T v>
	struct integral_constant {
		typedef integral_constant<T, v> type;
		typedef T                       value_type;
		static const T                  value = v;
		operator value_type() const { return value; }
	};

	// lexicographical compare implementation
	template<class InputIt1, class InputIt2>
	bool	lexicographical_compare(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2)
	{
		for(; first1 != last1 && first2 != last2; ++first1, ++ first2)
		{
			if ( *first1 < *first2 )
				return (true);
			if ( *first2 < *first2 )
				return (false);
		}
		return (first1 == last1 && first2 != last2);
	}

	template< class InputIt1, class InputIt2, class Compare>
	bool	lexicographical_compare(InputIt1 first1, InputIt1 last1,
							InputIt2 first2, InputIt2 last2, Compare cmp)
	{
		for(; first1 != last1 && first2 != last2; ++first1, ++ first2)
		{
			if ( cmp(*first1, *first2) )
				return (true);
			if ( cmp(*first2, *first2) )
				return (false);
		}
		return (first1 == last1 && first2 != last2);
	}

	//is_integral implementation
	typedef ft::integral_constant<bool, true>   true_type;
	typedef ft::integral_constant<bool, false>  false_type;

	template<typename> struct is_integral : ft::false_type {};
	template<> struct is_integral<bool> : ft::true_type {};
	template<> struct is_integral<char> : ft::true_type {};
	template<> struct is_integral<wchar_t> : ft::true_type {};
	template<> struct is_integral<short> : ft::true_type {};
	template<> struct is_integral<int> : ft::true_type {};
	template<> struct is_integral<long> : ft::true_type {};
	template<> struct is_integral<long long> : ft::true_type {};
	template<> struct is_integral<unsigned char> : ft::true_type {};
	template<> struct is_integral<unsigned short> : ft::true_type {};
	template<> struct is_integral<unsigned int> : ft::true_type {};
	template<> struct is_integral<unsigned long> : ft::true_type {};
	template<> struct is_integral<unsigned long long> : ft::true_type {};
	template<> struct is_integral<const bool> : ft::true_type {};
	template<> struct is_integral<const char> : ft::true_type {};
	template<> struct is_integral<const wchar_t> : ft::true_type {};
	template<> struct is_integral<const short> : ft::true_type {};
	template<> struct is_integral<const int> : ft::true_type {};
	template<> struct is_integral<const long> : ft::true_type {};
	template<> struct is_integral<const long long> : ft::true_type {};
	template<> struct is_integral<const unsigned char> : ft::true_type {};
	template<> struct is_integral<const unsigned short> : ft::true_type {};
	template<> struct is_integral<const unsigned int> : ft::true_type {};
	template<> struct is_integral<const unsigned long> : ft::true_type {};
	template<> struct is_integral<const unsigned long long> : ft::true_type {};
	template<> struct is_integral<signed char> : ft::true_type {};
	template<> struct is_integral<const signed char> : ft::true_type {};

	//enable_if

	template< bool B, class T = void >
	struct	enable_if {};

	template< class T >
	struct enable_if<true, T>{typedef T	type;};

	//pair
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
	pair<T1, T2> make_pair(T1 t, T2 u)
	{
		return pair<T1,T2>(t,u);
	}

	//operator overloads
	template<typename T1, typename T2>
		bool operator==(const pair<T1, T2> &lhs,const pair<T1, T2> &rhs)
		{
			return (lhs.first == rhs.first && lhs.second && rhs.second);
		}

	template<typename T1, typename T2>
		bool operator!=(const pair<T1, T2> &lhs,const pair<T1, T2> &rhs)
		{
			return !((lhs.first == rhs.first) || (lhs.second && rhs.second));
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
	
}

#endif