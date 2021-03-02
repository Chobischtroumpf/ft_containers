/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   List.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adorigo <adorigo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/25 10:48:54 by adorigo           #+#    #+#             */
/*   Updated: 2021/03/01 13:42:28 by adorigo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIST_HPP
#define LIST_HPP

#include <iostream>
#include <exception>
#include <cstddef>

namespace ft
{
	template <typename T, class Allocator = std::allocator<T> >
	class List
	{
		typedef typename Allocator::template rebind<Node>::other _node_alloc_type;

		public:
			typedef size_t			size_type;
			typedef ptrdiff_t		difference_type;
			typedef T*				pointer;
			typedef T&				reference;
			typedef T				value_type;
			
			struct Iterator
			{
				Iterator()
				{
					_node = NULL;
				};
				
				Iterator(const Iterator& it)
				{
					_node = it._node;
				};

				void operator=(const Iterator& it)
				{
					_node = it._node;
				};

				~Iterator() {};

				bool operator == (const Iterator& it)
				{
					return (it._node == _node);
				}

				bool operator != (const Iterator& it)
				{
					return(it._node != _node );
				}

				T& operator * ()
				{
					return (_node->_data);
				}

				T* operator -> ()
				{
					return(&_node->_data);
				}

				Iterator& operator ++ ()
				{
					_node = _node->_next;
					return (*this);
				}

				Iterator operator -- ()
				{
					_node = _node->_prev;
					return (*this);
				}

				Node				*_node;
			};

			List(): _head(NULL), _tail(NULL), _size(0)
			{
			};

			List(size_type size, T value = T())
			{
				
			};

			void push_back(T value)
			{
				if (_size == 0)
				{
					_head = allocate_node();
					_tail = _head;
					_size += 1;

				}
				Node *b;

				b = allocator();
				_tail->_next = b;
				_size += 1;
			};

			private:
				Node				*_head;
				Node				*_tail;
				size_type			_size;
				_node_alloc_type	_allocator;

			Node *allocate_node(Node *next, Node *prev)
			{
				Node *b = _allocator.allocate(1);
				b->_next = next;
				b->_prev = prev;
				return (b);
			}

			Node *allocate_node(Node *next, Node *prev, T value)
			{
				Node *b = allocate_node(next, prev);
				b->_data = value;
				return (b);
			}

	};
}

#endif