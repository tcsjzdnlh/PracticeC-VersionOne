#include "Test.h"
#include <iostream>
#include <vector>
void f_1()
{
}

void f_2( int _i )
{
	++_i;
}

int f_3()
{
	return 97;
}
int f_4( int _i )
{
	++_i;
	return 97;
}

class CPanda
{
public:
	CPanda()
	{
		m_age = 2;
	}
private:
	int		m_age;
	int		m_weight;
	int		m_speed;
};

CPanda f_5( CPanda _pao )
{
	int a = 99;
	++a;
	return _pao;
}

void f_6()
{
	CPanda pao;
	f_5( pao );
}


void f_7( int _i )
{
	++_i;
}

// 引发二义性问题
//void f_7( const int _i )
//{
//	int a = _i;
//}

void f_8( const int & _i )
{
	std::cout << "const int &   called ..." << std::endl;
}
void f_8( int & _i )
{
	std::cout << "int & called ..." << std::endl;
}

void f_9( int *const _p )
{
	int a = *_p;
}
//void f_9( int *_p )
//{
//	*_p = 20;
//}

// --------------------------------
// 下面三个函数  不能构成重载，编译器视为一个函数

int array_1[3] = { 0 };
int array_2[10] = { 0 };
int array_3[20] = { 0 };
//void f_10( int *_p_array )
//{
//	int a = _p_array[9];
//	std::cout << "f_10( int *_p_array ) called ... " << std::endl;
//}
//void f_10( int _array_2[] )
//{
//	int a = _array_2[9];
//	std::cout << "f_10( int _array_2[] ) called ... " << std::endl;
//
//}
void f_10( int _array_3[10] )
{
	int a = _array_3[9];
	std::cout << "f_10( int _array_3[10] called ... " << std::endl;
}


void f_11( int ( &_array )[10] )
{
	std::cout << "f_11( int (&_array)[10] called ... " << std::endl;
}

// --------------------------------------

void CTestor::Test()
{
	//f_1();
	//f_2( 123 );
	//f_3();
	//f_4( 123 );

	//f_6();

	// -------------------------------

	//const int a = 3;
	//// f_7( a ); //error
	//
	//f_8( a );

	//int a_1 = 5;
	//f_8( a_1 );

	// -------------------------------
	//int c_1 = 20;
	//const int c_2 = 30;
	//f_9( &c_1 );

	// -------------------------------
	//f_10( array_1 );
	//int f10[] = array_1; // error
	//int f10[] = &array_1[0]; // error
	//std::vector<int> vec1 = &array_1; // error


	// -------------------------------
	// f_11( array_1 ); // error
	f_11( array_2 );
	// f_11( array_3 ); // error
}