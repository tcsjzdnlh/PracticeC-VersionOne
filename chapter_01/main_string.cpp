#include <iostream>
#include <string>
#include <cctype>

using namespace std;

int main()
{
	string s;

	// --------------------------------------------------------------
	//// 自动忽略开头和结尾空白，且遇到下一个空白则结束输入
	//cin>>s;
	//cout<<s<<endl;

	// ---------------------------------------------------
	//while( cin >> s )
	//{
	//	cout<<s<<endl;
	//}

	
	// ---------------------------------------------------------------------------------
	//// getline 函数 从标准流中提取一行给 s，提取时，碰到 返回字符 则结束提取
	//// 并且  返回字符也被 提取且丢弃，并不放入s中
	//while( getline( cin, s ) )
	//{
	//	if( !s.empty() ) // stirng 的empty函数用法
	//	{
	//		if( s.size() > 10 )  // string 的size 函数用法
	//		{
	//			cout<<s<<endl;
	//		}
	//	}
	//}



	// ----------------------------------------------------------

	//while( getline( cin, s ) )
	//{
	//	for( auto c : s )
	//	{
	//		cout<< c << "  isalnum : " << std::isalnum( c )<<endl;
	//	}
	//	for( auto &c : s )
	//	{
	//		if( 'e' == c )
	//		{
	//			c = 'f';
	//			cout<< s <<endl;
	//			break;
	//		}
	//	}
	//}
	

	// ----------------------------------------------------------------------------------
	//char c;
	//while( cin >> c )
	//{
	//	//cout << c << " is alpha : " << std::isalpha( c ) << endl;
	//	//cout << c << " is cntrl : " << std::iscntrl( c ) << endl;
	//	//cout << c << " is digit : " << std::isdigit( c ) << endl;
	//	//cout << c << " is graph : " << std::isgraph( c ) << endl;
	//	cout << c << " is punctuation : " << std::ispunct( c ) << endl;
	//}

	
	
	// ----------------------------------------------------------------------------------
	//while( getline( cin, s ) )
	//{
	//	for( auto &c : s )
	//	{
	//		c = std::toupper( c );
	//	}

	//	cout << s << endl;
	//}

	// ----------------------------------------------------------------------------------
	//while( getline( cin, s ) )
	//{
	//	for( auto &c : s )
	//	{
	//		c = std::tolower( c );
	//	}

	//	cout << s << endl;
	//}


	//s = "hello world !";
	//string::size_type n = 1;
	//char c = s[n];
	//cout << c << endl;

	//s[n] = 'f';
	//cout << s << endl;

	s = "hello world !";
	for( decltype( s.size() ) index = 0; index != s.size() && !isspace( s[index] ); ++index )
	{
		s[index] = toupper(s[index]);
	}
	cout << s.size()<< "   " << s << endl;

	
	return 0;
}