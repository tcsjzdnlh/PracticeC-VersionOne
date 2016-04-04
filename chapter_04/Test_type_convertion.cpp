#include "Test.h"
#include <iostream>

namespace test_chapter_04
{
	namespace test_size_of
	{
		void test()
		{
			int a[] = { 2, 3, 50, 100 };
			std::cout << "sizeof( a ) : " << sizeof( a ) << std::endl;
		}
	}
	namespace test_type_conversion
	{
		namespace first
		{

			class CPanda
			{
			private:
				int		m_weight;
			};

			class CBook
			{
			public:
				operator CPanda()
				{
					return CPanda();
				}
			private:
				int		m_pages;
			};

			
			void test()
			{
				CPanda pao;

				//int a_1 = static_cast<int>( pao );		// error
				// int a_2 = reinterpret_cast<int>( pao );   //  error
				int a_3 = reinterpret_cast<int>( &pao );
				// CPanda pao_1 = reinterpret_cast<CPanda>( 100 );  


				// CBook yuwen = reinterpret_cast<CBook>( pao );  // error
				//CBook yuwen = CBook( pao );	// error
				//CBook yuwen = (CBook)pao;		// error

				CBook *pYuwen_1 = reinterpret_cast<CBook*>( &pao );
				//CBook *pYuwen_2 = static_cast<CBook*>( &pao );	// error


				int b = 3;
				int *p_b_1 = &b;
				char *p_b_2 = reinterpret_cast<char*>( p_b_1 );
				//char *p_b_3 = static_cast<char*>( p_b_1 );   // error
			}
		}
	}

	namespace test_aaa
	{
		int add_number( int n )
		{
			static int i = 100;
			i += n;
			return i;
		}
		
		
		void test()
		{
			int k = add_number( 100 );
			k += add_number( 100 );
			printf( "%d", k );
			return ;
		}
	}

}
void CTestor::Test()
{

	{
		using namespace test_chapter_04;
		//test_size_of::test();
		//test_type_conversion::first::test();
		test_aaa::test();
	}


}
