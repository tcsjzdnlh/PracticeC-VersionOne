#include "Test.h"
#include <iostream>
#include <typeinfo>

void CTestor::Test()
{
	int a_1 = 1;
	const int a_2 = 2;
	int const a_3 = 3;

	//  warning C4228: nonstandard extension used : qualifiers after comma in declarator list are ignored
	//int b_1 = 1, const b_2 = 2;


	auto c_1 = a_1;
	std::cout << "type of c_1 is : " << typeid( c_1 ).name() << std::endl;

	auto c_2 = a_2;
	std::cout << "type of c_2 is : " << typeid( c_2 ).name() << std::endl;

	auto c_3 = &a_1;
	std::cout << "type of c_3 is : " << typeid( c_3 ).name() << std::endl;

	const auto c_4 = a_1;
	std::cout << "type of c_4 is : " << typeid( c_4 ).name() << std::endl;

	const auto c_5 = &a_1;
	std::cout << "type of c_5 is : " << typeid( c_5 ).name() << std::endl;
	*c_5 = 9;

	const auto *c_6 = &a_1;
	c_6 = nullptr;


	// ---------------
	std::cout << std::endl << "// ------------------------------------------" << std::endl;
	auto &d_1 = a_1;
	auto &d_2 = a_2;
	// auto &d_3 = 50; // error
	const auto &d_4 = 50;
	const auto &d_5 = 9.3;

	d_1 = 45;
	//d_2 = 90; // error

	int *p_d_6 = &a_1;
	auto *&d_6 = p_d_6;

	const int *p_d_7 = &a_1;
	const auto *&d_7 = p_d_7;


	int f_1 = 0;
	decltype( f_1 ) f_2;
	decltype( ( f_1 ) ) f_3 = f_1;

}