#include "Test.h"
#include <iostream>

namespace miscellianeous
{
	namespace abnormal_switch
	{
		void abnormal_switch_use( int _case )
		{
			switch( _case )
			{
			default:
				{				
					std::cout << "casae default excuted ... " << std::endl;				
				}
				break;
			case 1:
				{
					std::cout << "casae 1 excuted ... " << std::endl;
				}
				break;
			case 2:
				{
					std::cout << "casae 2 excuted ... " << std::endl;
				}
				break;
			}
		}

		void test()
		{			
			int i;

			std::cout << std::endl << " please input a inteager , quit program input 9 : ";

			while( std::cin >> i )
			{
				if( i == 9 ) break;

				abnormal_switch_use( i );
				std::cout << std::endl << " please input a inteager , quit program input 9 : ";
			}
		}
	}
}


void CTestor::Test()
{
	{
		using namespace miscellianeous;
		abnormal_switch::test();
	}
}