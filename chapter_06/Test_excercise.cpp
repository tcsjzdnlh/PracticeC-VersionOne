#include "Test.h"
#include <vector>
#include <iostream>
#include <iterator>

int f_1( int _a, int _b )
{

	return _a + _b;
}

int f_2( int _a, int _b )
{
	return _a - _b;
}
int f_3( int _a, int _b )
{
	return _a * _b;
}
int f_4( int _a, int _b )
{
	return _a / _b;
}

std::vector<int (*)( int, int )> g_vec;



void CTestor::Test()
{
	g_vec.push_back( f_1 );
	g_vec.push_back( f_2 );
	g_vec.push_back( f_3 );
	g_vec.push_back( f_4 );

	int a = 1, b = 2;

	for( auto pf : g_vec )
	{
		std::cout << pf( a, b ) << std::endl;
	}

	for( auto begin = std::begin(g_vec); begin != std::end( g_vec); ++begin )
	{
		std::cout << ( *begin )( a, b ) << std::endl;
	}

}