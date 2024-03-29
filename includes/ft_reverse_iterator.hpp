#ifndef FT_REVERSE_ITERATOR
# define FT_REVERSE_ITERATOR 1

#include "ft_iterator_traits.hpp"
// #include <iterator>


namespace ft
{
	template <class Iterator>
		class reverse_iterator
		: public std::iterator<typename iterator_traits<Iterator>::iterator_category,
						typename iterator_traits<Iterator>::value_type,
						typename iterator_traits<Iterator>::difference_type,
						typename iterator_traits<Iterator>::pointer,
						typename iterator_traits<Iterator>::reference>
	{
	protected:
		Iterator	current;
		typedef		ft::iterator_traits<Iterator>					traits_type;

	public:
		typedef Iterator                                            iterator_type;
		typedef typename iterator_traits<Iterator>::difference_type difference_type;
		typedef typename iterator_traits<Iterator>::reference       reference;
		typedef typename iterator_traits<Iterator>::pointer         pointer;

		reverse_iterator(): current(){}

		explicit reverse_iterator(Iterator x) : current(x) {}

		template <class U>
		reverse_iterator(const reverse_iterator<U>& u) : current(u.base())
		{}

		template <class U>
		reverse_iterator& operator=(const reverse_iterator<U>& u)
		{
			current = u.base;
			return *this;
		}

		Iterator base() const
		{
			return current;
		}

		reference operator*() const
		{
			Iterator _tmp = current;
			return *--_tmp;
		}

		pointer   operator->() const {}

		reverse_iterator& operator++()
		{
			--current;
			return *this;
		}

		reverse_iterator  operator++(int) 
		{
			reverse_iterator _tmp(*this);
			--current;
			return _tmp;
		}

		reverse_iterator& operator--()
		{
			++current;
			return *this;
		}

		reverse_iterator  operator--(int)
		{
			reverse_iterator _tmp(*this);
			++current;
			return _tmp;
		}

		reverse_iterator  operator+(difference_type n) const
		{
			return reverse_iterator(current - n);
		}

		reverse_iterator& operator+=(difference_type n) 
		{
			current -= n;
			return *this;
		}

		reverse_iterator  operator- (difference_type n) const
		{
			return reverse_iterator(current + n);
		}

		reverse_iterator& operator-=(difference_type n)
		{
			current += n;
			return *this;
		}

		reference         operator[](difference_type n) const
		{
			return *(*this + n);
		}
	};
	
	template <class Iter1, class Iter2>
	bool operator==(const reverse_iterator<Iter1>& _it1, const reverse_iterator<Iter2>& _it2)
	{
		return _it1.base() == _it2.base();
	}

	template <class Iter1, class Iter2>
	bool operator!=(const reverse_iterator<Iter1>& _it1, const reverse_iterator<Iter2>& _it2)
	{
		return _it1.base() != _it2.base();
	}

	template <class Iter1, class Iter2>
	bool operator>(const reverse_iterator<Iter1>& _it1, const reverse_iterator<Iter2>& _it2)
	{
		return _it1.base() < _it2.base();
	}

		template <class Iter1, class Iter2>
	bool operator<(const reverse_iterator<Iter1>& _it1, const reverse_iterator<Iter2>& _it2)
	{
		return _it1.base() > _it2.base();
	}

	template <class Iter1, class Iter2>
	bool operator>=(const reverse_iterator<Iter1>& _it1, const reverse_iterator<Iter2>& _it2)
	{
		return _it1.base() <= _it2.base();
	}

	template <class Iter1, class Iter2>
	bool operator<=(const reverse_iterator<Iter1>& _it1, const reverse_iterator<Iter2>& _it2)
	{
		return _it1.base() >= _it2.base();
	}
	
	template <class Iter1, class Iter2>
	bool operator-(const reverse_iterator<Iter1>& _it1, const reverse_iterator<Iter2>& _it2)
	{
		return _it1.base() - _it2.base();
	}
	
	
	template <class Iter>
	reverse_iterator<Iter>
	operator-(typename reverse_iterator<Iter>::difference_type _n, const reverse_iterator<Iter>& _x)
	{
		return reverse_iterator<Iter>(_x.base() - _n);
	}

}
#endif