#include "Test.h"
#include <iostream>


void test()
{
	std::cout << "// ------------------------------------------------" << std::endl;
}


namespace test_lambda
{
	namespace lambda_definition
	{
				
		void test()
		{
			std::cout << "// ------------------------------------------------" << std::endl;
			
			auto f = []{ return 1; };
			std::cout << "lambda call resualt : " << f() << std::endl;
			
			
		}

	}
	namespace lambda_parameter
	{
		void test()
		{
			std::cout << "// ------------------------------------------------" << std::endl;

			auto f = []( int _a, int _b ){ return _a + _b; };

			std::cout << "lambda call resualt : " << f( 3, 5 ) << std::endl;

		}
	}
	namespace lambda_return_type
	{
		void test()
		{
			std::cout << "// ------------------------------------------------" << std::endl;

			// omitted return type, and lambda body not only a return expression, 
			// compiler should deduce it as return void type, but here is not
			auto e = []()
			{
				std::cout << "omitted return type ... " << std::endl;
				return true;
			};


			e();
			
			auto f = [] () ->bool 
				{
					std::cout << "hello lambda " << std::endl;
					return true;
				};

			std::cout << "lambda call resualt : " << f() << std::endl;
			std::cout << "type of f : " << typeid( f ).name() << std::endl;

		}
	}
	namespace lambda_capture_variable
	{
		void test()
		{
			std::cout << "// ------------------------------------------------" << std::endl;

			int a = 1;
			int b = 3;

			auto f = [&a, b]() ->bool
			{
				a += b;
				return true;
			};


			f();

			std::cout << "lambda call resualt : " << a << std::endl;

		}
	}
	namespace lambda_capture_defualt_type
	{
		void test()
		{
			std::cout << "// ------------------------------------------------" << std::endl;

			int a = 1;
			int b = 3;
			int c = 100;


			auto d = [&]() ->bool
			{
				++a;
				++b;
				++c += b;

				return true;
			};
			
			d();


			auto e = [=]() ->bool
			{
				// ++a; // error, a is not modifiable
				//++b; // error, b is not modifiable
				// ++c += b; // error, c is not modifiable

				return true;
			};


			e();

			auto f = [&, b]() ->bool
			{
				++a;
				//++b; // error, b is not modifiable
				++c += b;
				
				return true;
			};


			f();

			std::cout << "lambda call resualt a, b, c : " 
				<< a << ", " 
				<< b << ", "
				<< c << ", "
				<< std::endl;

			auto g = [=, &b]() ->bool
			{
				// ++a; // // error, b is not modifiable
				++b;
				// ++c += b; // // // error, b is not modifiable

				return true;
			};

			g();

			std::cout << "lambda call resualt a, b, c : "
				<< a << ", "
				<< b << ", "
				<< c << ", "
				<< std::endl;
		}
	}
	namespace lambda_capture_mutable_variable
	{
		void test()
		{
			std::cout << "// ------------------------------------------------" << std::endl;

			int a = 1;
			int b = 3;

			auto f = [a]() mutable ->bool
			{
				++a;
				return true;
			};



			f();


			std::cout << "lambda call resualt f() : " << a << std::endl;

			auto g = [a]() mutable
			{

				return ++a;
			};

			int rslt = g();
			std::cout << "lambda call resualt g(): " << rslt << std::endl;

		}
	}
}

void CTestor::Test()
{
	{
		using namespace test_lambda;
		lambda_definition::test();
		lambda_parameter::test();
		lambda_return_type::test();
		lambda_capture_variable::test();
		lambda_capture_defualt_type::test();
		lambda_capture_mutable_variable::test();
	}
}