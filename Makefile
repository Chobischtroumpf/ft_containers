NAME		=	 ft_containers

ITERATOR_DIR	= \
		iterators/ft_iterator_traits.hpp \
		iterators/ft_iterator.hpp \
		iterators/ft_reverse_iterator.hpp \

CONTAINERS_DIR	= \
		vector/vector.hpp


COMMON_DIR		= \
		shared/ft_equal.hpp

INC				= -I$(CONTAINERS_DIR) -T$(ITERATOR_DIR) #-I$(COMMON_DIR)

OBJ_DIR			= obj/
OBJ				= $(patsubst $$(OBJ_DIR), )