#include <iostream>
#include <algorithm>
#include <list>
#include <cstdlib>
#include <ctime>
#include "Test.h"


using namespace std;

std::list<unsigned int> g_rsltlst;
std::list<unsigned int > g_pricelst;
void InitGlobalPriceList()
{
	unsigned int span = 6;
	srand( time( 0 ) /*1*/ );
	for( unsigned int i = 0; i != span; ++i )
	{
		
		g_pricelst.push_back( rand() % span + 1 );
	}

	cout << endl << "price list initialized ..."<< endl;
	for( auto & price : g_pricelst )
	{
		cout << "price is : " << price << endl;
	}
}




void CTestor::Test()
{
	
	InitGlobalPriceList();


	unsigned int begin = ( *( g_pricelst.begin() ) );
	auto iter = std::partition( g_pricelst.begin(), g_pricelst.end(), 
								[&]( unsigned int const& val )
								{
									return val < begin;
								} );



	//auto iter = std::stable_partition( g_pricelst.begin(), g_pricelst.end(),
	//									[&]( unsigned int const& val )
	//									{
	//										return val < begin;
	//									} );



	cout << endl << endl << "after std::partition() called , price list values are: " << endl;
	for( auto & price : g_pricelst )
	{
		cout << "price is : " << price << endl;
	}

	cout << endl << "the divided point value is : " << ( *iter ) << endl << endl;


	// splice，结果不包括 iter
	g_rsltlst.splice( g_rsltlst.begin(), g_pricelst, g_pricelst.begin(), iter );
	
	
	cout << "after splice, price list values are: " << endl;
	for( auto & price : g_pricelst )
	{
		cout << price << endl;
	}


	cout << "result list values are : " << endl;
	for( auto & price : g_rsltlst )
	{
		cout << price << endl;
	}

}


//template <class BidirectionalIterator, class UnaryPredicate>
//BidirectionalIterator partition( BidirectionalIterator first,
//	BidirectionalIterator last, UnaryPredicate pred )
//{
//	while( first != last ) 
//	{
//		while( pred( *first ) ) 
//		{
//			++first;
//			if( first == last ) return first;
//		}
//		do 
//		{
//			--last;
//			if( first == last ) return first;
//		} while( !pred( *last ) );
//		swap( *first, *last );
//		++first;
//	}
//	return first;
//}
template<typename T>
std::list<T> DoSort( std::list<T> & _chunkdata )
{
	if( _chunkdata.empty() )
	{
		return _chunkdata;
	}

	std::list<T> rslt;
	rslt.splice( rslt.begin(), _chunkdata, _chunkdata.begin() );

	
	T const & partition_value = *( rslt.begin() );

	
	typename list<T>::iterator divide_pointe 
	= std::partition( _chunkdata.begin(), _chunkdata.end(), 
						[&]( T const & _value )
						{
							return _value < partition_value;
						} );





}