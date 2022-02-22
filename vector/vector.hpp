#ifndef VECTOR_HPP
# define VECTOR_HPP 1

/*
	vector synopsis

namespace std
{

template <class T, class Allocator = allocator<T> >
class vector
{
public:
	typedef T                                        value_type;
	typedef Allocator                                allocator_type;
	typedef typename allocator_type::reference       reference;
	typedef typename allocator_type::const_reference const_reference;
	typedef implementation-defined                   iterator;
	typedef implementation-defined                   const_iterator;
	typedef typename allocator_type::size_type       size_type;
	typedef typename allocator_type::difference_type difference_type;
	typedef typename allocator_type::pointer         pointer;
	typedef typename allocator_type::const_pointer   const_pointer;
	typedef std::reverse_iterator<iterator>          reverse_iterator;
	typedef std::reverse_iterator<const_iterator>    const_reverse_iterator;

	vector()
		noexcept(is_nothrow_default_constructible<allocator_type>::value);
	explicit vector(const allocator_type&);
	explicit vector(size_type n);
	vector(size_type n, const value_type& value, const allocator_type& = allocator_type());
	template <class InputIterator>
		vector(InputIterator first, InputIterator last, const allocator_type& = allocator_type());
	vector(const vector& x);
	vector(vector&& x)
		noexcept(is_nothrow_move_constructible<allocator_type>::value);
	vector(initializer_list<value_type> il);
	vector(initializer_list<value_type> il, const allocator_type& a);
	~vector();
	vector& operator=(const vector& x);
	vector& operator=(initializer_list<value_type> il);
	template <class InputIterator>
		void assign(InputIterator first, InputIterator last);
	void assign(size_type n, const value_type& u);
	void assign(initializer_list<value_type> il);

	allocator_type get_allocator() const noexcept;

	iterator               begin() noexcept;
	const_iterator         begin()   const noexcept;
	iterator               end() noexcept;
	const_iterator         end()     const noexcept;

	reverse_iterator       rbegin() noexcept;
	const_reverse_iterator rbegin()  const noexcept;
	reverse_iterator       rend() noexcept;
	const_reverse_iterator rend()    const noexcept;

	const_iterator         cbegin()  const noexcept;
	const_iterator         cend()    const noexcept;
	const_reverse_iterator crbegin() const noexcept;
	const_reverse_iterator crend()   const noexcept;

	size_type size() const noexcept;
	size_type max_size() const noexcept;
	size_type capacity() const noexcept;
	bool empty() const noexcept;
	void reserve(size_type n);
	void shrink_to_fit() noexcept;

	reference       operator[](size_type n);
	const_reference operator[](size_type n) const;
	reference       at(size_type n);
	const_reference at(size_type n) const;

	reference       front();
	const_reference front() const;
	reference       back();
	const_reference back() const;

	value_type*       data() noexcept;
	const value_type* data() const noexcept;

	void push_back(const value_type& x);
	void push_back(value_type&& x);
	void pop_back();

	template <class... Args> iterator emplace(const_iterator position, Args&&... args);
	iterator insert(const_iterator position, const value_type& x);
	iterator insert(const_iterator position, value_type&& x);
	iterator insert(const_iterator position, size_type n, const value_type& x);
	template <class InputIterator>
		iterator insert(const_iterator position, InputIterator first, InputIterator last);
	iterator insert(const_iterator position, initializer_list<value_type> il);

	iterator erase(const_iterator position);
	iterator erase(const_iterator first, const_iterator last);

	void clear() noexcept;

	void resize(size_type sz);
	void resize(size_type sz, const value_type& c);

	bool __invariants() const;
};
*/

#include <vector>
#include <memory>
#include "iterators/iterator.hpp"

namespace ft
{
	// template <class T, class Allocator = std::allocator<T> >
	// 	struct vector_base
	// 	{
	// 		typedef Allocator allocator_type;
	// 		typedef typename allocator_type::pointer pointer;
	// 		typedef std::size_t	size_type;

	// 		pointer	start;
	// 		pointer finish;
	// 		pointer end_of_storage;
	// 		allocator_type allocator;

	// 		vector_base(void):start(0),finish(0),end_of_storage(0),allocator()
	// 		{}

	// 		vector_base( const allocator_type& alloc): start(0),finish(0),end_of_storage(0), allocator(alloc)
	// 		{}

	// 		vector_base(size_type n, const allocator_type& a):allocator(a)
	// 		{
	// 			this->start = this->allocate(n);
	// 			this->finish = this->start;
	// 			this->end_of_storage = this->start + n;
	// 		}

	// 		~vector_base(void)
	// 		{
	// 			this->deallocate(this->start, size_type(this->end_of_storage - this->start));
	// 		}

	// 		pointer allocate(size_type n)
	// 		{
	// 			return (n != 0 ? this->allocator.allocate(n) : 0);
	// 		}

	// 		void deallocate(pointer ptr, size_type n)
	// 		{
	// 			if (ptr)
	// 				this->allocator.deallocate(ptr, n);
	// 		}
	// 	};

	template <class T, class Allocator = std::allocator<T> >
		class Vector
		{
		public:
			typedef T value_type;
			typedef Allocator allocator_type;
			typedef typename allocator_type::reference reference;
			typedef typename allocator_type::const_reference const_reference;
			typedef ft::Iter<pointer, vector> iterator;
			typedef ft::Iter<const_pointer, vector> const_iterator;
			typedef ft::reverse_iterator<iterator> reverse_iterator;
			typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
			typedef typename allocator_type::pointer pointer;
			typedef typename allocator_type::const_pointer const_pointer;
			typedef typename allocator_type::size_type size_type;
			typedef typename allocator_type::difference_type difference_type;
		
		private:
			T   			_vector;
			pointer			_ptr;
			allocator_type	_base;
			size_type		_size;
			size_type		_capacity;
		public:

			explicit		Vector(const allocator_type& alloc = allocator_type()) : _base(alloc), _ptr(NULL), size(0), _capacity(0)
			{
				this->_ptr = this->_base.allocate(0);
			};

			explicit		Vector(size_type count, const T& value = T(), const allocator_type& alloc = allocator_type())
			{
				this->_ptr = this->_base.allocate(count);
				for (size_t i = 0; i < count; i++)
					this->_base.construct(this->_ptr + i, value);
			};

			template<class InputIt>
			Vector(InputIt  first, InputIt last, const allocator_type& alloc = allocator_type())
			{
				for (InputIt it = first; it != last; it++)
				{
					
				}
			}
			
			vector(const vector& other)
			{

			}


			
		};
}

#endif