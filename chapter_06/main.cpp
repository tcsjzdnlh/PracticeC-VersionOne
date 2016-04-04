#include "Test.h"
#include <iostream>
#include <string>


int main( int argc, char* argv[] )
{
	//CTestor testor;
	//testor.Test();

	for( int i = 0; i != argc; ++i )
	{
		char *pstr = argv[i];
		std::cout << pstr << std::endl;
	}


	return 0;
}