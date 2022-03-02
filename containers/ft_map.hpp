#ifndef FT_MAP_HPP
# define FT_MAP_HPP 1

# include <memory>
# include "ft_iterator.hpp"
# include "ft_reverse_iterator.hpp"
# include "ft_utils.hpp"
# include "RedBlackTree.hpp"

namespace ft{
	template<class Key, class T, class Compare = std::less<Key>,
			class Allocator = std::allocator<std::pair<const Key, T> > > 
		class map{
			public:
				typedef Key													key_type;
				typedef T													mapped_type;
				typedef ft::pair<const key_type, mapped_type>				value_type;
				typedef	Compare												key_compare;
				typedef	Allocator											allocator_type;
				typedef	std::size_t											size_type;
				typedef std::ptrdiff_t										difference_type;
				typedef	typename allocator_type::reference					reference;
				typedef	typename allocator_type::const_reference			const_reference;
				typedef	typename allocator_type::pointer					pointer;
				typedef	typename allocator_type::const_pointer				const_pointer;


			private:
				class value_comp : public std::binary_function<value_type, value_type, bool>
				{
					protected:
						Compare						comp;
					public:
						typedef bool				result_type;
						typedef	value_type			first_argument_type;
						typedef	value_type			second_argument_type;
						
						value_comp(Compare c) : comp(c) {}
						bool operator()(const value_type& one, const value_type& two) const{
							return( comp( one.first, two.first));
						}
				};
			public:
				typedef value_comp											value_compare;
			private:
				typedef	RBTree<value_type, allocator_type, value_compare>	tree_type;
			public:
				typedef	typename tree_type::iterator						iterator;
				typedef	typename tree_type::const_iterator					const_iterator;
				typedef	typename tree_type::reverse_iterator				reverse_iterator;
				typedef	typename tree_type::const_reverse_iterator			const_reverse_iterator;
			private:
				tree_type													_tree;
				key_compare													_comparator;
				allocator_type												_allocator;
			public:
			//constructors
			//default
				explicit map(const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()):
					_tree(tree_type(alloc, comp)), _comparator(comp), _allocator(alloc) {}
				//range
				template <class InputIt>
				map(InputIt first, InputIt last,
					const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()):
						_tree(tree_type(alloc, comp)), _comparator(comp), _allocator(alloc)
				{
					for (; first != last; first++)
					{
						this->_tree.insert(*first);
					}
				}
				//copy
				map(const map& other):
				_tree(tree_type(other._allocator, other._comparator)), _comparator(other._comparator), _allocator(other._allocator)
				{
					for (const_iterator it = other.begin(); it != other.end(); it++){
						this->_tree.insert(*it);
					}
				}
				//destructor - les allocs et deallocs sont faite dans le rbt
				~map(){}

				//assignation operator
				map&								operator= (const map& other){
					if (this != &other) {
						this->_allocator = other._allocator;
						this->_comparator = other._comparator;
						this->_tree = other._tree;
					}
					return (*this);
				}
				//Iterateurs
				iterator							begin() {
					return (this->_tree.begin());
				}

				const_iterator						begin() const {
					return (this->_tree.begin());
				}

				reverse_iterator					rbegin() {
					return (this->_tree.rbegin());
				}

				const_reverse_iterator				rbegin() const {
					return (this->_tree.rbegin());
				}

				iterator							end() {
					return (this->_tree.end());
				}
				const_iterator						end() const {
					return (this->_tree.end());
				}

				reverse_iterator					rend() {
					return (this->_tree.rend());
				}
				const_reverse_iterator				rend() const {
					return (this->_tree.rend());
				}

				//taille et capacitée
				bool								empty() const {
					return (this->size() == 0);
				}
				size_type							size() const{
					return (this->_tree.size());
				}

				size_type							max_size() const {
					return (_allocator.max_size());
				}

				//access to map elements
				mapped_type&						operator[](const key_type& key){
					return((*((this->insert(ft::make_pair(key, mapped_type()))).first)).second);
				}

				mapped_type& 						at( const key_type& key) {
					iterator	found = this->_tree.search(ft::make_pair(key, mapped_type()));
					if (found != this->end()) {
						return (found->second);
					}
					throw std::out_of_range("key not in map!");
				}

				//modifiers
					//single elem
				ft::pair<iterator,bool>				insert(const value_type& val) {
					iterator  found = this->_tree.search(val);
					if (found != this->end()){
						return (ft::pair<iterator, bool>(found, false));
					}
					found = this->_tree.insert(val);
					return (ft::pair<iterator,bool>(found, true));
				}

				iterator							insert(iterator position, const value_type& val) {
					(void)position;
					iterator inserted = this->_tree.search(val);
					if (inserted != this->end()) {
						return (inserted);
					}
					return (this->_tree.insert(val));
				}

					//range
				template <class InputIt>
				void								insert(InputIt first, InputIt last){
					for (; first != last; first++)
					this->insert(*first);
				}

					//deletion
				void								erase(iterator position, typename ft::enable_if<!ft::is_integral<iterator>::value>::type* = 0){
					this->_tree.remove(position);
				}

				size_type							erase(const key_type& k){
					if (this->_tree.remove(ft::make_pair(k, mapped_type()))) {
						return (1);
					}
					return (0);
				}
				
				void								erase(iterator first, iterator last){
					this->_tree.remove(first, last);
				}

				void								swap (map& x){
					this->_tree.swap(x.tree);
					std::swap(this->_comparator, x._comparator);
					std::swap(this->_allocator, x._allocator);
				}

				void								clear(){
					this->_tree.clear();
				}
				
				//observers

				key_compare							key_comp() const {
					return (this->_comparator);
				}

				value_compare						value_comp() const {
					return (value_compare(_comparator));
				}

				//operations

				iterator							find(const key_type& key) {
					value_type		entry = ft::make_pair(key, mapped_type());
					return (this->_tree.search(entry));
				}

				const_iterator						find(const key_type& key) const {
					value_type		entry = ft::make_pair(key, mapped_type());
					return (const_iterator(this->_tree.search(entry)));
				}

				size_type				count(const key_type& key) const {
					const_iterator	found = this->find(key);
					if (found != this->end())
						return (1);
					return (0);
				}

				iterator								lower_bound(const key_type& k) {
					iterator it = begin();
					while (it != end() && _comparator(it->first, k)) {
						it++;
					}
					return (it);
				}

				const_iterator							lower_bound(const key_type& key) const {
					const_iterator it = begin();
					while (it != end() && _comparator(it->first, key)) {
						it++;
					}
					return (it);
				}

				iterator								upper_bound(const key_type& key) {
					iterator it = begin();
					while (it != end() && !(_comparator(key, it->first))) {
						it++;
					}
					return (it);
				}

				const_iterator							upper_bound(const key_type& key) const{
					const_iterator it = begin();
					while (it != end() && !(_comparator(key, it->first))) {
						it++;
					}
					return (it);
				}

				ft::pair<iterator,iterator>				equal_range(const key_type& key) {
					iterator    lower = lower_bound(key);
					if (lower != end()) {
						if (!_comparator(key, lower->first))
							return (ft::make_pair(lower, ++lower));
					}
					return (ft::make_pair(lower, lower));
				}

				ft::pair<const_iterator,const_iterator>	equal_range(const key_type& key) const {
					const_iterator    lower = lower_bound(key);
					if (lower != end()) {
						if (!_comparator(key, lower->first))
							return (ft::make_pair(lower, ++lower));
					}
					return (ft::make_pair(lower, lower));
				}

				allocator_type							get_allocator() const {
					return (_allocator);
				}
		};

	template<class key,class value, class comparator, class allocator>
		bool operator==(const map<key,value, comparator, allocator>& lhs,
						const map<key,value, comparator, allocator>& rhs){
			return(lhs._tree == rhs._tree);
		}

	template<class key,class value, class comparator, class allocator>
		bool operator!=(const map<key,value, comparator, allocator>& lhs,
						const map<key,value, comparator, allocator>& rhs){
			return(lhs._tree != rhs._tree);
		}

	template<class key,class value, class comparator, class allocator>
		bool operator<(const map<key,value, comparator, allocator>& lhs,
						const map<key,value, comparator, allocator>& rhs){
			return(lhs._tree < rhs._tree);
		}

	template<class key,class value, class comparator, class allocator>
		bool operator<=(const map<key,value, comparator, allocator>& lhs,
						const map<key,value, comparator, allocator>& rhs){
			return(lhs._tree <= rhs._tree);
		}

	template<class key,class value, class comparator, class allocator>
		bool operator>(const map<key,value, comparator, allocator>& lhs,
						const map<key,value, comparator, allocator>& rhs){
			return(lhs._tree > rhs._tree);
		}

	template<class key,class value, class comparator, class allocator>
		bool operator>=(const map<key,value, comparator, allocator>& lhs,
						const map<key,value, comparator, allocator>& rhs){
			return(lhs._tree >= rhs._tree);
		}

	template<class key,class value, class comparator, class allocator>
		void		swap(const map<key,value, comparator, allocator>& lhs,
						const map<key,value, comparator, allocator>& rhs){
			lhs.swap(rhs);
		}
}

#endif
