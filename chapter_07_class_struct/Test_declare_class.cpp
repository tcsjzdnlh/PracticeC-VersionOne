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

	CWuLi wuli( 1, 2, 3 ); // �����к����⣬����ȫ�ֶ���

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
		typedef int Money;   // error : Get�Ѿ�ʹ���� Money, ���������¶���, �� C++ �б����ǲ�����ģ�
									// �������ﱻ vc++ ��֧�֣����� Money ��������� Money��
									// ���� Get Ҳ�� int ����

		Money m_money;

	public:
		void Report()
		{
			std::cout << typeid( m_money ).name() << std::endl;
		}
	};
	
	//CYuwen yuwen;
	//// ���º��� ���� û������ ���е��ñ����� main �����ڣ��� main ��������ú��� ����
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
		//	C++ �� friend ����ʵ���ϲ�����ͨ�����ϵ�������
		// ��ֻ�ǶԷ���Ȩ������˵�����ѣ����� �� �������ڱ���Ա����ʹ�õ�ǰ��  ������
		// ���� ������VC++ ֧���ں�������Ҳ����
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

	// �����ж������������ֻ����һ������
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
	Test_various_constructor::CWuLi wuli( 1, 2, 3 ); // �ں����ڣ��ֲ����󣬺���δ����ֵ

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