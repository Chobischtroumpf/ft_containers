/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijacquet <ijacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 15:03:56 by ijacquet          #+#    #+#             */
/*   Updated: 2021/11/12 15:03:56 by ijacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tester.hpp"

void 	print_header(std::string str)
{
	int margin = (40 - str.length()) / 2;
	int width = (margin * 2 + str.length()) + 2;

	std::cout << BOLD << BLUE << std::endl;
	std::cout << std::string(width, '*') << std::endl;
	std::cout << '*' << RESET << std::string(margin, ' ') << str << std::string(margin, ' ') << BOLD << BLUE << '*' << std::endl;
	std::cout << std::string(width, '*') << std::endl;
	std::cout << RESET << std::endl;
}

void 	print_title(std::string str)
{
	int width = 30;

	std::cout << "- " << str << std::endl;
	std::cout << BOLD << BLUE << std::string(width, '-') << RESET << std::endl;
}

void print_error()
{
	std::cout << BOLD << ROUGE << "Unkown command." << RESET << std::endl;
	std::cout << "Pass the name of the test in argument."  << std::endl;
	std::cout << "List of valid args : "  << std::endl;
	std::cout << "- vector"  << std::endl;
	std::cout << "- map"  << std::endl;
	std::cout << "- all"  << std::endl;
}


bool compare_supEq(int a, int b)
{
	return (a >= b);
}

bool compare_infEq(int a, int b)
{
	return (a <= b);
}

bool compare_Eq(int a, int b)
{
	return (a == b);
}

bool compare_inf(int a, int b)
{
	return (a < b);
}

bool compare_sup(int a, int b)
{
	return (a > b);
}

bool test_pair(int &val)
{
	if (val % 2)
		return (false);
	return (true);
}

bool pred(int &val)
{
	if (val > 4)
		return (false);
	return (true);
}

int main(int argc, char **argv)
{
	std::string test;

	if (argc < 2)
		test="all";
	else
		test = argv[1];
	if (test == "all")
	{
		test_vector();
		test_map();
	}
	else if (test == "vector")
		test_vector();
	else if (test == "map")
		test_map();
	else
	{
		print_error();
		return (1);
	}
	while(1)
	{}
}
