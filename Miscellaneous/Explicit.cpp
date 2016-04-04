#include "Test.h"
#include <cstdint>
#include <iostream>

/*

	û�� explicit ���ε� ���캯��������൱�᣺		
		��ʽ�� AAA = eee��eeeΪ �� AAA �ĵ��������캯���Ĳ������͵�object��
									���ߣ� ֻ�е�һ������û��Ĭ��ֵ������������Ĭ��ֵʱ����һ�����������͵�object
									���߸��ƹ��캯���Ĳ�������object
		���� CBook Yuwen = 3;
		��������������


	explicit ֻ������ ���������캯��/ֻ��һ������û��Ĭ��ֵ������������Ĭ��ֵ�Ĺ��캯��/���ƹ��캯��/

	���ڵ����壺  �ϸ�����ƥ��

	


*/




class CBook
{
public:
	CBook( uint32_t _pages )
	{
		m_pages = _pages;
	}
	CBook( CBook const& _other )
	{
		m_pages = _other.m_pages;
		std::cout << std::endl << "copy construct excuted ... " << std::endl;
	}
	~CBook()
	{
		std::cout << std::endl << "CBook destructor excuted ... " << std::endl;
	}
public:
	uint32_t GetPages() const
	{
		return m_pages;
	}

private:
	uint32_t	m_pages;
};



class CTelephone
{
public:
	explicit CTelephone( uint32_t _BatteryCapacity )
	{
		m_BatteryCapacity = _BatteryCapacity;
	}
	explicit CTelephone( double _Weight, uint32_t _BatteryCapacity = 10 )
	{
		m_BatteryCapacity = _BatteryCapacity;
		m_Weight = _Weight;
	}
	explicit CTelephone( CTelephone const& _other )
	{
		m_BatteryCapacity = _other.m_BatteryCapacity;
		std::cout << std::endl << "copy construct excuted ... " << std::endl;
	}
	~CTelephone()
	{
		std::cout << std::endl << "CTelephone destructor excuted ... " << std::endl;
	}
public:
	uint32_t GetPages() const
	{
		return m_BatteryCapacity;
	}

private:
	uint32_t	m_BatteryCapacity;
	double		m_Weight;
};



void CTestor::Test()
{
	CBook Yuwen = 3;
	std::cout << std::endl << "Yuwen book pages is : " << Yuwen.GetPages() << std::endl;

	//CTelephone tlp = 3; explicit ��ֹ������
	CTelephone tlp_01( 3U );
	
	//CTelephone tlp_03 = 3.0;
	CTelephone tlp_02( 3.0 );
	

}