#include "Test.h"
#include <iostream>
#include <string>
/*
	包括函数重载，函数匹配 两方面的知识
*/

// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
/*
	函数 形参 有 top-level const 修饰的对象时，编译器的  function matching 将会忽视 这个 top-level const。
	（比如：const type _parameter / type * const _pParameter，
		但不包括 引用常量对象的别名和指向常量对象的指针，
		即： const type &_parameter , const type * _pParameter ）
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
	同名函数在同作用域内构成重载，
	内外作用域的情况下，内层屏蔽外层，
	具体看以下的实例，非常特殊
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
		以下三个函数的调用都会是调用 本函数内声明的 void f_5( std::string _str ),
		函数参数 必须是 std::string 类型 或者能转换成 std::string 类型的 参数，
		用任何其他类型的都会报错，
		在本函数内 对 f_5 函数的 调用时，编译器在本函数内找到一个同名函数声明，就不往外找了，
		下一步就是匹配参数，就造成了这样的结果。。。相当于内层屏蔽了外层
	*/
	//f_5( a_1 );	// error
	//f_5( a_2 );	// error
	//f_5( a_3 );	// error

	//f_5( &a_1 );	// error

	inner_scope::f_5( a_1 );   // 加上作用域就好了
	::f_5( a_1 );				// 加上作用域就好了

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