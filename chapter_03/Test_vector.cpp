#include "Test.h"
#include <vector>
#include <iostream>
#include <typeinfo>

using std::vector;

void CTestor::Test()
{
	vector<int> vec_1;
	vector<int> vec_2( vec_1 );
	vector<int> vec_3 = vec_2;
	vector<int> vec_4( 5 );
	vector<int> vec_5( 5, 10 );
	vector<int> vec_6 = { 1 };
	vector<int> vec_7{ 2 };

	const vector<int>::size_type sz = vec_1.size();
	std::cout << "size of empty vec_1 is : " << sz << std::endl;
		
	for( unsigned int i = 0; i < 10; ++i )
	{
		vec_1.push_back( i );
	}


	//typedef vector<int>::size_type v_size_type;
	//v_size_type sz_1 = vec_1.size();
	//std::cout << "size of vec_1 is : " << sz_1 << std::endl;

	//std::cout << "the return type of operator [] is : "
	//	<< typeid( decltype( vec_1[0] ) ).name()
	//	<< std::endl;

	vec_1[0] = 99;
	
	
	for( auto a : vec_1 )
	{
		std::cout << "value is : " << a << std::endl;
	}

	for( auto &a : vec_1 )
	{
		a = a + 5;
		std::cout << std::endl << std::endl
			<< "value is : " << a << std::endl;
	}



	using viter = vector<int>::iterator;
	
	vector<int>::iterator iter_1;
	iter_1 = vec_1.begin();
	vector<int>::const_iterator iter_1_1 = vec_1.cbegin();


	viter iter_2;
	iter_2 = vec_1.end();
	vector<int>::const_iterator iter_2_1 = vec_2.cend();

	std::cout << "--------" << std::endl;
	
	while( iter_1 != iter_2 )
	{
		std::cout << "value is : " << ( *iter_1 ) << std::endl;
		++iter_1;
	}


	std::cout << std::endl << "/----------------------" << std::endl;

	const vector<int> vec_8( vec_1 );
	vec_1 = vec_2;  // 到此处， 之前代码中 关于 vec_1的 迭代器 全部失效

	std::cout << "vec_1 now is empty or not : " << vec_1.empty() << std::endl;


	//viter iter_3 = vec_8.begin();  // error
	//const viter iter_3 = vec_8.begin() // error
	vector<int>::const_iterator iter_3 = vec_8.begin();
	vector<int>::const_iterator iter_4 = vec_8.end();

	while( iter_3 != iter_4 )
	{
		std::cout << "print value  : " << ( *iter_3 ) << std::endl;
		++iter_3;
	}


}