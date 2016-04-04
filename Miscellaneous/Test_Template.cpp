#include "Test.h"

#include "SmartMachine.h"
#include <iostream>

void CTestor::Test()
{
	CSmartMachine<unsigned int> SmartPander;
	

	std::cout << std::endl 
		<< SmartPander.GetHeight() 
		<< std::endl << std::endl;
}