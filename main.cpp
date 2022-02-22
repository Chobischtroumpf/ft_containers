// #include "vector/vector.hpp"
#include <vector>
#include <iostream>
int main()
{
	std::vector<std::string> Vec = std::vector<std::string>(103);
	Vec.reserve(200);
	std::cout << Vec.capacity() << ", " << Vec.size() << std::endl;

}