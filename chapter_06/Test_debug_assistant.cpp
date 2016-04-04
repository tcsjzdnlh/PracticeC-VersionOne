#include "Test.h"
#include <cassert>
#include <iostream>


void CTestor::Test()
{
	int a_1 = 10;
	assert( a_1 == 10 );

#ifndef NDEBUG
	std::cout << "NDEBUG not define ... " << std::endl;
#else
	std::cout << "NDEBUG defined ... " << std::endl;
#endif


	std::cout << "function name : " << __FUNCTION__ << std::endl;
	std::cout << "function signature : " << __FUNCSIG__ << std::endl;
	std::cout << "compile date : " << __DATE__ << std::endl;
	std::cout << "compile time : " << __TIME__ << std::endl;
	std::cout << "Line Number : " << __LINE__ << std::endl;
	std::cout << "FILE NAME : " << __FILE__ << std::endl;

	
}
