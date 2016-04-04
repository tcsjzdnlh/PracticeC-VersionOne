#include "Test.h"
#include <iostream>
#include <thread>

using namespace std;


class CBook
{
public:
	CBook()
	{
		cout << endl << "book constructor called ..." << endl;
	}
};

void g_task_1()
{
	static CBook book;
}
void g_task_2()
{
	static CBook book;
}

void CTestor::Test()
{
	//thread t1( g_task_1 );
	//thread t2( g_task_2 );


	//if( t1.joinable() )
	//{
	//	t1.join();
	//}
	//if( t2.joinable() )
	//{
	//	t2.join();
	//}

	// ----------------------------------
	//g_task_1();
	//g_task_2();

	// ----------------------------------
	g_task_1();
	g_task_1();

}