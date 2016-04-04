#include "Test.h"
#include <iostream>
#include <string>
/*
	�����������أ�����ƥ�� �������֪ʶ
*/

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
/*
	���� �β� �� top-level const ���εĶ���ʱ����������  function matching ������� ��� top-level const��
	�����磺const type _parameter / type * const _pParameter��
		�������� ���ó�������ı�����ָ���������ָ�룬
		���� const type &_parameter , const type * _pParameter ��
*/

// ----------const object	---> error
void f_1( int _parameter )
{
	++_parameter;
}
//void f_1( const int _parameter )
//{
//	int a = _parameter;
//}

// ----------const pointer object   --> error
void f_2( int *_p )
{
	int a = *_p;
}
//void f_2( int * const _p )
//{
//	int a = *_p;
//}

// ------------ const reference   ---> ok
void f_3( const int &_ref )
{
	int a = _ref;
}
void f_3( int &_ref )
{
	++_ref;
}

// ------------- low-level pointer	--->ok
void f_4( const int *_p )
{
	int a = *_p;
}
void f_4( int *_p )
{
	++( *_p );
}

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
/*
	use const_cast to get/get_rid_off  const property
*/
int a_1 = 3;
const int a_2 = 7;

int &a_get_rid_of_cst = const_cast<int&>( a_2 );
const int &a_add_cst = const_cast<const int &>( a_1 );

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
/*
	ͬ��������ͬ�������ڹ������أ�
	���������������£��ڲ�������㣬
	���忴���µ�ʵ�����ǳ�����
*/

void f_5( int _parameter )
{
	++_parameter;
	std::cout << __FUNCSIG__ << " called ... " << std::endl;
}
void f_5( double _parameter )
{
	++_parameter;
	std::cout << __FUNCSIG__ << " called ... " << std::endl;
}
void f_5( int * _p )
{
	int a = *_p;
	std::cout << __FUNCSIG__ << " called ... " << std::endl;
}
//void f_5( bool _b )
//{
//	bool b = _b;
//	std::cout << __FUNCSIG__ << " called ... " << std::endl;
//}

namespace inner_scope
{
	void f_5( int _parameter )
	{
		++_parameter;
		std::cout << "inner_scope::" << __FUNCSIG__ << " called ... " << std::endl;
	}
	void f_5( double _parameter )
	{
		++_parameter;
		std::cout << "inner_scope::" << __FUNCSIG__ << " called ... " << std::endl;
	}
	void f_5( bool _b )
	{
		bool b = _b;
		std::cout << "inner_scope::" << __FUNCSIG__ << " called ... " << std::endl;
	}
}

void f_inner_scope_outer_scope()
{
	int a_1 = 6;
	double a_2 = 2;
	bool  a_3 = true;

	void f_5( std::string _str );   // declare a function in function body 
	

	f_5( std::string( "hello world !" ) );
	/*
		�������������ĵ��ö����ǵ��� �������������� void f_5( std::string _str ),
		�������� ������ std::string ���� ������ת���� std::string ���͵� ������
		���κ��������͵Ķ��ᱨ��
		�ڱ������� �� f_5 ������ ����ʱ���������ڱ��������ҵ�һ��ͬ�������������Ͳ��������ˣ�
		��һ������ƥ�������������������Ľ���������൱���ڲ����������
	*/
	//f_5( a_1 );	// error
	//f_5( a_2 );	// error
	//f_5( a_3 );	// error

	//f_5( &a_1 );	// error

	inner_scope::f_5( a_1 );   // ����������ͺ���
	::f_5( a_1 );				// ����������ͺ���

}
void f_5( std::string _str )
{
	_str += " ok!";
	std::cout << __FUNCSIG__ << " called ... " << std::endl;
}



void CTestor::Test()
{
	f_inner_scope_outer_scope();
}