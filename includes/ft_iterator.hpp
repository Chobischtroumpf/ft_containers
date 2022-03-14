#ifndef FT_ITERATOR_HPP
# define FT_ITERATOR_HPP 1

# include "ft_iterator_traits.hpp"

namespace	ft
{
	template< typename Iterator, typename Container >
		class	iterator
		{
		protected:
			Iterator	current;

		public:
			typedef typename ft::iterator_traits<Iterator>::iterator_category	iterator_category;
			typedef typename ft::iterator_traits<Iterator>::value_type			value_type;
			typedef typename ft::iterator_traits<Iterator>::difference_type		difference_type;
			typedef typename ft::iterator_traits<Iterator>::pointer				pointer;
			typedef typename ft::iterator_traits<Iterator>::reference			reference;

			iterator( void )
			: current()
			{}

			explicit
			iterator( const Iterator& x )
			: current(x)
			{}

			template< typename Iter >
				iterator( const iterator<Iter, Container>& other )
				: current(other.base())
				{}


				iterator( iterator_category iter_cat, value_type val, difference_type diff, pointer ptr, reference ref)
				: iterator_category(iter_cat), value_type(val), difference_type(diff), pointer(ptr), reference(ref)
				{}

			const Iterator&
			base( void ) const
			{
				return this->current;
			}

			reference
			operator*( void ) const
			{
				return *(this->current);
			}

			pointer
			operator->( void ) const
			{
				return this->current;
			}

			iterator&
			operator++( void )
			{
				++this->current;
				return *this;
			}

			iterator&
			operator--( void )
			{
				--this->current;
				return *this;
			}

			iterator
			operator++( int )
			{
				return iterator(this->current++);
			}

			iterator
			operator--( int )
			{
				return iterator(this->current--);
			}

			iterator
			operator+( difference_type n ) const
			{
				return iterator(this->current + n);
			}

			iterator&
			operator+=( difference_type n )
			{
				this->current += n;
				return *this;
			}

			iterator
			operator-( difference_type n ) const
			{
				return iterator(this->current - n);
			}

			iterator&
			operator-=( difference_type n )
			{
				this->current -= n;
				return *this;
			}

			reference
			operator[]( difference_type n ) const
			{
				return this->current[n];
			}
		};

	template< typename IteratorL, typename IteratorR, typename Container >
		inline bool
		operator==( const iterator<IteratorL, Container>& lhs,
			const iterator<IteratorR, Container>& rhs )
		{
			return lhs.base() == rhs.base();
		}

	template< typename IteratorL, typename IteratorR, typename Container >
		inline bool
		operator!=( const iterator<IteratorL, Container>& lhs,
			const iterator<IteratorR, Container>& rhs )
		{
			return !(lhs == rhs);
		}

	template< typename IteratorL, typename IteratorR, typename Container >
		inline bool
		operator<( const iterator<IteratorL, Container>& lhs,
			const iterator<IteratorR, Container>& rhs )
		{
			return lhs.base() < rhs.base();
		}

	template< typename IteratorL, typename IteratorR, typename Container >
		inline bool
		operator<=( const iterator<IteratorL, Container>& lhs,
			const iterator<IteratorR, Container>& rhs )
		{
			return !(rhs < lhs);
		}

	template< typename IteratorL, typename IteratorR, typename Container >
		inline bool
		operator>( const iterator<IteratorL, Container>& lhs,
			const iterator<IteratorR, Container>& rhs )
		{
			return rhs < lhs;
		}

	template< typename IteratorL, typename IteratorR, typename Container >
		inline bool
		operator>=( const iterator<IteratorL, Container>& lhs,
			const iterator<IteratorR, Container>& rhs )
		{
			return !(lhs < rhs);
		}

	template< typename IteratorL, typename IteratorR, typename Container >
		inline typename iterator<IteratorL, Container>::difference_type
		operator-( const iterator<IteratorL, Container>& lhs,
			const iterator<IteratorR, Container>& rhs )
		{
			return lhs.base() - rhs.base();
		}

	template< typename Iterator, typename Container >
		inline iterator<Iterator, Container>
		operator+( typename iterator<Iterator, Container>::difference_type n,
			const iterator<Iterator, Container>& x )
		{
			return iterator<Iterator, Container>(x.base() + n);
		}
}

#endif