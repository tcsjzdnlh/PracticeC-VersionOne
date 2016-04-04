
#include "Test.h"
#include <iostream>
#include <string>
namespace xfs
{
	namespace one_string_connector
	{

#define Warning( exp ) \
	if( exp ) std::cout << "exp: "<<#exp  " is not allowed ";

		void test()
		{
			Warning( 5 )
		}
	}

	namespace example_for_string_connector_from_internet
	{
		#define WARN_IF(EXP) if( EXP ) fprintf( stderr, "warning: "#EXP )
		
		#define STR(s) #s

		#define _STRI(s) #s
		#define STRI(s) _STRI(s) //转换宏
				
		#define paster(n) printf("token#n = %d \n", token##n )

		#define _CONS(a, b) int(a##+##b)
		#define CONS(a, b) _CONS(a, b) //转换宏

		#define  _GET_FILE_NAME(f)   #f
		#define  GET_FILE_NAME(f)    _GET_FILE_NAME(f)  //转换宏

		#define  _TYPE_BUF_SIZE(type)  sizeof #type
		#define  TYPE_BUF_SIZE(type)   _TYPE_BUF_SIZE(type) 

		#define D(x)  #@x  //仅对单一标记转换有效

		void test()
		{
			int divider = 0;
			WARN_IF( divider == 0 );//warning: divider == 0 

			printf( "\n int max : %s \n", STR( INT_MAX ) );//int max: INT_MAX

			printf( "int max : %s \n", STRI( INT_MAX ) );//int max: 2147483647

			int token9 = 9;
			paster( 9 );//token9 = 9 

			int A = 15, B = 2;
			printf( "A + B = %d \n", CONS( A, B ) );//A + B = 17

			char  FILE_NAME[] = GET_FILE_NAME( __FILE__ );
			std::cout << FILE_NAME << std::endl; 
			//11 = "" f = "" pre = "" return = "" test7 = "" test8 = "" tmp.cpp = "" > <p> < / p><p> < / p>< / file_name << endl; > < / iostream >

		}
	}

	namespace enum_to_string
	{
		
		class CAction
		{
		public:
			CAction( std::string &_strName )
			{
				m_strName = _strName;
			}
			std::string GetName() const
			{
				return m_strName;
			}
		private:
			std::string			m_strName;
		};

		
		enum EActions { eCut = 0, eCopy, ePaste, eDel };
		CAction *pActions[4];



		#define ToString( exp ) #exp
		//#define ToStringMedia( exp )  ToString( exp )

		#define ToStringM1( exp )  ToString( exp )
		#define Exp(exp)				   ToStringM1( EActions(0##+##exp) )//EActions(0##+##exp)
		//#define ToStringMedia( exp )  EActions e = EActions( int(exp) ); ToString( e )


		void test()
		{
			EActions e = eCut;
			while( e <= eDel )
			{
				std::string strName( Exp(e)/*ToStringM1( Exp(e) )*/ );
				pActions[e] = new CAction( strName );
				e = EActions( e + 1 );
				std::cout << pActions[e]->GetName() << std::endl;
			}
		}
	}


	void CTestor::Test()
	{
		//one_string_connector::test();
		//example_for_string_connector_from_internet::test();
		//enum_to_string::test(); // 没有达成目标
	}

}