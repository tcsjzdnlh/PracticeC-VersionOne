#include "Test.h"
#include <iostream>
#include <typeinfo>
// ------------------------------------------------------------------------------------------------
// ------------------------------------------------------------------------------------------------
/*
	���� ���� / ����ָ�� / ��ʼ���б�
*/

// ------------------------------------------------------------------------
/* ��������ָ�� */
typedef int array_1_1[3];
using array_1_2 = int[3];

// �� typeid �鿴�� ���� ��   2   ��д�� ʵ���� �� int [0] ���ͣ������͵�������ֻ����Ϊ������
typedef int array_1_3[];
using array_1_4 = int[];


int a[] = { 0, 1, 2 };

array_1_1 *  f_1_1()
{	
	std::cout << __FUNCSIG__ << " called ... " << std::endl;
	return &a;
}

array_1_2 & f_1_2()
{	
	std::cout << __FUNCSIG__ << " called ... " << std::endl;
	return a;
}

//array_1_3 * f_1_3()
//{
//	int b[1] = { 1 };
//	return &b;
//}

int( *( f_1_4() ) )[3]
{
	std::cout << __FUNCSIG__ << " called ... " << std::endl;
	return &a;
}
auto f_1_4_1() ->int( *)[3]
{
	std::cout << __FUNCSIG__ << " called ... " << std::endl;
	return &a;
}


void f_1_5()
{
	std::cout << "// -------------------------------------------------------" << std::endl;
	f_1_1();
	f_1_2();
	
	f_1_4();
	f_1_4_1();
}

// ------------------------------------------------------------------------
/* ���غ���ָ�� */
typedef void func_0_1( int );
using func_0_2 = void ( int );

void f_2( int _parameter )
{
	std::cout << "function for test ... " << std::endl;
}

void( *( f_2_1() ) )( int )
{
	std::cout << __FUNCSIG__ << " called ... " << std::endl;

	return f_2;
}
// ��������ò�Ʋ���
//void ( *( ( *f_2_2 )( ) ) )( int )
//{
//
//}
auto f_2_3() -> void( *)( int )
{
	std::cout << __FUNCSIG__ << "called ... " << std::endl;
	return &f_2;
}

void f_2_4()
{
	std::cout << " // --------------------------------------------------" << std::endl;
	f_2_1();
	f_2_3();
}




// ------------------------------------------------------------------------
/* ���� ��ʼ���б� */
#include <vector>
std::vector<int> f_3()
{
	std::cout << "// ----------------------------------------------------" << std::endl;
	std::cout << __FUNCSIG__ << " called .. " << std::endl;
	return { 0, 1, 2, 3 };
}



// ------------------------------------------------------------------------

void CTestor::Test()
{
	f_1_5();

	f_2_4();


	f_3();
}
