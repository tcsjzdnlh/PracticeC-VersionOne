#include "Test.h"
#include <iostream>
#include <windows.h>

using namespace std;

void CTestor::Test()
{
	cout << endl << "bool size is :  " << sizeof( bool ) << endl
		<< "char size is : " << sizeof( char ) << endl
		<< "wchar_t size is : " << sizeof( wchar_t ) << endl
		<< "char16_t size is : " << sizeof( char16_t ) << endl
		<< "char32_t size is : " << sizeof( char32_t ) << endl
		<< "short size is : " << sizeof( short ) << endl
		<< "int size is : " << sizeof( int ) << endl
		<< "long size is : " << sizeof( long ) << endl
		<< "long long size is : " << sizeof( long long ) << endl
		<< "float size is : " << sizeof( float ) << endl
		<< "double size is : " << sizeof( double ) << endl
		<< "long double size is : " << sizeof( long double ) << endl;
		//<< "word size is " << sizeof( word ) << endl


//	cout << "word size is : " << sizeof( WORD ) << endl
//		<< "dword size is : " << sizeof( DWORD ) << endl
//		<< "dword32 size is : " << sizeof( DWORD32 ) << endl
//		<< "dword 64 size is : " << sizeof( DWORD64 ) << endl;
}