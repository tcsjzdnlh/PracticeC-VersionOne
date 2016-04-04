#include "Test.h"
#include <iostream>
#include <string>
#include <vector>
namespace test_operator_overload
{
	namespace overloaded_arithmetic
	{
		namespace test_add
		{
			namespace scenario_nonmember_function
			{
				//---- as non-member function
				class CBook
				{
				public:
					int	GetLevel() const
					{
						return m_level;
					}
					void SetLevel( int _level )
					{
						m_level = _level;
					}
				public:
					friend CBook operator+( const CBook &, const CBook & );
				private:
					int		m_level{ 1 };
				};

				CBook operator+( const CBook & _lbook, const CBook &_rbook )
				{
					CBook book;
					book.m_level = _lbook.m_level + _rbook.m_level;
					
					return book;
				}

				void test()
				{
					std::cout << "// -------------------------------------" << std::endl;

					CBook yuwen, shuxue, lishi;
					lishi = yuwen + shuxue;


					std::cout << "book total level is : "<< lishi.GetLevel() << std::endl;
				}


			}
			namespace scenario_member_function
			{
				class CBook
				{
				public:
					int GetLevel() const
					{
						return m_level;
					}
					CBook operator+( const CBook &_rbook )
					{
						CBook book;
						book.m_level = m_level + _rbook.m_level;

						return book;
					}
				private:
					int	m_level { 1 };
				};


				void test()
				{
					std::cout << "// --------------------------" << std::endl;
					CBook yuwen, shuxue, lishi;
					
					lishi = yuwen + shuxue;

					std::cout << "total book level is : " << lishi.GetLevel() << std::endl;
				}

			}
		}		
		namespace test_equal
		{
			// �ܶ�ʱ�� ������ == �����ʱ��Ҳ��Ҫ !=
			// != �� == ���ͣ�����c++��׼��ʵ���зǳ�����
			class CBook
			{
			public:
				bool operator==( const CBook &_rbook )
				{
					// ��·��ֵ��ֻ�� && ��� ����ʱ �Ż�ִ�� && �ұ�
					if( m_pages == _rbook.m_pages && 
						m_level == _rbook.m_level && 
						m_price == _rbook.m_price )
					{
						return true;
					}
					
					return false;
				}
				bool operator!=( const CBook &_rbook )
				{
					return !( this->operator==( _rbook ) );
				}
			private:
				int m_pages;
				int m_level;
				int m_price;
			};


			void test()
			{
				std::cout << "// --------------------------------------------------" << std::endl;

				CBook jihe, daishu;
				std::string strRslt = ( ( jihe == daishu ) ? "yes": "no" );
				std::cout << "is jihe == daishu ? " << strRslt << std::endl;

				strRslt.clear();
				strRslt = ( ( jihe != daishu ) ? "yes" : "no" );
				std::cout << "is jihe != daishu ? " << strRslt << std::endl;
			}

		}
		namespace test_assignment
		{
#include <initializer_list>
			// std::vector v; v = { "hello", "world" };  // ��������ʽ
			class CBook
			{
			public:
				CBook & operator=( std::initializer_list<std::string> &_il )
				{
#include <iterator> // for std::begin / std::end
					// Ϊ�˼�˵��������ֻ�ǰ� initializer_list�����ݴ�ӡ����
					// ��ʵ�Ĳ���Ӧ���� �� ����Ƿ�Ϊ �Ը�ֵ��copyһ���Ҷ������Դ���ͷ��������Դ����ֵ�����
					for( auto beg = std::begin( _il ); beg != std::end( _il ); ++beg )
					{
						std::cout << ( *beg ) << std::endl;
					}
					
					return *this;
				}
				CBook & operator=( const int _level )
				{
					m_level = _level;
					
					return *this;
				}

				int GetLevel() const
				{
					return m_level;
				}
			private:
				int m_level;
			};

			void test()
			{
				//std::vector<int> v = { 1, 2, 3 };
				//std::vector<std::string> v2;
				//v2 = { "hello", "world" };
				
				std::cout << "// ---------------------------------" << std::endl;
				
				CBook yuwen;
				std::initializer_list<std::string> il = { "hello", "world" };
				yuwen = il;
				yuwen = 5;
				yuwen = std::initializer_list<std::string>( { "hello", "world" } );
			}

		}
		namespace test_index
		{
			// ��ö��� const / non-const �����汾, ���Ҫ�� ���Բο� const_iterator/cbegin/cend ��ʵ��
			class CBook
			{
			public:
				CBook()
					//:m_level{ 1, 2 }		// error, cannot specify explicit initializer for arrays
				{
					m_level[0] = 1;
					m_level[1] = 2;
				}
			public:
				int& operator[]( const std::string _key )
				{
					if( _key == "level" )
					{
						return m_level[0];
					}

					return m_level[1];
				}
				const int& operator[]( const std::string _key ) const
				{
					if( _key == "level" )
					{
						return m_level[0];
					}

					return m_level[1];
				}
			private:
				int m_level[2];
			};

			void test()
			{
				std::cout << "// --------------------------------" << std::endl;
				CBook yuwen;
				std::cout << "yuwen[\"level\"] value is : " << ( yuwen["level"] ) << std::endl;
			}

		}
		namespace test_crement
		{
			// pre-increment / post-increment
			class CBook
			{
			public:
				CBook( int _level )
					:m_level( _level )
				{

				}
				int GetLevel() const
				{
					return m_level;
				}
			public:
				// return reference and no parameter
				CBook& operator++( )
				{
					++m_level;
					return *this;
				}
				// return object and has a int type parameter
				CBook operator++( int )
				{
					CBook book(0);
					book.m_level = m_level;

					++m_level;

					return book;
				}
			private:
				int m_level;
			};


			void test()
			{
				std::cout << "// -------------------------------" << std::endl;

				CBook yuwen( 1 );
				
				yuwen.operator++( );	// pre-increment
				yuwen.operator++( 0 ); // post-increment
				
				std::cout << "pre-increment CBook object : " << ( ++yuwen ).GetLevel() << std::endl;
				std::cout << "post-increment CBook object : " << ( yuwen++ ).GetLevel() << std::endl;
				std::cout << "current level of CBook : " << yuwen.GetLevel() << std::endl;

				yuwen.operator++( );	// pre-increment
				yuwen.operator++( 0 ); // post-increment
			}

		}
		namespace test_arrow
		{
			// operator* / operator-> �ķ���ֵ �������޶��ģ�������ʧȥ�䱾��������
			class CBook
			{
			public:
				int GetLevel() const
				{
					return m_level;
				}
				void SetLevel( int _level )
				{
					m_level = _level;
				}
			private:
				int m_level;
			};

			class CBookPtr
			{
			public:
				CBookPtr( CBook * const _pbook )
					:m_pBook( _pbook )
				{}
			public:
				CBook& operator*( ) const
				{
					return *m_pBook;
				}
				CBook* operator->( ) const
				{
					//return m_pBook;
					return &( operator*( ) );		// ����ί��
				}

			private:
				CBook		*m_pBook{ nullptr };
			};


			void test()
			{
				std::cout << "// --------------------------------------" << std::endl;
				
				
				CBook yuwen;
				yuwen.SetLevel( 20 );

				CBookPtr pYuwen = &yuwen;
				
				int level_1 = ( *pYuwen ).GetLevel();
				int level_2 = pYuwen->GetLevel();


				std::cout << "level_1 : " << level_1 << std::endl;
				std::cout << "level_2 : " << level_2 << std::endl;


				level_1 = ( pYuwen.operator*( ) ).GetLevel();
				level_2 = ( pYuwen.operator->( ) )->GetLevel();
				


				std::cout << "level_1 : " << level_1 << std::endl;
				std::cout << "level_2 : " << level_2 << std::endl;

			}



		}
		namespace test_function_call
		{
			namespace common_functor
			{

				class CBook
				{
				public:
					typedef int (*pf)( int );

				public:
					CBook() = default;
					CBook( pf _pf, int _param )
						:m_pf(_pf), m_param( _param )
					{

					}
				public:
					void operator()()
					{
						if( m_pf )
						{
							m_pf( m_param );
						}
						
						std::cout << "default function call : " << __FUNCSIG__ << std::endl;

					}
					int operator()( int _parameter )
					{
						std::cout << "one parameter function call : " << __FUNCSIG__ << std::endl;
						return 0;
					}
				private:
					int m_param;
					pf  m_pf{ nullptr };
				};

				
				int SayHi( int _param )
				{
					std::cout << "SayHi function called ... " << std::endl;
					
					return _param;
				}
				void test()
				{

					std::cout << "// ----------------------------------------" << std::endl;

					CBook yuwen( SayHi, 0 );
					yuwen();
					yuwen( 3 );

				}
			}
			


		}
		namespace test_type_conversion
		{
			
			namespace scenario_definition
			{
				class CPages
				{
				public:
					int ReportPages() const
					{
						std::cout << "pages ..." << std::endl;
						return 0;
					}
				private:

				};
				class CBook
				{
				public:
					operator int () const
					{
						return m_level;
					}
					operator CPages () const
					{
						return m_pages;
					}

				private:
					int m_level;
					CPages m_pages;
				};

				void test()
				{
					std::cout << "// --------------------------------------" << std::endl;
					
					CBook yuwen;
					int level = yuwen + 3;
					( (CPages)yuwen ).ReportPages();


				}

			}
			namespace scenario_ambiguous_one
			{
				// one_class_can_convert_to_another_class_throgh_many_ways
				
				class CBook;

				class CBamboo
				{
				public:
					operator CBook() const;   // way 1 : convert CBamboo to CBook
				};


				class CBook
				{
				public:
					CBook() = default;
					CBook( const CBamboo &_bamboo )
					{

					}   // way 2: convert CBamboo to CBook;
				};

				//---
				CBamboo::operator CBook() const
				{
					return CBook();
				}



				void Read( CBook _book )
				{}

				void test()
				{
					//Read( CBamboo() ); // ambiguous ����
				}

				
			}
			namespace scenario_ambiguous_two
			{
				// two built-in type conversion in one class
				class CBook
				{
				public:
					operator int() const
					{
						return m_level;
					}
					operator double() const
					{
						return ( m_level + 3.14 );
					}
				private:
					int m_level;
				};

				void f_ambiguous( long double )
				{

				}

				void test()
				{
					CBook yuwen;
					//f_ambiguous( yuwen );  // ambiguous occured
				}


			}
			namespace scenario_ambiguous_three
			{
				class CYuwen
				{
				public:
					CYuwen( int _level )
					{
						m_level = _level;
					}
				private:
					int m_level;
				};

				class CShuxue
				{
				public:
					CShuxue( int _level )
					{
						m_level = _level;
					}
				private:
					int m_level;
				};

				void f_overload( CYuwen _yuwen )
				{}
				void f_overload( CShuxue _shuxue )
				{}

				void test()
				{
					// f_overload( 3 ); // ambiguous occured
				}

			}
			namespace scenario_ambiguous_four
			{
				// overload operator 
				class CBook
				{
				public:
					CBook() = default;
					CBook( int _level )
						:m_level( _level )
					{}
				
				public:
					operator int() const
					{
						return m_level;
					}

				public:
					CBook operator+ ( const CBook &_book )
					{
						std::cout << "function called : " << __FUNCSIG__ << std::endl;

						CBook book;
						book.m_level = m_level + _book.m_level;
						
						return book;
					}
					//CBook operator+ ( int _level )
					//{
					//	std::cout << "function called : " << __FUNCSIG__ << std::endl;
					//	CBook book;
					//	book.m_level += _level;
					//	return book;
					//}

				public:
					friend CBook operator +( const CBook &_book, int _level );
					
				private:
					int m_level = 0;
				};

				//CBook operator+( const CBook &_book, int _level )
				//{
				//	CBook book;
				//	book.m_level = _book.m_level + _level;
				//	
				//	return book;
				//}


				void test()
				{
					std::cout << "// -------------------------------------" << std::endl;
					CBook yuwen;
					CBook shuxue;

					// yuwen + 3;	// error, ambiguous;

					yuwen + shuxue;
				}



			}
		}
	}
	
}
namespace test_type_converstion
{

}


void CTestor::Test()
{
	{
		using namespace test_operator_overload::overloaded_arithmetic;
		test_add::scenario_nonmember_function::test();
		test_add::scenario_member_function::test();
		test_equal::test();
		test_assignment::test();
		test_index::test();
		test_crement::test();
		test_arrow::test();
		test_function_call::common_functor::test();
		test_type_conversion::scenario_definition::test();
		test_type_conversion::scenario_ambiguous_one::test();
		test_type_conversion::scenario_ambiguous_two::test();
		test_type_conversion::scenario_ambiguous_four::test();
	}
}