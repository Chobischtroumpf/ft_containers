// #include "vector/vector.hpp"
#include "vector/ft_vector.hpp"
#include <iostream>
int main()
{
	// ft::vector<std::string> Vec = ft::vector<std::string>(103);
{	ft::vector<std::string> Vec = ft::vector<std::string>(105);
	Vec.reserve(200);
	std::cout << Vec.capacity() << ", " << Vec.size() << std::endl;}

	{std::vector<std::string> Vec = std::vector<std::string>(105);
	Vec.reserve(200);
	std::cout << Vec.capacity() << ", " << Vec.size() << std::endl;}
}