#include <list>
#include <iostream>
#include "Test.h"

using namespace std;


list<int> g_pricelst;
void InitGlobalPriceList()
{
	for( unsigned int i = 0; i != 6; ++i )
	{
		g_pricelst.push_back( i );
	}
}



void CTestor::Test()
{
	//g_pricelst.push_back( 2 );
	//g_pricelst.push_back( 1 );


	InitGlobalPriceList();

	list<int> rslt;
	//rslt.splice( rslt.begin(), g_pricelst, g_pricelst.begin() );
	rslt.splice( rslt.end(), g_pricelst, g_pricelst.begin() );


	unsigned int i = 0;
	for( auto& price : g_pricelst )
	{
		cout << "price_ "<< i <<" is:  " << price << endl;
		++i;
	}

	unsigned int u = 0;
	for( auto & price : rslt )
	{
		cout << "rslt price_" << u << " is : " << price << endl;
		++u;
	}



}