#include <iostream>
class CBook
{
public:
	//CBook()
	//{
	//	// ��ע�������캯������ ������������ִ��2�Σ�����ִ�� 1��
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
