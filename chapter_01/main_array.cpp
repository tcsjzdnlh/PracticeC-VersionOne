#include <cstddef>
#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::size_t;
using std::string;


int main()
{
	//constexpr size_t size = 5;
	const size_t size = 5;
	int a[size] = { };
	
	int (&aref)[size] = a;  // 一个引用 aref，所绑定的对象为 一个数组对象a
	int (*pa)[size] = &a;  // 一个指针pa，所指对象为一个数组对象a

	int rv = aref[0];
	int v = ( *pa )[0];

	cout << "pa value is:    " << pa << endl 
		 << "&pa value is:   " << &pa << endl
		 << "(*pa) value is: " << ( *pa ) << endl
		 << "a value is:     " << a << endl
		 << "&a value is:    " << &a << endl;

	// C++11中 对数组的支持
	for( auto b = std::begin( a ), e = std::end( a ); b != e; ++b )
	{

	}
	
	
	char namestr[] = { 'c', '+', '+' };
	cout << namestr << endl;

	char bookstr[] = { 'c', '+', '+', '\0' };
	cout << bookstr << endl;
	string s = "hello \0";
	cout << s << endl;
	cout << s.c_str() << endl;
	return 0;
}