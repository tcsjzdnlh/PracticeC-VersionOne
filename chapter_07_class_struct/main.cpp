#include <iostream>
#include "Test.h"
#include <cstdlib>

int main( int argc, char * argv[] )
{
	CTestor testor;
	testor.Test();

	
	std::cout << std::endl << std::endl;
	std::cout << "//----------------------------------------" << std::endl;
	
	for( int i = 0; i != argc; ++i )
	{
		std::cout << argv[i] << std::endl;
	}

	std::cout << std::endl << std::endl;
	std::cout << "//----------------------------------------" << std::endl;
	
	
	
	//return EXIT_FAILURE;
	return EXIT_SUCCESS;
}