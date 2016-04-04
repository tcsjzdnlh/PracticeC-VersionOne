#include "Test.h"
#include <iostream>
#include <list>
#include <cstdint>


namespace xfs
{
	
	std::list<int32_t>		g_datas;
	
	class CBook
	{
	public:

	};

	class CApple
	{
	public:

	};

	void PrepareData()
	{
		int32_t counts = 10;

		while( counts )
		{
			g_datas.push_back( counts );
			--counts;
		}
	}


	void CTestor::Test()
	{
		//PrepareData();

		//std::list<int32_t>::iterator iter = g_datas.begin();
		//++iter;
		//--iter;


		//for( auto fbiter = g_datas.begin(); fbiter != g_datas.end(); ++fbiter )
		//{
		//	std::cout << ( *fbiter ) << std::endl;
		//}


		//++iter;
		//std::list<int32_t>::iterator rsltIter = g_datas.insert( iter, 100 );
		//std::cout << "rslt iter is: " << ( *rsltIter ) << std::endl;


		//std::cout << "-----------------" << std::endl;

		//for( auto fbiter = g_datas.begin(); fbiter != g_datas.end(); ++fbiter )
		//{
		//	std::cout << ( *fbiter ) << std::endl;
		//}


		// ----------------------------------------------------------------
		// ----------------------------------------------------------------

		//std::list<CApple>		apples;
		//std::list<CApple>::iterator		iter_1 = apples.end();
		//++iter_1;
		
	

		// ----------------------------------------------------------------
		// ----------------------------------------------------------------
		
		//
		//std::list<uint32_t> books;

		//auto iter_1 = books.begin();
		//auto iter_1_1 = iter_1;

		////iter_1 = books.end();

		//books.insert( iter_1, 100 );		
		////if( iter_1 == iter_1_1 )
		////{
		////	std::cout << "iter_1 equal to iter_1_1" << std::endl;
		////}

		//books.insert( iter_1, 200 );

		//books.insert( iter_1_1, 300 );
		//

		//++iter_1;

		//for( auto f2iter = books.begin(); f2iter != books.end(); ++f2iter )
		//{
		//	std::cout << ( *f2iter ) << std::endl;
		//}



		// ----------------------------------------------------------------
		// ----------------------------------------------------------------

		typedef std::list<uint32_t>::iterator iter;
		
		std::list<uint32_t> books;
		iter iterBegin = books.begin();
		iter iterEnd = books.end();

		if( iterBegin == iterEnd )
		{
			std::cout << "iterBegin is equal to iterEnd " << std::endl;
		}

		iter iterRslt = books.insert( iterEnd, 5 );

		if( iterRslt == iterEnd )
		{
			std::cout << "iterRslt is equal to iterEnd " << std::endl;
		}

		for( iter pos = books.begin(); pos != books.end(); ++pos )
		{
			std::cout << ( *pos ) << std::endl;
		}



	}
}

