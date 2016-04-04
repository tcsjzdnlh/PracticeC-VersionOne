#include "Test.h"

#include <iostream>
#include <string>

#include <cctype>   // for functions to process character
#include <typeinfo>




using std::cout;
using std::cin;
using std::endl;
using std::string;


void CTestor::Test()
{
	// --- test cctype functions --------
	{

		char a = 'a';		
		a = '\0';
		a = '\t';
		a = '\012';
		a = '\141';
		a = '\x61';


		int rslt = isupper( a );
		cout << "isupper: " << rslt << std::endl;
		
		rslt = islower( a );
		cout <<"islower: " << rslt << std::endl;

		rslt = isdigit( a );
		cout << "isdigit: " << rslt << std::endl;

		rslt = isxdigit( a );
		std::cout << "isxdigit: " << rslt << std::endl;


		rslt = isalnum( a );
		std::cout << "isalnum: " << rslt << std::endl;
		
		rslt = isalpha( a );
		std::cout << "isalpha: " << rslt << std::endl;

		rslt = isgraph( a );
		std::cout << "isgraph: " << rslt << std::endl;

		rslt = isspace( a );
		std::cout << "isspace: " << rslt << std::endl;

		rslt = isblank( a );
		std::cout << "isblank: " << rslt << std::endl;

		rslt = ispunct( a );
		std::cout << "ispunct: " << rslt << std::endl;

		rslt = iscntrl( a );
		std::cout << "iscntrl: " << rslt << std::endl;
		
		rslt = isprint( a );
		std::cout <<"isprint: " << rslt << std::endl;


		std::cout << toupper( a ) << std::endl;
		std::cout << tolower( a ) << std::endl;


		// ------------------------------------------------------------


		//
		//a = 'A';
		//rslt = islower( a );
		//std::cout << rslt << std::endl;

		//rslt = isupper( a );
		//std::cout << rslt << std::endl;


		//int b = 1;
		//rslt = isdigit( b );
		//std::cout << b << std::endl;




		// ---------------------------------------------
		
		std::cout << std::endl << "// --------------------------------" << std::endl;

#include <cstring>
		// include <cstring> for : strlen, strcmp, strcat, strcpy
#include <cstddef>
		// include <cstddef> for : size_t


		char *p_str_1 = "hello world !";
		char p_str_2[] = "hello world !";
		char p_str_3[] = { 'h', 'e', 'l', 'l', 'o' };
		char p_str_4[] = { 'h', 'e', 'l', 'l', 'o', '\0' };

		size_t length = strlen( p_str_1 );
		std::cout << "hello world ! lenght is : " << length << std::endl;

		int rslt_strcmp = strcmp( p_str_1, p_str_2 );
		std::cout << "are p_str_1 and p_str_2 is same ? : " << rslt_strcmp << std::endl;

		size_t length_2 = strlen( p_str_3 );
		std::cout << "length of p_str_3 is : " << length_2 << std::endl;

		size_t length_3 = strlen( p_str_4 );
		std::cout << "length of p_str_4 is : " << length_3 << std::endl;

#define _CRT_SECURE_NO_WARNINGS
		char p_str_5_1[] = "hello, ";
		char p_str_5_2[] = "world !";
		
		const size_t length_5 = 100;
		char buffer_5[length_5] = { '\0' };

		// _CRT_SECURE_NO_WARNINGS
		//strcat( buffer_5, p_str_5_1 );
		//std::cout << "strcat result is : " << buffer_5 << std::endl;

		// error way of use
		//strcat( p_str_5_1, p_str_5_2 );
		//std::cout << "strcat result is : " << p_str_5_1 << std::endl;

		strcpy_s( buffer_5, length_5, p_str_5_1 );
		strcat_s( buffer_5, length_5, p_str_5_2);
		std::cout << "content of buffer_5 is : " << buffer_5 << std::endl;
		

	}
}