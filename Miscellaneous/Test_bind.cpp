#include "Test.h"

void CTestor::Test()
{

}

////---------------------------网上摘抄 bind 原理 的简易手动实现
//namespace
//{
//	class placeholder_ {};
//	placeholder_ __1;
//}
//
//template <typename R, typename T, typename Arg>
//class simple_bind_t
//{
//private:
//	typedef R( T::*F )( Arg );
//	F f_;
//	T* t_;
//	Arg& a_;
//
//public:
//	simple_bind_t( F f, T* t, Arg &a )
//		: f_( f ), t_( t ), a_( a )
//	{}
//
//	R operator()()
//	{
//		return ( t_->*f_ )( a_ );
//	}
//};
//
//template <typename R, typename T, typename Arg>
//class simple_bind_t2
//{
//private:
//	typedef R( T::*F )( Arg );
//	F f_;
//	T* t_;
//
//public:
//	simple_bind_t2( F f, T* t )
//		: f_( f ), t_( t )
//	{}
//
//	R operator()( Arg& a )
//	{
//		return ( t_->*f_ )( a );
//	}
//};
//
//template <typename R, typename T, typename Arg>
//simple_bind_t<R, T, Arg> simple_bind( R( T::*f )( Arg ), T* t, Arg& a )
//{
//	return simple_bind_t<R, T, Arg>( f, t, a );
//}
//
//template <typename R, typename T, typename Arg>
//simple_bind_t2<R, T, Arg> simple_bind( R( T::*f )( Arg ), T* t, placeholder_& a )
//{
//	return simple_bind_t2<R, T, Arg>( f, t );
//}
//
//class bind_test
//{
//public:
//	void print_string( const std::string str )
//	{
//		printf( "%s", str.c_str() );
//	}
//};
//
//void test()
//{
//	bind_test t;
//	std::string h = "hehe\n";
//	simple_bind( &bind_test::print_string, &t, h )( );
//	simple_bind( &bind_test::print_string, &t, __1 )( h );
//	boost::function<void( const std::string )> f;
//	f = simple_bind( &bind_test::print_string, &t, __1 );
//	f( h );
//}




