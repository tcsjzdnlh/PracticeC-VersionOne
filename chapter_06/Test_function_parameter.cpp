#include "Test.h"
#include <iostream>

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
/*
	���� / ��ά���� / ����ָ��   ��Ϊ  ���� �β�(parameter)
*/

// -------- ���� ���� 3 ��ʽ
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
	// list_initialize�� curly brace �����ֵֻҪ��ת�����񣬾����������һ��ֵһ��
	int a[] = { 0, 1, 2, 3, 4, 5, 6.0 };  
	f_1_1( a );
	f_1_2( a );
	f_1_3( a ); // ��ȫ���� array �� size
}

// ------��ά����

int array_1_7[2][3] = { 0 };

void f_1_7( int( *_p_array )[3] )
{
	std::cout << __FUNCSIG__ << " called ... " << std::endl;
}

// ���� ��ʽ����
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
	����ָ�� ������ 2 ����ʽ���ȼ�
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
	// ����2�ֵ�����ʽ������
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
	�������� 3 ��ʽ	
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
void f_3_1_1( int _parameter ... )   // ���������Զ����� comma
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
	// ---�������
	f_1_4();
	f_2_3();
	f_3_4();


	f_1_9();
}