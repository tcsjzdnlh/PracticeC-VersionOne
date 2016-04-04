#include "Test.h"
#include <iostream>
#include <string>
#include <typeinfo>

//---------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------


class CBook;  // forward declaration
CBook AddBook( CBook & _book, CBook *_pBook );

//---------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------
/*
	constructor / default constructor / synthesized constructor / constructor initialize list
*/
namespace Test_various_constructor
{

	class CYuwen
	{
	private:
		int m_level;
	};

	CYuwen yuwen();  // declare a function, not instance an object
	CYuwen guwen;	// instance an object

	// ---------------------
	// default constructor
	class CDaiShu
	{
	public:
		CDaiShu() = default;			// -------> key code for default constructor
		CDaiShu( std::string _str );

	private:
		std::string		m_str;
	};
	CDaiShu::CDaiShu( std::string _str )
	{
		m_str = _str;
	}

	class CShuxue
	{
	public:
		//CShuxue()
		//	:m_ds_1(std::string(""))
		//{};
	private:
		int	m_level;
		CDaiShu	m_ds;   //  no appropriate default constructor available
		CDaiShu m_ds_1 = "hello";
	};

	CShuxue sx; //  no appropriate default constructor available

	class CJiHe
	{
	public:
		explicit CJiHe( int _level );
		explicit CJiHe( std::string _str )
		{
			std::cout << _str;
		}

	private:
		int		m_level;
	};
	// explicit is not allowed when in outside class
	/*explicit*/ CJiHe::CJiHe( int _level )
	{
		m_level = _level;
	}

	// CJiHe jihe; // error, no approperiate default constructor
	// CJiHe jihe = 3; // error, explicit stopped that implicit convert constructor

	CJiHe jihe = static_cast<CJiHe>( 3 );
	CJiHe jihe_1( 3 );
	CJiHe jihe_2 = static_cast<CJiHe>( "hello" );


	// member variable initialize order: in the order of the declare in class
	class CWuLi
	{
	public:
		CWuLi( int _level, int _pages, int _weight )
			:m_level( _level ), m_weight( _weight ), m_pages( m_weight )
		{
			std::cout << "// ---------------------------------------------------------------" << std::endl;

			std::cout << "m_level : " << m_level << std::endl
				<< "m_pages : " << m_pages << std::endl
				<< "m_weight : " << m_weight << std::endl;
		}
	private:
		int m_level;
		int m_pages;
		int m_weight;
	};

	CWuLi wuli( 1, 2, 3 ); // 在所有函数外，即，全局对象

	// ---------------------
	// delegate constructor
	class CHuaXue
	{
	public:
		// call delegate constructor
		CHuaXue()
			:CHuaXue( 3 )
		{
			std::cout << " in default constructor ... " << std::endl;
		}
		CHuaXue( int _level )
			: m_level( _level )
		{
			std::cout << "in delegate constructor ... " << std::endl;
		}
	private:
		int m_level;
	};


	CHuaXue hx;
}


//---------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------

namespace Test_name_lookup
{
	typedef double Money;
	class CYuwen
	{
	public:
		CYuwen()
		{
			std::cout << "// -------------------------------------------------------" << std::endl;
		}
		Money Get()
		{
			std::cout << typeid( Money ).name() << std::endl;
			return Money( 0 );
		}
	private:
		typedef int Money;   // error : Get已经使用了 Money, 这里又重新定义, 在 C++ 中本来是不允许的，
									// 但是这里被 vc++ 所支持，而且 Money 屏蔽了外层 Money，
									// 导致 Get 也是 int 类型

		Money m_money;

	public:
		void Report()
		{
			std::cout << typeid( m_money ).name() << std::endl;
		}
	};
	
	//CYuwen yuwen;
	//// 以下函数 调用 没错，但是 所有调用必须在 main 函数内，在 main 函数外调用函数 报错
	//yuwen.Get();   
	//yuwen.Report();

}
//---------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------
namespace Test_const
{
	class CYuwen
	{
	public:
		CYuwen() = default;
	
	public:
		int GetLevel() const
		{
			//++m_level;	error
			return m_level;
		}
		int GetPages()
		{
			return m_pages;
		}
		int GetChars() const
		{
			++m_characters;
			return m_characters;
		}
	private:
		int		m_level;
		int		m_pages;
		mutable int		m_characters;
	};

	CYuwen yuwen;
	const CYuwen cyw;
}

//---------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------
namespace Test_friend
{
	class CYuwen
	{
	public:
		//	C++ 中 friend 声明实际上不是普通意义上的声明，
		// 它只是对访问权限作出说明而已，必须 在 类外且在被成员函数使用的前面  声明，
		// 但是 本例，VC++ 支持在后面声明也可以
		friend void f_1( int _level, CYuwen &yw );
		
		int GetLevel() const;
		
		void SetLevel( int _level );
		//void SetLevel( int _level )
		//{
		//	f_1( _level, *this );
		//}

	private:
		int m_level;
	};
	void CYuwen::SetLevel( int _level )
	{
		f_1( _level, *this );
		std::cout << "// ---------------------------------------------------" << std::endl;
		std::cout << "m_level is : " << m_level << std::endl;
	}

	// 可以有多个声明，但是只能有一个定义
	void f_1( int _level, CYuwen &yw );
	void f_1( int _level, CYuwen &yw );
	void f_1( int _level, CYuwen &yw );
	void f_1( int _level, CYuwen &yw );
	
	void f_1( int _level, CYuwen &yw )
	{
		yw.m_level = _level;
	}

	CYuwen yuwen;
}
//---------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------

namespace Test_static
{
	class CYuwen
	{
	public:
		// static int GetLevel() const;	// error, const is not allowed for static member function
		static int GetLevel();
	private:
		static const int m_level = 3;// in-class initializer for static member variable only const / consexpr
		// static int m_level_1 = 4;    // error, static in-class initializer must be const
		static int m_level_2;
	public:
		static int m_level_3;
	};


	int CYuwen::GetLevel()
	{
		return m_level_2;
	}
	//static int CYuwen::m_level_2 = 3; // error , static not allowed
	int CYuwen::m_level_2 = 3;
	const int CYuwen::m_level;	// can't reinitial for define, and this define can be omit

	int CYuwen::m_level_3 = 20;

	int a = 0;
}


void CTestor::Test()
{
	Test_various_constructor::CWuLi wuli( 1, 2, 3 ); // 在函数内，局部对象，含有未定义值

	// --------------------------------------
	Test_name_lookup::CYuwen yuwen;
	yuwen.Get();
	yuwen.Report();


	// --------------------------------------
	Test_const::yuwen.GetChars();
	// Test_const::cyw.GetPages();  // error const object can just call const member function
	Test_const::cyw.GetLevel();


	// --------------------------------------
	
	Test_friend::yuwen.SetLevel( 3 );

	// --------------------------------------
	// Test_static::a = Test_static::CYuwen::m_level;	// error , m_level is private
	Test_static::a = Test_static::CYuwen::m_level_3;
	Test_static::a = Test_static::CYuwen::GetLevel();
}