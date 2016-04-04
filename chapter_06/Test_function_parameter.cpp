#include "Test.h"
#include <iostream>

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
/*
	数组 / 多维数组 / 函数指针   作为  函数 形参(parameter)
*/

// -------- 数组 参数 3 形式
void f_1_1( int *_p )
{
	int a = *_p;
	std::cout << __FUNCSIG__ << " called ... " << std::endl;
}
void f_1_2( int _array[] )
{
	int a = _array[1];
	std::cout << __FUNCSIG__ << " called ... " << std::endl;
}
void f_1_3( int _array[10] )
{
	int a = _array[9];
	std::cout << __FUNCSIG__ << " called ... " << std::endl;
}
void f_1_4()
{
	// list_initialize， curly brace 里面的值只要能转换就像，就像本例的最后一个值一样
	int a[] = { 0, 1, 2, 3, 4, 5, 6.0 };  
	f_1_1( a );
	f_1_2( a );
	f_1_3( a ); // 完全不管 array 的 size
}

// ------多维数组

int array_1_7[2][3] = { 0 };

void f_1_7( int( *_p_array )[3] )
{
	std::cout << __FUNCSIG__ << " called ... " << std::endl;
}

// 该种 形式不行
//void f_1_5( int _array[][] )
//{
//
//}
void f_1_6( int _array[][3] )
{
	std::cout << __FUNCSIG__ << " called ... " << std::endl;
}
void f_1_8( int _array[2][3] )
{
	std::cout << __FUNCSIG__ << " called ... " << std::endl;
}

void f_1_9()
{
	std::cout << "// -----------------------------------------------" << std::endl;
	f_1_6( array_1_7 );
	f_1_7( array_1_7 );
	f_1_8( array_1_7 );
}



// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
/*
	函数指针 参数： 2 种形式都等价
*/

void f_2( int _a )
{
	std::cout << __FUNCSIG__ << " called at:  " << __LINE__ << std::endl;
}

void f_2_1( void _f( int ) )
{
	int a = 3;
	_f( a );
}
void f_2_2( void ( *_pf )( int ) )
{
	int a = 6;
	// 下面2种调用形式都可以
	_pf( a );
	( *_pf )( a );
}

void f_2_3()
{
	std::cout << "//-----------------------------------" << std::endl;
	f_2_1( f_2 );
	f_2_2( f_2 );
}


// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
/*
	不定参数 3 形式	
*/
#include <initializer_list>   // for std::initializer_list
#include <iterator>			// for std::begin(), std::end()

void f_3( std::initializer_list<int> _il )
{
	for( auto begin = std::begin( _il ); begin != std::end( _il ); ++begin )
	{
		std::cout << ( *begin ) << std::endl;
	}
}

void f_3_1( int _parameter, ... )
{
	std::cout << __FUNCSIG__ << " called _parameter value is : " << _parameter << std::endl;
}
void f_3_1_1( int _parameter ... )   // 编译器会自动补上 comma
{
	std::cout << __FUNCSIG__ << " called _parameter value is : " << _parameter << std::endl;
}

void f_3_2()
{
	std::cout << __FUNCSIG__ << " called ..." << std::endl;
}
void f_3_3( ... )
{
	std::cout << __FUNCSIG__ << " called ... " << std::endl;
}

void f_3_4()
{
	std::cout << "//-------------------------------------------------------------" << std::endl;
	int a = 6;
	
	std::initializer_list<int>	il = { 0, 1, 2, 3, 6 };
	f_3( il );
	
	f_2_3();

	f_3_1( a );
	f_3_1_1( a );
	f_3_2();
	f_3_3();
}



//----------------------------------------------------------------------------------------
void CTestor::Test()
{
	// ---数组参数
	f_1_4();
	f_2_3();
	f_3_4();


	f_1_9();
}