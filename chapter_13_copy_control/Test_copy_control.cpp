#include "Test.h"
#include <iostream>
#include <string>
#include <thread>
#include <chrono>


namespace test_copy_constructor
{
	class CBook
	{
	public:
		//CBook() = default;
		//CBook( const CBook &_book ) = default;
		//CBook& operator=( CBook &_book ) = default;

		//CBook() = delete;
		//CBook( const CBook &_book ) = delete;
		//CBook& operator=( const CBook &_book ) = delete;



		CBook()
			:m_level( 1 )
		{
			//std::this_thread::sleep_for( std::chrono::seconds(2) );
			std::cout << "CBook default constructor" << std::endl;
			std::this_thread::yield();
		}
		CBook( const CBook & _book )
			:m_level( _book.m_level )
		{

			std::cout << "CBook copy constructor" << std::endl;			
		}
		CBook& operator=( const CBook &_book )
		{
			m_level = _book.m_level;
			std::cout << "CBook copy assignment " << std::endl;
			
			return *this;
		}
		~CBook()			
		{}


	private:
		int m_level;

	};


	CBook yuwen;
	CBook shuxue = yuwen;
	CBook wuli( shuxue );
	//wuli = shuxue;		//	ȫ�������� ֻ�ܶ����������������(�����Ǹ�ֵ����)

	
	void test()
	{		
		wuli = shuxue;
		
	}


}
namespace test_destructor
{
	namespace private_destructor
	{
		/*
		���ۣ�delete�� destructor ���� ȫ�ֶ��� ���Զ��� �� new�ֲ����� ���ԣ��ֲ����� �����Զ���
		*/
		class CBook
		{
		public:

		private:
			~CBook() = default;
		};

		CBook yuwen;	// private �� destructor ȫ�ֶ������

		void test()
		{
			//CBook yuwen;	// error, destructor is inaccessble
			CBook *pyuwen = new CBook;
			CBook *pshuxue = new ( std::nothrow )CBook;
		}
	}
	namespace delete_destructor
	{
		/*
			���ۣ�delete�� destructor ���� ֻ�� new���� ���ԣ� ȫ�ֶ���/�ֲ����� �������Զ���
		*/
		class CBook
		{
		public:
			~CBook() = delete;
		private:
			int		m_level{ 3 };
		};

		// CBook yuwen; // ---------->error

		CBook *phuaxue = new CBook;
		CBook *plishi = new ( std::nothrow ) CBook;
		
		void test()
		{
			// CBook shuxue;	// ---------->error
			CBook *phuaxue = new CBook;
			CBook *plishi = new ( std::nothrow ) CBook;
		}
	}
	namespace use_destructor
	{
		class CBook
		{
		public:
			CBook() = default;
			
			CBook( int _level )
				:m_pLevel( new (std::nothrow) int( _level ) )
			{}
			
			~CBook()
			{
				if( m_pLevel )
				{
					std::cout << "object has a int need to free, the value is : " 
						<< ( *m_pLevel ) << std::endl;
					delete m_pLevel;
					m_pLevel = nullptr;
				}
			}

		private:
			int		*m_pLevel;
		};

		
		void test()
		{
			CBook yuwen( 3 );
			// yuwen.~CBook(); // error, ��ʾ������������ ���� ������������� 2 �Σ��������
		}

	}
	namespace three_five_principle
	{
		/*
			��Ҫ ��д destructor ����� �ض� ��Ҫ��д copy-constructor/copy-assignment��
			��� ��д�� destructor������д copy-constructor/copy-assignment ��
			������� ���� Ĭ�ϵ� copy-constructor / copy-assignment,
			��ᵼ�����صĴ���
		*/
		class CBook
		{
		public:
			CBook() = default;
			//CBook()
			//	:m_pLevel( nullptr )
			//{}
			
			CBook( int _level )
				:m_pLevel( new ( std::nothrow ) int(_level) )
			{}

			CBook( const CBook & _book )
				/*:m_pLevel( new ( std::nothrow ) int( *( _book.m_pLevel ) ) )*/
			{
				if( _book.m_pLevel )
				{
					m_pLevel = new ( std::nothrow ) int( *( _book.m_pLevel ) );
				}
			}

			CBook& operator=( const CBook &_book )
			{
				// �Ը�ֵ������ҶԷ�Ҫ����Դ
				if( ( this != &_book ) && ( nullptr != _book.m_pLevel ) )
				{
					
					if( !m_pLevel )
					{
						m_pLevel = new ( std::nothrow ) int( *( _book.m_pLevel ) );
					}
					else
					{	
						// �����ȴ�����Դ���ٽ��������Դ���Դ��Ȼ����Ǹ�ֵ
						auto *p = new ( std::nothrow ) int( *( _book.m_pLevel ) );
						if( p )
						{
							Destruct();
							m_pLevel = p;
						}
						else
						{
							// new �����������ˣ�Ҫôû�ڴ��ˣ�Ҫôϵͳ���������ش���
							std::cout << "dadly error ocured ... " << std::endl;
						}

						
					}
					
				}
				
				return *this;
			}
			~CBook()
			{
				std::cout << "object destroy ... " << std::endl;
				Destruct();
			}
			
		public:
			int GetLevel() const
			{
				if( m_pLevel )
				{
					return *m_pLevel;
				}
				return 0;
			}

		private:
			void Destruct()
			{
				if( m_pLevel )
				{
					delete m_pLevel;
					m_pLevel = nullptr;
				}
			}
		private:
			int		*m_pLevel = nullptr;
		};


		void test()
		{
			std::cout << "// ----------------------------------------" << std::endl;
			CBook yuwen;
			CBook shuxue( 5 );
			CBook lishi = shuxue;
			
			std::cout << "yuwen level: " << yuwen.GetLevel() << std::endl
				<< "shuxue level : " << shuxue.GetLevel() << std::endl
				<< "lishi level : " << lishi.GetLevel() << std::endl;
			
			
			yuwen = lishi;

			std::cout << "yuwen level : " << yuwen.GetLevel() << std::endl;

		}

	}	
}
namespace test_rvalue_ref
{
	namespace simple_rvalue
	{
		void test()
		{
			std::cout << "// -----------------------------------" << std::endl;
			int a = 3;
			int &&ref_a_1 = (int &&)a;		// ��ֵת���� ��ֵ����
			// int &&ref_2 = ref;	// error, ref �Ǳ������ʽ���������ʽ������ֵ����ֵ���ò��ܰ󶨵���ֵ��
			int &&ref_a_2 = (int&&)ref_a_1;
			int &&ref_a_3 = static_cast<int&&>( ref_a_1 );
			int &&ref_a_4 = std::move( ref_a_1 );

			ref_a_1 = 3;			
			std::cout << "a value : " << ref_a_1 << " " << a << std::endl;

			ref_a_2 = 100;
			std::cout << "a value : " << ref_a_2 << " " << a << std::endl;

			std::cout << "address of ref_a_1 : " << &ref_a_1 << std::endl
				<< "address of ref_a_2 : " << &ref_a_2 << std::endl
				<< "address of ref_a_3 : " << &ref_a_3 << std::endl
				<< "address of ref_a_4 : " << &ref_a_4 << std::endl
				<< "addres of a : " << &a << std::endl;


			int &&b = 3;
			b = 5;

			int &ref_b_1 = b;
			int &ref_b_2 = (int&)b;		// ��ֵ����ת������ֵ����

			std::cout << "b value : " << b << std::endl
				<< "ref_b_1 value : " << ref_b_1 << std::endl
				<< "ref_b_2 value : " << ref_b_2 << std::endl;


			std::cout << "address of b : " << &b << std::endl
				<< "address of ref_b_1 : " << &ref_b_1 << std::endl
				<< "address of ref_b_2 : " << &ref_b_2 << std::endl;


		}
	}
	namespace move_constructor_and_assignment
	{
		class CBook
		{
		public:
			//CBook() = default;

			CBook( int _level )
				:m_level( _level )
			{}

			CBook( CBook &&_book ) /*noexcept*/			// vc++2013 δʵ��
				:m_level( _book.m_level )
			{
				_book.m_level = 0;
			}

			CBook& operator=( CBook &&_book ) /*noexcept*/		// vc++2013 δʵ��
			{
				m_level = _book.m_level;

				return *this;
			}

			int GetLevel()
			{
				return m_level;
			}
		private:
			int		m_level;
		};
		void test()
		{
			// CBook yuwen;	// error, ��������ʽ�� constructor, �� ���������� Ϊ�� ���� synthesized constructor
			CBook yuwen = CBook( 5 );
			CBook shuxue( 6 );
			shuxue = yuwen;

#include <utility>	// ------> for std::move

			CBook lishi = std::move<CBook>( CBook( 90 ) );
			lishi = std::move( CBook( 90 ) );

			CBook dili = (CBook&&)lishi;		// std::move �ı��ʾ��� ����ֵת���� ��ֵ��������һ��

		}
	}
	namespace explore_synthesized_move_control
	{
		namespace first
		{
			class CBook
			{
			public:
				CBook() = default;
				CBook( const CBook &_book )
					:m_level( 2 + _book.m_level )
				{
					std::cout << " in CBook copy-constructor" << std::endl;
				}
				CBook( CBook &&_book )
					:m_level( 3 + _book.m_level )
				{
					_book.m_level = 0;
					std::cout << "in CBook move-constructor" << std::endl;
				}

			private:
				int	m_level;
			};


#include <utility>
			void test()
			{
				std::cout << "// -----------------------------" << std::endl;
				CBook yuwen;
				yuwen = std::move( CBook() );
				CBook shuxue = std::move( CBook() );	// ��ûд move-constructor��ʱ�򣬻���� copy-constructor
			}
		}

		namespace second
		{
			class CPaper
			{
			public:
				CPaper() = default;
				CPaper( CPaper &&_paper )
					:m_chars( 100 + _paper.m_chars )
				{
					std::cout << "in CPaper move-constructor" << std::endl;
				}
			private:
				int		m_chars;
			};
			
			class CBook
			{
			public:
				CBook() = default;
				void DisWarning() const
				{
					return;
				}
				CBook( CBook &&_book )
					:m_level( _book.m_level ),
					m_paper( std::move( _book.m_paper ) ),
					m_name( std::move( _book.m_name ) )
				{
					m_level = 0;
					//m_paper = std::move( CPaper() );
					m_name.clear();
					std::cout << "in CBook move-constructor " << std::endl;
				}
			private:
				int		m_level;
				CPaper	m_paper;
				std::string		m_name;
			};

			void test()
			{
#include <utility>

				std::cout << "// -----------------------------------" << std::endl;
				CBook yuwen;
				yuwen.DisWarning();
				CBook shuxue = CBook();
				CBook hauxue = std::move( CBook() );
			}


		}

	}
	namespace return_rvalue_lvalue_reference
	{
		namespace first
		{
			/*
				vc++2013����֧�� C++11 ����������﷨
			*/

#include <utility>
			class CBook
			{
			public:
				CBook& Read()
				{
					return *this;
				}
				CBook&& Write()
				{
					return std::move( *this );
				}
				CBook& operator=( int _level )
				{
					m_level = _level;
					
					return *this;
				}
				int GetLevel() const
				{
					return m_level;
				}
				CBook CreateBook()
				{
					return CBook();
				}

			private:
				int		m_level;
			};

			void test()
			{
				std::cout << "// --------------------------------------------" << std::endl;
				CBook yuwen;
				yuwen.Read() = 3;
				yuwen.Write() = 100;

				std::cout << yuwen.GetLevel() << std::endl;

				// �� C++ 11 �л���ר�ŵ���ֵ�����﷨��ֹ���ֶ���ֵ��ֵ�ķ�ʽ����VC2013��û��ʵ��
				yuwen.CreateBook() = 200;

			}
		}

	}

}



void CTestor::Test()
{		
	{
		//using namespace test_copy_constructor;
		//test();
	}
	// -----------------------
	{
		//using namespace test_destructor;
		////private_destructor::test();
		////delete_destructor::test();
		////use_destructor::test();
		//three_five_principle::test();
	}
	// -----------------------
	{
		using namespace test_rvalue_ref;
		simple_rvalue::test();
		move_constructor_and_assignment::test();
		explore_synthesized_move_control::first::test();
		explore_synthesized_move_control::second::test();
		return_rvalue_lvalue_reference::first::test();
	}

}