#include "Test.h"
#include <cstddef>   // for size_t
#include <iostream>
#include <typeinfo> // for typeid
#include <vector>
#include <iterator> // for begin() / end()


void CTestor::Test()
{
	const size_t sz = 10;
	int a_1[sz] = { 3, 6 };
	
	int a_2[] = { 20 };
	std::cout << "type of a_2 is : " << typeid( /*decltype( a_2 )*/ a_2 ).name() << std::endl;

	// ----------------------------	
	using a_2_1 = int [3];
	std::cout << "type of _a_2_1 is : " << typeid( a_2_1 ).name() << std::endl;
		
	typedef int array[100];
	array b_1_1;
	b_1_1[0] = 10;
	std::cout << std::endl << "b_1_1[0] value is : " << b_1_1[0] << std::endl;
	std::cout << "type of b_1_1 is : " << typeid( b_1_1 ).name() << std::endl;

	// ----------------------------
	int c[20];
	int  ( *pC_1 )[20] = &c;	
	// int rslt_c_1 = pC_1[3]; // error
	int rslt_1 = ( *pC_1 )[2];
	std::cout << "type of pC_1 is : " << typeid( pC_1 ).name() << std::endl;


	int *pC_2 = c;
	int rslt_c_2_1 = pC_2[2];
	std::cout << "type of pC_2 is : " << typeid( pC_2 ).name() << std::endl;


	int d[20];

	int ( &rd_1 )[20] = d;
	std::cout << "type of rd_1 is : " << typeid( rd_1 ).name() << std::endl;

	int e[20];
	auto e_1( e );
	std::cout << "type of e_1 is : " << typeid( e_1 ).name() << std::endl;

	auto &e_2( e );
	std::cout << "type of e_2 is : " << typeid( e_2 ).name() << std::endl;

	auto *p_e_1( e );
	std::cout << " type of p_e_1 is : " << typeid( p_e_1 ).name() << std::endl;

	auto *p_e_2( &e );
	std::cout << "type of p_e_2 : " << typeid( p_e_2 ).name() << std::endl;

	std::cout << "// -----------------------------------" << std::endl;

	int f[20];
	auto fbegin = &f[0];
	auto fend = &f[20];
	
	for( unsigned int i = 0; fbegin != fend; ++ i, ++fbegin )
	{
		( *fbegin ) = i;
	}

	std::cout << "f array values are : " << std::endl;
	for( auto element : f )
	{
		std::cout << "	" << element << std::endl;
	}


	std::cout << std::endl << "// -----------------------------------" << std::endl;
	
	std::vector<int> vec_1( std::begin( f ), std::end( f ) );
	std::cout << std::endl << "vec_1 values are : " << std::endl;
	for( int element : vec_1 )
	{
		std::cout << "	" << element << std::endl;
	}


	std::cout << std::endl << "// -----------------------------------" << std::endl;

	int g[2][3] = { };

	for( auto &element_out : g )
	{
		for( auto &element_in : element_out )
		{
			static int i = 0;
			element_in = i;
			
			++i;
		}
	}

	std::cout << std::endl << " g array values are : " << std::endl;
	for( auto &element_out : g )
	{
		for( auto element_in : element_out )
		{
			std::cout << "	" << element_in << std::endl;
		}
	}



	auto &rg_1( g );
	std::cout << " type of rg_1 is : " << typeid( rg_1 ).name() << std::endl;

	auto *pg_1( g );
	std::cout << "type of pg_1 is " << typeid( pg_1 ).name() << std::endl;
}