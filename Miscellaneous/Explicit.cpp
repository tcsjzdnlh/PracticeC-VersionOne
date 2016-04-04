#include "Test.h"
#include <cstdint>
#include <iostream>

/*

	没有 explicit 修饰的 构造函数真滴素相当酷：		
		形式： AAA = eee，eee为 类 AAA 的单参数构造函数的参数类型的object，
									或者， 只有第一个参数没有默认值其他参数都有默认值时，第一个参数的类型的object
									或者复制构造函数的参数类型object
		例如 CBook Yuwen = 3;
		详情见下面的例子


	explicit 只能修饰 单参数构造函数/只有一个参数没有默认值其他参数都有默认值的构造函数/复制构造函数/

	存在的意义：  严格类型匹配

	


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

	//CTelephone tlp = 3; explicit 禁止这样用
	CTelephone tlp_01( 3U );
	
	//CTelephone tlp_03 = 3.0;
	CTelephone tlp_02( 3.0 );
	

}