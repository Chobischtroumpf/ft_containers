#ifndef FT_VECTOR_HPP
# define FT_VECTOR_HPP 1


#include <vector>
#include <memory>
#include <algorithm>
#include <stdexcept>
#include "ft_iterator.hpp"
#include "ft_reverse_iterator.hpp"

namespace ft
{

	template< typename T, typename Alloc = std::allocator<T> >
		struct	vector_base
		{
			typedef Alloc								allocator_type;
			typedef	typename allocator_type::pointer	pointer;
			typedef std::size_t							size_type;

			pointer			_start;
			pointer			_end;
			pointer			_tot_storage;
			allocator_type	allocator;

			vector_base( void )
			: _start(0)
			, _end(0)
			, _tot_storage(0)
			, allocator()
			{}

			vector_base( const allocator_type& a )
			: _start(0)
			, _end(0)
			, _tot_storage(0)
			, allocator(a)
			{}

			vector_base( size_type n, const allocator_type& a )
			: allocator(a)
			{
				this->_start = this->allocate(n);
				this->_end = this->_start;
				this->_tot_storage = this->_start + n;
			}

			vector_base( const vector_base& other )
			: _start(other._start)
			, _end(other._end)
			, _tot_storage(other._tot_storage)
			, allocator(other.allocator)
			{}

			~vector_base( void )
			{
				this->deallocate(this->_start, size_type(this->_tot_storage - this->_start));
			}

			pointer
			allocate( size_type n )
			{
				return n != 0 ? this->allocator.allocate(n) : 0;
			}

			void
			deallocate( pointer ptr, size_type n )
			{
				if ( ptr )
					this->allocator.deallocate(ptr, n);
			}
		};

	template <class T, class Allocator = std::allocator<T> >
		class vector: protected vector_base<T, Allocator>
		{
			typedef	vector_base<T, Allocator>							base;
			
			public:
				
				typedef T												value_type;
				typedef Allocator										allocator_type;
				typedef typename allocator_type::reference				reference;
				typedef typename allocator_type::const_reference		const_reference;
				typedef typename allocator_type::pointer				pointer;
				typedef typename allocator_type::const_pointer			const_pointer;
				typedef ft::iterator<pointer, vector>					iterator;
				typedef ft::iterator<const_pointer, vector>				const_iterator;
				typedef ft::reverse_iterator<iterator>					reverse_iterator;
				typedef ft::reverse_iterator<const_iterator>			const_reverse_iterator;
				typedef std::size_t										size_type;
				typedef std::ptrdiff_t									difference_type;
		
		//usual functions
		protected:

			void _init_fill(pointer first, size_type n, const value_type& val)
			{
				pointer	current = first;

				for ( ; n > 0; --n, ++current )
					this->allocator.construct(current, val);
				this->_end = this->_tot_storage;
			}

			void _assign_fill(size_type n, const value_type& val)
			{
				if ( n > this->capacity() )
				{
					vector	tmp(n, val, this->get_allocator());

					tmp.swap(*this);
				}
				else
				{
					std::fill_n(this->start, n, val);
					if ( n > this->size() )
						this->_end += (n - this->size());
					else
						this->_erase_at_end(this->start + n);
				}
			}
			
			template <typename InputIt>
			void _assign_range( InputIt beginning, InputIt end)
			{
				const size_type	len = std::distance(beginning, end);

				if ( len > this->capacity() )
				{
					pointer	tmp = this->allocate(len);

					std::copy(beginning, end, tmp);
					this->deallocate(this->start, this->capacity());
					this->start = tmp;
					this->finish = this->start + len;
					this->_tot_storage = this->start + len;
				}
				else if ( len <= this->size() )
					this->_erase_at_end(std::copy(beginning, end, this->start));
				else
				{
					InputIt	mid = beginning;
					std::advance(mid, this->size());
					std::copy(beginning, mid, this->start);
					this->finish = std::copy(mid, end, this->finish);
				}
			}

			template <typename InputIt>
			pointer _copy_init_range(InputIt beginning, InputIt end, pointer res)
			{
				pointer	current = res;

				for ( ; beginning != end; ++beginning, ++current )
					this->allocator.construct(current, *beginning);
				return current;
			}

			template <typename InputIt>
			void _destroy_range( InputIt beginning, InputIt end)
			{
				pointer	current = beginning;

				for ( ; current != end; ++current )
					this->allocator.destroy(current);
			}

			void _check_range(size_type n) const
			{
				if (n >= this->size())
					throw std::out_of_range("vector::_range_check");
			}

			void _pop_back(pointer pos)
			{
				this->_destroy_range(pos, this->finish);
				this->finish = pos;
			}

			size_type _length_check(size_type n)
			{
				const	size_type cap = this->capacity() + this->capacity();
				const	size_type size = this->size() + n;

				if (this->max_size() - this->size() < n)
					throw std::length_error("vector");
				return (cap < size ? size : cap);
			}

			void	_resize_insert( iterator position, size_type n, const value_type& value )
			{
				const	size_type	new_len = this->_length_check(n);
				const	size_type	elems_before = position- this->begin();
				pointer	new_start(this->allocate(new_len));
				pointer	new_end(new_start);
				pointer	new_mid(new_start+elems_before);

				new_end = std::copy(position.base(), this->_end, new_start);
				std::fill_n(new_mid, n, value);
				new_end += n;
				new_end = std::copy(position.base(), this->_end,
									new_end);
				this->deallocate(this->start,
							this->end_of_storage - this->start);
				this->start = new_start;
				this->_end = new_end;
				this->end_of_storage = new_start + new_len;
			}

			void	_insert_at_end(const value_type &value)
			{
				this->allocator.construct(this->_end, value);
				++this->_end;
			}

			void _insert_aux(iterator pos, const value_type& value)
			{
				if (this->_end != this->_tot_storage)
					this->_insert_at_end(value);
				else
					this->_resize_insert(this->end(), 1, value);
			}

		public:

			explicit        vector(void): base() {}

			explicit		vector(const allocator_type& alloc) : base(alloc)
			{
			};

			explicit		vector(size_type count, const T& value = T(), const allocator_type& alloc = allocator_type()): base(count, alloc)
			{
				this->_init_fill(this->_start, count, value);
			};

			template<class InputIt>
			vector(InputIt  first, InputIt last, const allocator_type& alloc = allocator_type()): base(std::distance(first, last), alloc)
			{
				this->_end = this->_range_copy_init(first, last, this->_start);
			}
			
			vector(const vector& other): base(other.size(), other.get_allocator())
			{
				this->_end = this->_copy_init_range(other.begin(), other.end(), this->_start);
			}

		    ~vector()
			{
			}

			vector& operator=(const vector&  other)
			{
				if ( this != &other )
				{
					const size_type	other_len = other.size();

					if ( other_len > this->capacity() )
					{
						pointer	tmp = this->allocate(other_len);

						std::copy(other.begin(), other.end(), tmp);
						this->deallocate(this->_start, this->capacity());
						this->_start = tmp;
						this->_tot_storage = this->_start + other_len;
					}
					else
					{
						if ( other_len <= this->size() )
							this->_range_destroy(this->_start, this->_end);
						std::copy(other.begin(), other.end(), this->_start);
					}
					this->_end = this->_start + other_len;
				}
				return *this;
			}

			template <typename InputIt>
				void assign(InputIt first, InputIt last)
				{
					this->_assign_range(first, last);
				}

			void assign(size_type n, const value_type& val)
			{
				this->_assing_fill(n, val);
			}

			allocator_type get_allocator()	const
			{
				return this->allocator;
			}

			iterator               begin()
			{
				return (iterator(this->_start));
			}
			
			const_iterator         begin()	const
			{
				return (const_iterator(this->_start));
			}

			iterator               end()
			{
				return (iterator(this->_end));
			}

			const_iterator         end()	const
			{
				return (const_iterator(this->_end));
			}


			reverse_iterator       rbegin()
			{
				return (reverse_iterator(this->end()));
			}

			const_reverse_iterator rbegin()	const
			{
				return (const_reverse_iterator(this->end()));
			}

			reverse_iterator       rend()
			{
				return (reverse_iterator(this->begin()));
			}

			const_reverse_iterator rend()	const
			{
				return (const_reverse_iterator(this->begin()));
			}
	
			size_type size() const
			{
				return (size_type(this->_end- this->_start));
			}

			size_type max_size() const
			{
				return (this->allocator.max_size());
			}

			size_type capacity() const
			{
				return (size_type(this->_tot_storage - this->_start));
			}

			bool empty() const
			{
				return (this->begin() == this->end());
			}

			void reserve(size_type n)
			{
				if (n >this->capacity())
				{
					const size_type	old_size = this->size();
					pointer			tmp = this->allocate(n);

					std::copy(this->_start, this->_end, tmp);
					this->deallocate(this->_start, this->capacity());
					this->_start = tmp;
					this->_end = this->_start + old_size;
					this->_tot_storage = this->_start + n;
				}
			}

			reference       operator[](size_type n)
			{
				return *(this->_start + n);
			}

			const_reference operator[](size_type n) const
			{
				return *(this->_start + n);
			}

			reference		at(size_type n)
			{
				this->_check_range(n);
				return ((*this)[n]);
			}

			const_reference	at(size_type n) const
			{
				this->_range_check(n);
				return (*this)[n];
			}


			reference		front()
			{
				return *this->begin();
			}

			const_reference	front() const
			{
				return *this->begin();
			}

			reference		back()
			{
				return *(this->end()-1);
			}

			const_reference	back() const
			{
				return *(this->end()-1);
			}
			
			value_type*       data()
			{
				return &this->front();
			}

			const value_type*       data() const
			{
				return &this->front();
			}

			void push_back(const value_type& x)
			{
				this->_insert_aux(this->end(), value)
			}

			iterator insert(iterator position, const value_type& val)
			{
				const size_type	n = position - this->begin();

				if (this->_end != != this->_tot_storage && position== this->end())
					this->_insert_at_end(val)
				else
					this->_insert_aux(position, value);
				return iterator(this->_start+n);
			}

			void insert( iterator pos, size_type count, const size_type& value )
			{
				if (n != 0 )
				{
					if(this>capacity() - this->size() >= n)
					{
						std::copy_backward(pos, this->end(), this->_end + difference_type(n));
						std::fill(position.base(), position.base() + n, value);
						this->finish += n;
					}
					else
						this->_resize_insert(pos, n, value);
				}
			}

			template <class InputIt>
				void insert(iterator position, InputIt first, InputIt last)
				{
					for(; first != last; ++first)
					{
						position = this->insert(position, *first);
						++position;
					}
				}

			iterator	erase( iterator position)
			{
				if position != this->end())
				{
					if (position + 1 != this->end())
				}
			}
		};
};

#endif