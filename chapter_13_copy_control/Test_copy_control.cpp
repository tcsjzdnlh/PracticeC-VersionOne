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
	//wuli = shuxue;		//	全局区域不能 只能定义变量，不能运算(这里是赋值运算)

	
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
		结论：delete的 destructor 导致 全局对象 可以定义 ， new局部对象 可以，局部对象 不可以定义
		*/
		class CBook
		{
		public:

		private:
			~CBook() = default;
		};

		CBook yuwen;	// private 的 destructor 全局对象可以

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
			结论：delete的 destructor 导致 只有 new对象 可以， 全局对象/局部对象 都不可以定义
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
			// yuwen.~CBook(); // error, 显示调用析构函数 导致 析构函数会调用 2 次，程序崩溃
		}

	}
	namespace three_five_principle
	{
		/*
			需要 手写 destructor 的情况 必定 需要手写 copy-constructor/copy-assignment，
			如果 手写了 destructor，而不写 copy-constructor/copy-assignment ，
			则编译器 引入 默认的 copy-constructor / copy-assignment,
			则会导致严重的错误
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
				// 自赋值情况，且对方要有资源
				if( ( this != &_book ) && ( nullptr != _book.m_pLevel ) )
				{
					
					if( !m_pLevel )
					{
						m_pLevel = new ( std::nothrow ) int( *( _book.m_pLevel ) );
					}
					else
					{	
						// 必须先创建资源，再进行销毁自带资源，然后才是赋值
						auto *p = new ( std::nothrow ) int( *( _book.m_pLevel ) );
						if( p )
						{
							Destruct();
							m_pLevel = p;
						}
						else
						{
							// new 都发生错误了，要么没内存了，要么系统发生了严重错误
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
			int &&ref_a_1 = (int &&)a;		// 左值转化成 右值引用
			// int &&ref_2 = ref;	// error, ref 是变量表达式，变量表达式都是左值，右值引用不能绑定到左值上
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
			int &ref_b_2 = (int&)b;		// 右值引用转化成左值引用

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

			CBook( CBook &&_book ) /*noexcept*/			// vc++2013 未实现
				:m_level( _book.m_level )
			{
				_book.m_level = 0;
			}

			CBook& operator=( CBook &&_book ) /*noexcept*/		// vc++2013 未实现
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
			// CBook yuwen;	// error, 有其他形式的 constructor, 则 编译器不会 为类 生成 synthesized constructor
			CBook yuwen = CBook( 5 );
			CBook shuxue( 6 );
			shuxue = yuwen;

#include <utility>	// ------> for std::move

			CBook lishi = std::move<CBook>( CBook( 90 ) );
			lishi = std::move( CBook( 90 ) );

			CBook dili = (CBook&&)lishi;		// std::move 的本质就是 把左值转化成 右值，就像这一句

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
				CBook shuxue = std::move( CBook() );	// 当没写 move-constructor的时候，会调用 copy-constructor
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
				vc++2013还不支持 C++11 里面的这种语法
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

				// 在 C++ 11 中会有专门的右值引用语法阻止这种对右值赋值的方式，但VC2013中没有实现
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