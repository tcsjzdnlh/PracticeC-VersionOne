#include "Test.h"
#include <iostream>
#include <string>

#include <ctime> // for time


using namespace std;

class CBook
{
public:
	virtual void PrintName()
	{
		cout << endl << "CBook name:  " << m_strName << endl << endl;

		this->WhichThis();
	}

	virtual void WhichThis()
	{
		cout << endl << endl << "CBook this ..." << endl << endl;
	}
private:
	string		m_strName = "base book class";
};

class CYuWen : public CBook
{
public:
	//virtual void PrintName()
	//{
	//	cout << endl << endl << "CYuWen book name is : " << m_strSentence << endl;
	//}
	virtual void WhichThis()
	{
		cout << endl << endl << "CYuWen this ..." << endl << endl;
	}

private:
	string		m_strSentence;
};





void CTestor::Test()
{
	//CYuWen *pBook = new CYuWen;

	//pBook->PrintName();


	//if( nullptr != pBook )
	//{
	//	delete pBook;
	//}

	// 临时测试 time(0) 的输出值
	//std::cout << std::endl << std::endl
	//	<< time( 0 ) << std::endl << std::endl;


	// 临时测试 3 % 5 的输出值
	std::cout << std::endl << std::endl
		<< 3 % 5 << std::endl << std::endl;

}