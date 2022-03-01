#ifndef FT_VECTOR_HPP
# define FT_VECTOR_HPP

# include <cstddef>
# include <memory>
# include <stdexcept>
# include <algorithm>
# include <iterator>
# include "ft_iterator.hpp"
# include "ft_reverse_iterator.hpp"
# include "lexicographical_compare.hpp"
# include "is_equal.hpp"
# include "is_integral.hpp"
# include "enable_if.hpp"

namespace	ft
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
				if (n != 0)
					return this->allocator.allocate(n);
				else
					return 0;
				
			}

			void
			deallocate( pointer ptr, size_type n )
			{
				if ( ptr )
					this->allocator.deallocate(ptr, n);
			}
		};

	template< typename T, typename Allocator = std::allocator<T> >
		class	vector : protected vector_base<T, Allocator>
		{
			typedef vector_base<T, Allocator>							base;
			
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

			explicit        vector(void): base() {}

			explicit		vector(const allocator_type& alloc) : base(alloc)
			{
			};

			explicit		vector(size_type count, const T& value = T(), const allocator_type& alloc = allocator_type()): base(count, alloc)
			{
				this->_init_fill(this->_start, count, value);
			};

			template<class InputIt>
			vector(typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type first, InputIt last, const allocator_type& alloc = allocator_type()): base(std::distance(first, last), alloc)
			{
				this->_end = this->_copy_init_range(first, last, this->_start);
			}
			
			vector(const vector& other): base(other.size(), other.get_allocator())
			{
				this->_end = this->_copy_init_range(other.begin(), other.end(), this->_start);
			}

		    ~vector()
			{}

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
							this->_destroy_range(this->_start, this->_end);
						std::copy(other.begin(), other.end(), this->_start);
					}
					this->_end = this->_start + other_len;
				}
				return *this;
			}

			protected:

			void _init_fill( pointer first, size_type n, const value_type& value )
			{
				pointer	current = first;

				for ( ; n > 0; --n, ++current )
					this->allocator.construct(current, value);
				this->_end = this->_tot_storage;
			}

			void _assign_fill(size_type n, const value_type& value)
			{
				if ( n > this->capacity() )
				{
					vector	tmp(n, value, this->get_allocator());

					tmp.swap(*this);
				}
				else
				{
					std::fill_n(this->_start, n, value);
					if ( n > this->size() )
						this->_end += (n - this->size());
					else
						this->_pop_back(this->_start + n);
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
					this->deallocate(this->_start, this->capacity());
					this->_start = tmp;
					this->_end = this->_start + len;
					this->_tot_storage = this->_start + len;
				}
				else if ( len <= this->size() )
					this->_pop_back(std::copy(beginning, end, this->_start));
				else
				{
					InputIt	mid = beginning;
					std::advance(mid, this->size());
					std::copy(beginning, mid, this->_start);
					this->_end = std::copy(mid, end, this->_end);
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

			void _pop_back(pointer pos)
			{
				this->_destroy_range(pos, this->_end);
				this->_end = pos;
			}

			public:

			template <typename InputIt>
					void assign(typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type first, InputIt last)
					{
						this->_assign_range(first, last);
					}

			void assign(size_type n, const value_type& val)
			{
				this->_assign_fill(n, val);
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
				return (size_type(this->_end - this->_start));
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

		protected:

			void _check_range(size_type n) const
			{
				if (n >= this->size())
					throw std::out_of_range("vector::_check_range");
			}

		public:

			reference		at(size_type n)
			{
				this->_check_range(n);
				return ((*this)[n]);
			}

			const_reference	at(size_type n) const
			{
				this->_check_range(n);
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

			void pop_back()
			{
				--this->_end;
				this->allocator.destroy(this->_end);
			}

			protected:

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
				const size_type	new_len = this->_length_check(n);
				const size_type	elems_before = position - this->begin();
				pointer			new_start(this->allocate(new_len));
				pointer			new_finish(new_start);
				pointer			new_mid(new_start + elems_before);

				new_finish = std::copy(this->_start, position.base(),
									new_start);
				std::fill_n(new_mid, n, value);
				new_finish += n;
				new_finish = std::copy(position.base(), this->_end,
									new_finish);
				this->deallocate(this->_start,
							this->_tot_storage - this->_start);
				this->_start = new_start;
				this->_end = new_finish;
				this->_tot_storage = new_start + new_len;
			}

				void	_insert_at_end(const value_type &value)
			{
				this->allocator.construct(this->_end, value);
				++this->_end;
			}

				void _insert_aux(iterator pos, const value_type& value)
				{
					if (this->_end != this->_tot_storage)
					{
						this->allocator.construct(this->_end, *(this->_end - 1));
						++this->_end;
						std::copy_backward(pos.base(), this->_end - 2, this->_end - 1);
						*pos = value;
					}
					else
						this->_resize_insert(pos, 1, value);
				}

			public:

			void push_back(const value_type& x)
			{
				if (this->_end != this->_tot_storage)
					this->_insert_at_end(x);
				else
					this->_insert_aux(this->end(), x);
			}

			iterator insert(iterator position, const value_type& val)
			{
				const size_type	n = position - this->begin();

				if (this->_end != this->_tot_storage && position== this->end())
					this->_insert_at_end(val);
				else
					this->_insert_aux(position, val);
				return iterator(this->_start+n);
			}

			void insert( iterator pos, size_type count, const size_type& value )
			{
				if (count != 0 )
				{
					if(this->capacity() - this->size() >= count)
					{
						std::copy_backward(pos, this->end(), this->_end + difference_type(count));
						std::fill(pos.base(), pos.base() + count, value);
						this->_end += count;
					}
					else
						this->_resize_insert(pos, count, value);
				}
			}

			template <class InputIt>
				void insert(iterator position, typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type first, InputIt last)
				{
					for(; first != last; ++first)
					{
						position = this->insert(position, *first);
						++position;
					}
				}

			iterator	erase( iterator position)
			{
				if (position != this->end())
				{
					if (position + 1 != this->end())
						std::copy(position.base() + 1, this->_end, position.base());
					--this->_end;
					this->allocator.destroy(this->_end);
				}
				return(position);
			}

			iterator	erase(iterator beginning, iterator end)
			{
				if (beginning != end)
				{
					if (end != this->end())
						std::copy(end.base(), this->_end, beginning.base());
					this->_pop_back(beginning.base() + (this->_end - end.base()));
				}
				return beginning;
			}

			void swap(vector& other)
			{
				std::swap(this->_start, other._start);
				std::swap(this->_end, other._end);
				std::swap(this->_tot_storage, other._tot_storage);
				std::swap(this->allocator, other.allocator);
			}

			void clear()
			{
				this->_pop_back(this->_start);
			}

			void
			resize( size_type n, T value = T() )
			{
				if (n > this->size())
					this->insert(this->end(), n - this->size(), value);
				else if (n < this->size())
					this->_pop_back(this->_start + n);
			}
	};


	template< typename T, typename Alloc >
		inline bool	operator==( const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs )
		{
			return (lhs.size() == rhs.size()
				&& ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
		}

	template< typename T, typename Alloc >
		inline bool	operator!=( const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs )
		{
			return !(lhs == rhs);
		}

	template< typename T, typename Alloc >
		inline bool	operator<( const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs )
		{
			return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
		}

	template< typename T, typename Alloc >
		inline bool	operator>( const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs )
		{
			return rhs < lhs;
		}

	template< typename T, typename Alloc >
		inline bool	operator<=( const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs )
		{
			return !(rhs < lhs);
		}

	template< typename T, typename Alloc >
		inline bool	operator>=( const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs )
		{
			return !(lhs < rhs);
		}

	template< typename T, typename Alloc >
		inline void	swap( vector<T, Alloc>& lhs, vector<T, Alloc>& rhs)
		{
			lhs.swap(rhs);
		}
		
};

#endif