#include <iostream>
class CBook
{
public:
	//CBook()
	//{
	//	// 不注销本构造函数，则 例子析构函数执行2次，否则执行 1次
	//}
	//CBook( CBook const& _other )
	//{
	//}
	~CBook()
	{
		++m_lmumber;
		std::cout << std::endl << std::endl << m_lmumber << std::endl;
	}
private:
	static unsigned long m_lmumber;
};

unsigned long CBook::m_lmumber = 0L;

CBook func_01()
{
	return CBook();
}

int main()
{
	func_01();
	return 0;
}
