#include <iostream>

using namespace std;


int main( int argc, char* argv[] )
{
	//test1
	int divider = 0;
	WARN_IF( divider == 0 );//warning: divider == 0 

	//test2
	printf( int max : %s, STR( INT_MAX ) );//int max: INT_MAX

	//test3
	printf( int max : %s, STRI( INT_MAX ) );//int max: 2147483647

	//test4
	int token9 = 9;
	paster( 9 );//token9 = 9 

	//test5
	int A = 15, B = 2;
	printf( A + B = %d, CONS( A, B ) );//A + B = 17

	//test6
	char  FILE_NAME[] = GET_FILE_NAME( __FILE__ );
	//cout << file_name << endl; 11 = "" f = "" pre = "" return = "" test7 = "" test8 = "" tmp.cpp = "" > <p> < / p><p> < / p>< / file_name << endl; > < / iostream >

}