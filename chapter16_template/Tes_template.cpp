#include "Test.h"
#include <iostream>

#include "Book.h"
#include "template_friend.h"


#include "CYuwen.h"
#include "CShuxue.h"
#include "CHuaxue.h"
#include "CWuli.h"
#include "CLishi.h"


#include <vector>
#include <type_traits>		// for std::remove_reference
#include <utility>			// for std::move, std::forward
#include <thread>
#include <functional>

//void test()
//{
//	std::cout << "// ---------------------------------------------" << std::endl;
//}

namespace test_template
{
	namespace template_definition
	{
		namespace template_function
		{			
			template< typename T >
			void ReadBook( T _level )
			{
				std::cout << "read book level : " << _level << std::endl;
			}

			void test()
			{
				std::cout << "// ---------------------------------------------" << std::endl;
				
				ReadBook( 5 );
			}

		}

		namespace template_un_function
		{
			// M, N must be a constexpr
			template</* const */unsigned M,/* const */unsigned N>
			void ReadBook( int ( &a )[M], int ( &b )[N] )
			{
				//a[0] = b[0];

				std::cout << "a[0] : " << a[0] << std::endl
					<< "b[0] : " << b[0] << std::endl;
			}


			void test()
			{
				std::cout << "// ---------------------------------------------------" << std::endl;

				int a[10] = { 3, 9 };
				int b[6] = { 2, 8 };
				ReadBook( a, b );
			}
		}
		namespace template_inline_constexpr_function
		{
			template< typename T >
			inline void ReadBook( T _value )
			{
				std::cout << "value is : " << _value << std::endl;
			}

			template< typename T >
			/*constexpr*/ void WriteBook( T _value )
			{
				std::cout << "value is : " << _value << std::endl;
			}

			void test()
			{
				ReadBook( 20 );
				WriteBook( 30 );
			}
		}

		namespace template_compile_template
		{
			template<typename T>
			void DeclareTempalte( T _value )
			{
				std::cout << "separate template function declare and definition " << std::endl;
			}


			void test()
			{
				std::cout << "// ------------------------------------------------" << std::endl;
				DeclareTempalte( 3 );
			}
		}

//---------------------------------------------------------------------------------
//---------------------------------------------------------------------------------

		namespace template_class
		{
			template<typename T>
			class CBook
			{
			public:
				CBook() = default;
				CBook( T _level )
					:m_level( _level )
				{

				}
				virtual ~CBook() = default;
				
			public:
				T GetLevel() const
				{
					return m_level;
				}
				void SetLevel( T _level );

				//T GetLevel() const;
				//{
				//	return m_level;
				//}

			private:
				T m_level;
			};

			template<typename T >
			void CBook<T>::SetLevel( T _level )
			{
				m_level = _level;
			}

			void test()
			{
				std::cout << "// ------------------------------------------------" << std::endl;
				
				CBook<int> book( 3 );
				std::cout << "book level is : " << book.GetLevel() << std::endl;
				
				book.SetLevel( 10 );
			}
		}
		namespace using_template_class_name
		{
			template<typename T>
			class CBook
			{
			public:
				CBook& operator++( )
				{
					++m_level;

					std::cout << "pre operator++ called ... " << std::endl;

					return *this;
				}
				CBook<T>& operator--( )
				{
					--m_level;

					std::cout << "pre operator-- called ... " << std::endl;

					return *this;
				}

			public:
				CBook operator++( int );

			private:
				T m_level;
			};

			template<typename T>
			CBook<T> CBook<T>::operator++( int _value )
			{
				CBook book;
				book.m_level = m_level;
				++m_level;
				
				std::cout << "post operator++ called ... " << std::endl;
				return book;
			}



			void test()
			{
				std::cout << "// ---------------------------------------------" << std::endl;
				CBook<int> book;
				
				++book;
				book++;

				--book;


			}

		}
		namespace independent_template_member_function
		{
			template<typename T>
			class CBook
			{
			public:
				template<typename W>
				void SetLevel( W _level );

				T GetLevel() const
				{
					return m_level;
				}

			private:
				int m_level;
			};

			template<typename T>
			template<typename W>
			void CBook<T>::SetLevel( W _level )
			{
				m_level = static_cast<T>( _level );
			}


			void test()
			{
				
				std::cout << "// -----------------------------------------------" << std::endl;
				
				CBook<int> book;
				
				std::cout << "book level is : " << book.GetLevel() << std::endl;
				
				book.SetLevel( 5.9 );
				
				std::cout << "book level is : " << book.GetLevel() << std::endl;
			}

		}
		namespace normal_class_template_member_function
		{
			

			void test()
			{
				std::cout << "// -----------------------------------------------" << std::endl;


				CBook book;
				book.IncrementLevel( 50 );
				std::cout << "book level is : " << book.GetLevel() << std::endl;

			}
		}

		namespace template_class_static_member
		{
			template<typename T>
			class CBook
			{
			public:
				int GetFirstPage() const
				{
					return m_pages[0];
				}
				T GetLevel() const
				{
					return m_level;
				}
			private:
				static T m_level;
				static int m_pages[];
			};


			template<typename T>
			T CBook<T>::m_level = 0;

			template<typename T>
			int CBook<T>::m_pages[] = { 90, 20, 4, 5 };

			void test()
			{
				std::cout << "// ---------------------------------------------" << std::endl;

				CBook<int> book;
				std::cout << "book first page : " << book.GetFirstPage() << std::endl;
				std::cout << "book level is : " << book.GetLevel() << std::endl;
			}

		}
		namespace template_class_and_friend
		{


			template<typename T> 
			class CCreature;						
			
			template<typename T>
			class CBook
			{
			public:
				friend T;
			public:

				friend class CCreature < T > ;
				template<typename T> class CFood;
			private:

			};


			void test()
			{
				std::cout << "// ---------------------------------------------" << std::endl;
				CBook<int> book;
			}
		}
		namespace typename_keword
		{
			template<typename T>
			class CBook
			{
			public:
				typedef T Level;
				Level * GetLevelAddress();

				
			private:
				Level m_level;
			};

			template<typename T>
			typename CBook<T>::Level*
			CBook<T>::GetLevelAddress()
			{
				return &m_level;
			}


			void test()
			{
				std::cout << "// ---------------------------------" << std::endl;
				std::cout << __FUNCSIG__ << std::endl;
				CBook<int> book;
				
				
				// error, typename cann't be use outside template
				// typename CBook<int>::Level *p = book.GetLevelAddress(); 
				CBook<int>::Level *p = book.GetLevelAddress();
			}

		}

		namespace default_template_parameter
		{
			template<typename A, typename B= int, typename C  = double,
					 typename D = long double, typename E = bool >
			void ReadBook( A _v, B _a = 3, C _l = 3.14, D _u = 3.1, E _e = true )
			{
				int result = _v + _a + _l + _u;

				std::cout << "result is : " << result << std::endl;
			}

			template<typename T = int>
			class CBook
			{
			public:
				T GetLevel() const
				{
					return m_level;
				}
			private:
				T m_level;
			};

			template< typename T, typename W  = int >
			class CCreature
			{
			public:
				void Move()
				{

				}
			};

			void test()
			{
				std::cout << "// -----------------------------------" << std::endl;
				ReadBook( 90 );


				CBook<> book;
				std::cout << "book level is : " << book.GetLevel() << std::endl;

				CCreature<int> flyer;
			}
		}

		namespace template_instantance_control
		{
			// 进行实例化集中控制，会导致被实例化的类的所有成员函数都被实例化，包括没有用到的

			extern template class CYuwen < int > ;
			extern template class CShuxue < int > ;
			extern template class CHuaxue < int >;
			extern template class CWuli < int >;
			extern template class CLishi < int >;

			void test()
			{
				std::cout << "// -------------------------------------------" << std::endl;
				CYuwen<int> yuwen;
				CShuxue<int> shuxue;
				CWuli<int> wuli;
				CLishi<int> lishi;
				CHuaxue<int> huaxue;
			}
		}


	}
	namespace template_function_argument_deducation
	{
		namespace template_basic_type_conversion
		{
			template<typename T>
			void ReadBook( const T &_value )
			{
				std::cout << "value is : " << _value << std::endl;

				std::cout << __FUNCSIG__ << std::endl;
			}

			template<typename T>
			void WriteBook( T _a, T _b )
			{
				std::cout << __FUNCSIG__ << std::endl;
			}


			// ----------
			
			void a_1()
			{};
			void b_1()
			{}

			void test()
			{
				std::cout << "// --------------------------------------------------" << std::endl;
				
				int e = 3;
				ReadBook( e ); // const reference bind to a  non-const variable

				int a[] = { 2, 3, 5 };
				int b[] = { 29, 47, 20, 40, 10 };
				WriteBook( a, b );	// implicit convert


				WriteBook( a_1, b_1 );

			}

		}
		namespace template_function_explicit_type
		{
			template<typename T1, typename T2, typename T3>
			T1 ReadBook( T2 _t2, T3 _t3 )
			{
				std::cout << __FUNCSIG__ << std::endl;
			}

			void test()
			{
				std::cout << "// ---------------------------------------------" << std::endl;

				ReadBook<void>(1, 2);	// explicit specified void for T1
				ReadBook<void, double, long>( 9, 100 );

			}
		}
		namespace template_trailing_return_type
		{
			template< typename It >
			auto ReadBook( It beg, It end ) -> decltype( *beg )
			{
				std::cout << __FUNCSIG__ << std::endl;
				return *beg;
			}

			void test()
			{
				std::cout << "// ---------------------------------------------" << std::endl;

				std::vector<int> vec;
				vec.push_back( 3 );

				ReadBook( vec.begin(), vec.end() );
			}

		}

		namespace use_type_traits
		{
			template< typename It >
			auto ReadBook( It beg, It end )->typename std::remove_reference<decltype( *beg )>::type
			{
				std::cout << __FUNCSIG__ << std::endl;
				return *beg;
			}

			void test()
			{
				std::cout << "// ---------------------------------------------" << std::endl;

				std::vector<int> vec;
				vec.push_back( 3 );

				ReadBook( vec.begin(), vec.end() );
			}
		}
		namespace function_pointer_template_name
		{
			template<typename T1, typename T2, typename T3>
			T1 ReadBook( T2 _t2, T3 _t3 )
			{
				std::cout << __FUNCSIG__ << std::endl;
			}

			void ( *f )( int, int ) = ReadBook;

			void test()
			{
				std::cout << "// --------------------------------------------------" << std::endl;
				f( 3, 5 );
			}


		}

		namespace lreference_or_const_lreference
		{
			template<typename T>
			void Fly( T &_t )
			{
				std::cout << __FUNCSIG__ << std::endl;
			}

			template<typename T>
			void Run( const T &_t )
			{
				std::cout << __FUNCSIG__ << std::endl;
			}

			void test()
			{
				std::cout << "// ---------------------------------------" << std::endl;

				int a = 1;
				const int ca = 3;
				
				Fly( a );
				Fly( ca );
				// error, cannot convert argument 1 from 'int' to 'int &'， 也就是左值引用不能绑定到右值上
				// Fly( 5 );	
				
				Run( a );
				Run( ca );
				Run( 5 );
				
				
			}

		}
		namespace rreference_collapse
		{
			template<typename T>
			void Fly( T &&_t )
			{
				std::cout << __FUNCSIG__ << std::endl;
			}
			
			
			void test()
			{
				std::cout << "// ---------------------------------------------" << std::endl;
				
				int a = 3;
				int &refa = a;

				const int ca = a;
				const int &refca = ca;


				int *pa = &a;
				const int *pca = &ca;
				const int * const ( &refcp ) = pa;

				int &&rref = 5;


				Fly( a );
				Fly( refa );

				Fly( ca );
				Fly( refca );

				
				Fly( pa );
				Fly( pca );
				Fly( refcp );
				

				Fly( 5 );
				Fly( rref );	// reference collapse
				Fly( std::move( rref ) );
			}
		}

		namespace understand_std_move
		{


			void test()
			{
			
				std::cout << "// -----------------------------------------" << std::endl;

				int a = 3;
				int &&rrefa = static_cast<int&&>( a );
				std::cout << "rrefa : " << rrefa << std::endl;
			}
		}

		namespace use_std_forward
		{
		
			
			template<typename T1, typename T2>
			void e( T1 _t1, T2 _t2 )
			{
				std::cout << "e: " << __FUNCSIG__ << std::endl;
			}

			template<typename T1, typename T2>
			void f( T1 &_t1, T2 _t2 )
			{
				std::cout << "f: " << __FUNCSIG__ << std::endl;
			}


			template<typename T1, typename T2>
			void g( T1 &&_t1, T2 _t2 )
			{
				std::cout << "g: " << __FUNCSIG__ << std::endl;
			}





			template<typename T1, typename T2, typename T3>
			void DelegateCall( T1 _t1, T2 &&_t2, T3 &&_t3 )
			{
				std::cout << "DelegateCall : " << __FUNCSIG__ << std::endl;
				
				_t1( _t2, _t3 );

			}


			template<typename T1, typename T2, typename T3>
			void ForwardCall( T1 _t1, T2 &&_t2, T3 &&_t3 )
			{
				std::cout << "ForwardCall : " << __FUNCSIG__ << std::endl;

				_t1( std::forward<T2>( _t2 ), std::forward<T3>( _t3) );

			}
			
			
			template void e<int, int >( int _a, int _b );
			template void f<int&, int>( int &_a, int _b );
			template void g<int&&, int>( int &&_a, int _b );

			void test()
			{
				std::cout << "// -------------------------------------------------------" << std::endl;

				int a_1 = 0;
				const int ca_1 = a_1;

				int &refa = a_1;

				int &&rref = 1;


				DelegateCall( e<int, int>, a_1, ca_1 );
				DelegateCall( f<int&, int>, a_1, ca_1 );
				//DelegateCall( g<int&&, int>, rref, ca_1 );		// error

				ForwardCall( g<int&&, int>, std::move(a_1), ca_1 );

			}

		}

		namespace forward_code
		{
			//template<typename T>
			//T&& xfsforward( typename remove_reference<T>::type& _Arg )
			//{
			//	 forward an lvalue
			//	return ( static_cast<T&&>( _Arg ) );
			//};
		}
	}

	namespace template_function_overload
	{
		namespace template_overload_template
		{

			template<typename T>
			void Debug_rep( const T &_str )
			{
				std::cout<< "const T &_str called ... " << __FUNCSIG__ << std::endl;
				return;
			}

			template<typename T>
			void Debug_rep( T *_p )
			{
				std::cout<< "T *_p called ... " << __FUNCSIG__ << std::endl;
				return;
			}


			void test()
			{
				std::cout << "// ----------------------------------------" << std::endl;
				
				std::string str( "hello" );
				Debug_rep( str );		// const T &_str called 

				Debug_rep( "hello" );	// T *_p called 
				
				Debug_rep( &str );
			}
		}
		namespace template_function_overload_common_function
		{
			template<typename T>
			void Debug_rep( const T &_str )
			{
				std::cout << "const T &_str called ... " << __FUNCSIG__ << std::endl;
				return;
			}

			template<typename T>
			void Debug_rep( T *_p )
			{
				std::cout << "T *_p called ... " << __FUNCSIG__ << std::endl;
				return;
			}

			void Debug_rep( const std::string &_s )
			{
				std::cout << "const std::string &_s called ... " << __FUNCSIG__ << std::endl;
				return;
			}

			void test()
			{
				std::cout << "// ---------------------------------------------------" << std::endl;

				std::string str( "hello" );

				Debug_rep( str );


			}

		}
		namespace template_overload_and_type_conversion
		{
			template<typename T>
			void Debug_rep( const T &_str )
			{
				std::cout << "const T &_str called ... " << __FUNCSIG__ << std::endl;
				return;
			}

			template<typename T>
			void Debug_rep( T *_p )
			{
				std::cout << "T *_p called ... " << __FUNCSIG__ << std::endl;
				return;
			}

			void Debug_rep( const std::string &_s )
			{
				std::cout << "const std::string &_s called ... " << __FUNCSIG__ << std::endl;
				return;
			}

			void test()
			{
				std::cout << "// ---------------------------------------------------" << std::endl;

				

				Debug_rep( "hello" );


			}

		}

		namespace declare_all_overload_function_to_avoid_involuntary_template_instance
		{
			template<typename T>
			void Debug_rep( const T &_str )
			{
				std::cout << "const T &_str called ... " << __FUNCSIG__ << std::endl;
				return;
			}

			template<typename T>
			void Debug_rep( T *_p )
			{
				std::cout << "T *_p called ... " << __FUNCSIG__ << std::endl;
				return;
			}

			// declare function that at other namespace to avoid Debug_rep template instance
		 	void ::test_template::template_function_overload::template_overload_and_type_conversion::Debug_rep( const std::string &_s );			

			void test()
			{
				std::cout << "// --------------------------------------------------" << std::endl;
				std::cout << "test declare ... " << std::endl;
				Debug_rep( std::string( "hello" ) );


			}
		}
	}


	namespace variadic_template
	{
		namespace variadic_template_definition
		{
			
			template<typename T>
			void ReadBook( T _content )
			{
				std::cout << _content << std::endl;
			}
			
			template<typename T, typename ... Ts>
			void ReadBook( T _t, Ts ... args )
			{
				
				std::cout << "_t typeid : " << typeid( _t ).name() << std::endl;
				std::cout << "sizeof ... (args) : " << sizeof ... ( args ) 
					<< std::endl << std::endl << std::endl;
				
				std::thread t1;

				ReadBook( args ... );


			}
			
			void test()
			{
				std::cout << "// ---------------------------------------------------" << std::endl;
				
				ReadBook( 50, 30.1, "hello", 99, 200 );
			}
		}
		namespace expand_variadic_args_example
		{
			//template <typename Sig, Sig& S> struct OpF;

			//template <typename TR, typename ... Ts, TR( &f )( Ts... )>
			//struct OpF < TR( Ts... ), f >
			//{
			//};

			//int foo( int x )
			//{
			//	return 0;
			//}

			//OpF<int( int ), foo> f;


			//template<class _Fn, class... _Args>
			//explicit thread( _Fn&& _Fx, _Args&&... _Ax )
			//{	// construct with _Fx(_Ax...)
			//	_Launch( &_Thr,
			//		_STD bind( _Decay_copy( _STD forward<_Fn>( _Fx ) ), _Decay_copy( _STD forward<_Args>( _Ax ) )... ) );
			//}


			//std::bind( _Decay_copy( forward<_Fn>( _Fx ) ), _Decay_copy( forward<_Args>( _Ax ) )... )

			void test()
			{
				


			}
		}
	}


	namespace template_specialization
	{
		namespace template_function_specialization_definition
		{
			template<typename T>
			void ReadBook( T _t )
			{
				std::cout << __FUNCSIG__ << std::endl;
				std::cout << _t << std::endl;
			}

			template<>
			void ReadBook( const char * _pchar )
			{
				std::cout << "ReadBook specialization called ... " << std::endl;

			}



			void test()
			{
				std::cout << "// ---------------------------------------------" << std::endl;

				ReadBook( "hello" );

			}
		}
		namespace template_specialization_and_function_overload
		{
			template<typename T>
			void ReadBook( T _t )
			{
				std::cout << __FUNCSIG__ << std::endl;
				std::cout << _t << std::endl;
			}

			template<>
			void ReadBook( const char * _pchar )
			{
				std::cout << "ReadBook specialization called ... " << std::endl;

			}

			template<typename T, typename W>
			void ReadBook( T &_t, W _w )
			{
				std::cout << " template ReadBook overload called ... " << std::endl;
			}


			void test()
			{
				std::cout << "// ---------------------------------------------" << std::endl;

				ReadBook( "hello" );

			}
		}
		namespace template_class_whole_specialization
		{
			template<typename T>
			class CBook
			{
			public:
				void ReadBook( T _t )
				{
					std::cout << __FUNCSIG__ << std::endl;
				}
			};

			template<>
			class CBook<char*>
			{
			public:
				void ReadBook( char* _p )
				{
					std::cout << "specialization CBook ... "<< std::endl;
				}
			};


			void test()
			{
				std::cout << "// -----------------------------" << std::endl;
				CBook<char*> book;
				book.ReadBook( "hello" );
			}
		}
		namespace template_class_half_specialization
		{
			template<typename T1, typename T2>
			class CBook
			{
			public:
				void ReadBook()
				{
					std::cout << __FUNCSIG__ << std::endl;
				}
			};

			template<typename T>
			class CBook < T, int>
			{
			public:
				void ReadBook()
				{
					std::cout << "CBook<T, int> specialization called ... " << std::endl;
					std::cout << __FUNCSIG__ << std::endl;
				}
			};


			void test()
			{
				std::cout << "// ------------------------------------------" << std::endl;
				CBook<int, double> book;
				book.ReadBook();

				CBook<char, int> yuwen;
				yuwen.ReadBook();
			}

		}

		namespace template_class_memberfunction_specialization
		{
			template<bool _b>
			class CBook
			{
			public:
				void ReadBook( )
				{
					std::cout << _b << std::endl;
				}
			};

			template<>
			void CBook<true>::ReadBook()
			{
				std::cout << "hello ---> void CBook<true>::ReadBook()  " << std::endl;
			}

			void test()
			{
				std::cout << "// ----------------------------------" << std::endl;
				CBook<true> yuwen;
				yuwen.ReadBook();

				CBook<false> shuxue;
				shuxue.ReadBook();
			}

		}
	}
	
}



void CTestor::Test()
{
	
	{
		using namespace test_template;
		template_definition::template_function::test();
		template_definition::template_un_function::test();
		template_definition::template_inline_constexpr_function::test();
		template_definition::template_compile_template::test();
		template_definition::template_class::test();
		template_definition::using_template_class_name::test();
		template_definition::independent_template_member_function::test();
		template_definition::normal_class_template_member_function::test();
		template_definition::template_class_static_member::test();
		template_definition::template_class_and_friend::test();
		template_definition::typename_keword::test();
		template_definition::default_template_parameter::test();
		template_definition::template_instantance_control::test();
	}
	{
		using namespace test_template::template_function_argument_deducation;
		template_basic_type_conversion::test();
		template_function_explicit_type::test();
		template_trailing_return_type::test();
		use_type_traits::test();
		function_pointer_template_name::test();
		lreference_or_const_lreference::test();
		rreference_collapse::test();
		understand_std_move::test();
		use_std_forward::test();
	}

	{
		using namespace test_template::template_function_overload;
		
		template_overload_template::test();
		template_function_overload_common_function::test();
		template_overload_and_type_conversion::test();
		declare_all_overload_function_to_avoid_involuntary_template_instance::test();
	}

	{
		using namespace test_template::variadic_template;
		variadic_template_definition::test();

	}

	{
		using namespace test_template::template_specialization;
		template_function_specialization_definition::test();
		template_class_whole_specialization::test();
		template_class_half_specialization::test();
		template_class_memberfunction_specialization::test();
	}
}


//
//4.部分特例化
//ep1:
////general template
//template <class T1, class T2> class pail { …… };
////specialization
//template <class T1> class pail < T1, int > { …… };
//
//ep2:
//template <class T*> class Feeb { …… };
////有 Feeb<char *> fb;       则T被替换为 char
//
//ep3:
////general template
//template <class T1, class T2, class T3> class pail { …… };
//
////specialization
//template <class T1, class T2> class pail < T1, T2, T2 > { …… };
//
////specialization
//template <class T1> class pail < T1, T1*, T1* > { …… };
//*************************************************************
//pail<int, short, char*> t1;//use ep1
//
//pail<int, short, char*> t1;//use ep2
//
//pail<int, char*, char*> t1;//use ep3