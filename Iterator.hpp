/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adorigo <adorigo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 13:42:26 by adorigo           #+#    #+#             */
/*   Updated: 2021/02/27 14:32:00 by adorigo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_HPP
# define ITERATOR_HPP

# include "Node.hpp"

namespace ft
{
	struct IteratorTrait {};

	template<typename It>
	class ReverseIterator:
		public It
	{
	public:
		using typename It::type;
		using typename It::pointer;
		using typename It::const_pointer;
		using typename It::reference;
		using typename It::const_reference;
		using typename It::difference_type;
	public:
		ReverseIterator(): It() {}
		ReverseIterator(It const &it): it(it) {}
		ReverseIterator(ReverseIterator const &other): It(other.p) {}

		ReverseIterator &operator=(ReverseIterator const &other) {
		this->p = other.p;
		return (*this);
		}

		reference operator*() {
			It tmp(*this);
			return (*--tmp);
		}

		const reference operator*() {
			It tmp(*this);
			return (*--tmp);
		}

		pointer operator->() {
			It tmp(*this);
			return (&*--tmp);
		}

		const pointer operator->() {
			It tmp(*this);
			return (&*--tmp);
		}

		ReverseIterator operator++(int) {
			ReverseIterator tmp(*this);
			operator++();
			return (tmp);
		}

		It &operator++() {
			return(this->It::operator--());
		}
		
		ReverseIterator operator--() {
			ReverseIterator tmp(*this);
			operator--();
			return (tmp);
		}

		It &operator--() {
			return(this->It::operator++());
		}
	};
}

#endif