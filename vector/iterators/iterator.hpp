#ifndef ITERATOR_HPP
#define ITERATOR_HPP 1
#include <iterator>

namespace ft
{
	template<class Iter>
	struct iterator_traits
	{
		typedef typename Iter::difference_type difference_type;
		typedef typename Iter::value_type value_type;
		typedef typename Iter::pointer pointer;
		typedef typename Iter::reference reference;
		typedef typename Iter::iterator_category iterator_category;
	};
	//iterator traits 
	template<class T>
	struct iterator_traits<T*>
	{
		typedef ptrdiff_t difference_type;
		typedef T value_type;
		typedef T* pointer;
		typedef T& reference;
		typedef random_access_iterator_tag iterator_category;
	};
	//iterator traits but const
	template<class T>
	struct iterator_traits<const T*>
	{
		typedef ptrdiff_t difference_type;
		typedef T value_type;
		typedef T* pointer;
		typedef T& reference;
		typedef random_access_iterator_tag iterator_category;
	};

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

	template <class Iterator>
	class reverse_iterator
		: public iterator<typename iterator_traits<Iterator>::iterator_category,
						typename iterator_traits<Iterator>::value_type,
						typename iterator_traits<Iterator>::difference_type,
						typename iterator_traits<Iterator>::pointer,
						typename iterator_traits<Iterator>::reference>
	{
	protected:
		Iterator current;
	public:
		typedef Iterator                                            iterator_type;
		typedef typename iterator_traits<Iterator>::difference_type difference_type;
		typedef typename iterator_traits<Iterator>::reference       reference;
		typedef typename iterator_traits<Iterator>::pointer         pointer;

		reverse_iterator(): current(iterator()){}

		explicit reverse_iterator(Iterator x) : current(x) {}

		template <class U>
		reverse_iterator(const reverse_iterator<U>& u) : current(u.base())
		{}

		template <class U>
		reverse_iterator& operator=(const reverse_iterator<U>& u) {current = u.base;return *this;}

		Iterator base() const {return current;}

		reference operator*() const {Iterator _tmp = current; return *--_tmp;}

		pointer   operator->() const {}

		reverse_iterator& operator++() {--current;return *this;}

		reverse_iterator  operator++(int) {reverse_iterator _tmp(*this); --current; return _tmp;}

		reverse_iterator& operator--() {++current; return *this;}

		reverse_iterator  operator--(int) {reverse_iterator _tmp(*this); ++current; return _tmp;}

		reverse_iterator  operator+ (difference_type n) const {return reverse_iterator(current - __n);}

		reverse_iterator& operator+=(difference_type n) {current -= __n; return *this;}

		reverse_iterator  operator- (difference_type n) const {return reverse_iterator(current + __n);}

		reverse_iterator& operator-=(difference_type n) {current += __n; return *this;}

		reference         operator[](difference_type n) const {return *(*this + __n);}
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

	//Iter vector//
	template <class T>
	class Iter
	{
		public:
		    typedef Iter											iterator_type;
			typedef typename iterator_traits<T*>::iterator_category	iterator_category;
			typedef typename iterator_traits<T*>::value_type		value_type;
			typedef typename iterator_traits<T*>::difference_type	difference_type;
			typedef typename iterator_traits<T*>::reference			reference;
			typedef typename iterator_traits<T*>::pointer			pointer;
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

		reference		operator*() const {Iterator _tmp = current; return *++_tmp;}

		pointer			operator->() const {}

		iterator_type&	operator++() {++current;return *this;}

		iterator_type	operator++(int) {iterator_type _tmp(*this); ++current; return _tmp;}

		iterator_type&	operator--() {--current; return *this;}

		iterator_type	operator--(int) {iterator_type _tmp(*this); --current; return _tmp;}

		iterator_type	operator+ (difference_type n) const {return iterator_type(current + n);}

		iterator_type&	operator+=(difference_type n) {current += n; return *this;}

		iterator_type	operator- (difference_type n) const {return iterator_type(current - n);}

		iterator_type&	operator-=(difference_type n) {current -= n; return *this;}

		reference		operator[](difference_type n) const {return *(*this + n);}

	}

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
	operator-(typename Iter<T>::difference_type _n, const Iter<T>& _x)
	{
		return reverse_iterator<T>(_x.base() - _n);
	}
}

#endif