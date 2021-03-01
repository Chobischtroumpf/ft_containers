/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Node.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adorigo <adorigo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 14:02:02 by adorigo           #+#    #+#             */
/*   Updated: 2021/02/21 13:28:10 by adorigo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NODE_HPP
# define NODE_HPP

# include <cstring>

namespace ft
{
	template<typename T>
	class Node
	{
	private:
		Node<T>		*_prev;
		T			_data;
		Node<T>		*_next;
	public:
		Node(): _prev(nullptr), _data(), _next(nullptr) {}
		Node(T const &val): _prev(nullptr), _data(val), _next(nullptr) {}
		Node(Node *prev, T const &val, Node *next=nullptr):
			_prev(prev), _data(val), _next(next) {}
		Node(Node const &other):
			_prev(other._prev), _data(other._data), _next(other._next) {}
		virtual ~Node(){}

		Node &operator=(Node const &other){
			this->_prev = other->_prev;
			this->_data = other->_data;
			this->_next = other->_next;
		}

		void insert_prev(Node *node){
			if (this->_prev){
				node->_prev = this->_prev;
				this->_prev->_next = node;
			}
			node->_next = this;
			node->_prev = node;
		}

		void insert_next(Node *node){
			if (this->_next){
				node->_next = this->_next;
				this->_next->_prev = node;
			}
			node->_prev = this;
			node->_next = node;
		}

		void disconnect(void) {
			if (this->_prev)
				this->_prev->_next = this->_next;
			if (this->_next)
				this->_next->_prev = this->_prev;
		}

		void swap(Node *node) {
			if (this->_next == node)
			{
				if (this->_prev)
					this->_prev->_next = node;
				node->_prev = this->_prev;
				this->_prev = node;
				if (node->_next)
					node->_next->_prev = this;
				this->_next = node->_next;
				node->_next = this;
			}
			else if (this->_prev == node)
			{
				if (this->_next == node)
				{
					if (this->_prev)
						node->_prev->_next = this;
					this->_prev = node->_prev;
					node->_prev = this;
					if (this->_next)
						this->_next->_prev = node;
					node->_next = this->_next;
					this->_next = node;
				}
			}
			else
			{
				Node<T> *previous = this->_prev;
				Node<T> *next = this->_next;

				if (this->_prev)
					this->_prev->_next = node;
				if (this->_next)
					this->_next->_prev = node;
				this->_prev = node->_prev
			}
		}

		void	reverse(void){
			Node<T> *tmp = this->_prev;
			this->_prev = this->_next;
			this->_next = tmp;
		}

		void	swap_values(Node *node){
			T tmp;
			std::memmove(static_cast<void*>(&tmp), static_cast<void*>(&node->_data), 1);
			std::memmove(static_cast<void*>(&node->_data), static_cast<void*>(&this->_data), 1);
			std::memmove(static_cast<void*>(&this->_data), static_cast<void*>(&tmp), 1);
		}

		T	&value(void){
			return(this->_data);
		}

		T	const &value(void){
			return(this->_data);
		}

		Node *&previous(void){
			return (this->_prev);
		}

		Node const *&previous(void) const{
			return (this->_prev);
		}

		Node *&next(void){
			return (this->_next);
		}

		Node const *&next(void) const{
			return (this->_next);
		}
	};
}

#endif

