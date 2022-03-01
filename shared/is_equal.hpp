#ifndef	FT_EQUAL_HPP
#define FT_EQUAL_HPP

namespace ft
{
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
}

#endif