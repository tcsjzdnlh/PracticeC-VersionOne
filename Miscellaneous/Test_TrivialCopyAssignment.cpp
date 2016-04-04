#include <iostream>
#include "Test.h"

using namespace std;

class CBook
{
public:
	virtual unsigned int GetPrice()
	{
		cout << endl << "virtual function GetPrice() called ... " << endl;
		return 0;
	};
	virtual unsigned int GetPages()
	{
		cout << endl << "virtual function GetPages() called ... " << endl;
		return 0;
	};
};






void CTestor::Test()
{

	CBook Yuwen;
	CBook Shuxue;


	int *pVirtable_1 = reinterpret_cast<int*>( &Yuwen );
	int *pVirtable_2 = reinterpret_cast<int*>( &Shuxue );

	bool bRslt = ( ( *pVirtable_1 ) == ( *pVirtable_2 ) );

	cout << endl << "pVirtable_1, pVirtable_2 values are : " << endl
		<< ( *pVirtable_1 ) << endl
		<< ( *pVirtable_2 ) << endl;

	

	
	
	



}