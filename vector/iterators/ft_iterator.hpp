#ifndef ITERATOR_HPP
#define ITERATOR_HPP 1
#include <iterator>
#include "ft_iterator_traits.hpp"

namespace ft
{
	template<class Category, class T, class Distance = ptrdiff_t,
        class Pointer = T*, class Reference = T&>
	struct iterator
	{
		typedef T         value_type;
		typedef Distance  difference_type;
		typedef Pointer   pointer;
		typedef Reference reference;
		typedef Category  iterator_category;
	};

	
	//Iter vector//
	template <class T>
	class Iter
	{
		public:
		    typedef Iter												iterator_type;
			typedef typename ft::iterator_traits<T*>::iterator_category	iterator_category;
			typedef typename ft::iterator_traits<T*>::value_type		value_type;
			typedef typename ft::iterator_traits<T*>::difference_type	difference_type;
			typedef typename ft::iterator_traits<T*>::reference			reference;
			typedef typename ft::iterator_traits<T*>::pointer			pointer;
		private:
			pointer	current;
		
		//constructor//
		Iter() : current(iterator()){}
		explicit Iter(iterator_type _it) : current(_it){}

		//getter//
		iterator_type	base() const {}

		template <class U>
		iterator_type& operator=(const iterator_type<U>& u) {current = u.base;return *this;}

		Iter base() const {return current;}

		reference		operator*(void) const 
		{
			Iterator _tmp = current;
			return *++_tmp;
		}

		pointer			operator->(void) const
		{
			return this->current;
		}

		iterator_type&	operator++(void) 
		{
			++current;
			return *this;
		}

		iterator_type	operator++(int)
		{
			iterator_type _tmp(*this);
			++current;
			return _tmp;
		}

		iterator_type&	operator--() 
		{
			--current;
			return *this;
		}

		iterator_type	operator--(int)
		{
			iterator_type _tmp(*this);
			--current;
			return _tmp;
		}

		iterator_type	operator+(difference_type n) const
		{
			return iterator_type(current + n);
		}

		iterator_type&	operator+=(difference_type n)
		{
			current += n;
			return *this;
		}

		iterator_type	operator-(difference_type n) const
		{
			return iterator_type(current - n);
		}

		iterator_type&	operator-=(difference_type n)
		{
			current -= n;
			return *this;
		}

		reference		operator[](difference_type n) const
		{
			return *(*this + n);
		}

	};

	template <class T1, class T2>
	bool operator==(const Iter<T1>& _it1, const Iter<T2>& _it2)
	{
		return _it1.base() == _it2.base();
	}

	template <class T1, class T2>
	bool operator!=(const Iter<T1>& _it1, const Iter<T2>& _it2)
	{
		return _it1.base() != _it2.base();
	}

	template <class T1, class T2>
	bool operator>(const Iter<T1>& _it1, const Iter<T2>& _it2)
	{
		return _it1.base() > _it2.base();
	}

		template <class T1, class T2>
	bool operator<(const Iter<T1>& _it1, const Iter<T2>& _it2)
	{
		return _it1.base() < _it2.base();
	}

	template <class T1, class T2>
	bool operator>=(const Iter<T1>& _it1, const Iter<T2>& _it2)
	{
		return _it1.base() >= _it2.base();
	}

	template <class T1, class T2>
	bool operator<=(const Iter<T1>& _it1, const Iter<T2>& _it2)
	{
		return _it1.base() <= _it2.base();
	}
	
	template <class T1, class T2>
	bool operator-(const Iter<T1>& _it1, const Iter<T2>& _it2)
	{
		return _it1.base() - _it2.base();
	}

	template <class T>
	bool operator-(typename Iter<T>::difference_type _n, const Iter<T>& _x)
	{
		return reverse_iterator<T>(_x.base() - _n);
	}

	template <class T>
	bool operator-(typename Iter<T>::difference_type _n, const Iter<T>& _x)
	{
		return reverse_iterator<T>(_x.base() + _n);
	}
}

#endif