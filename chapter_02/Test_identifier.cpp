#include "Test.h"
#include <iostream>
#include <typeinfo>


void CTestor::Test()
{
	const int &ra = 3.14;
	int b = 0;
	float i = 3;

	std::cout << typeid( i ).name() << std::endl;
	std::cout << typeid( ra ).name() << std::endl;

	decltype( i ) e = b;

	// -----------------

	std::cout << std::endl << "// -----------------------------------" << std::endl;
	
	int f = 200;
	auto p_f_1 = &f;
	std::cout << "type of p_f_1 is : " << typeid( p_f_1 ).name() << std::endl;

	auto *p_f_2 = &f;
	std::cout << "type of p_f_2 is : " << typeid( p_f_2 ).name() << std::endl;

	auto * const p_f_3 = &f;
	std::cout << " type of p_f_3 is : " << typeid( p_f_3 ).name() << std::endl;

	
}