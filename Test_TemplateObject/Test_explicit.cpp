#include <cstdint>
#include <cstdio>
#include <iostream>
#include <vector>

class CBook_01
{
public:
	CBook_01( uint32_t _pages )
	{
		m_pages = _pages;
	}
	bool operator== ( CBook_01 const& _other )
	{
		return m_pages == _other.m_pages;
	}
private:
	uint32_t	m_pages;
};

class CBook_02
{
public:
	explicit CBook_02( uint32_t _pages )
	{
		m_pages = _pages;
	}
private:
	uint32_t	m_pages;
};
class A
{};

class CBook_03
{
public:
	CBook_03( uint32_t _pages )
	{

	}
private:
	uint32_t		m_pages;
};

//uint32_t explicit������( uint32_t _value )
//{
//	_value += 100;
//	return _value;
//}
//void explicit������( CBook_03 _object )
//{
//	// doing somthing
//}

int main()
{
	CBook_01 Yuwen = 300U;
	//CBook_02 Shuxue = 400U; // ��ʽת��
	CBook_02 Shuxue( 400U ); // ��ʾ���� ���캯�� ���� explicit

	if( Yuwen == 5 )
	{
	}

	return 0;
}