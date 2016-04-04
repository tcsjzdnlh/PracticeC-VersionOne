#include "Test.h"
#include <iostream>

namespace test_derivered
{
	namespace derivered_definition
	{
		//class CBook_no_impl;
		//// error, a base class must be a complete defined class, not just a declare
		//class CYuwen_test_derivered : CBook_no_impl
		//{};


		class CBook
		{
		public:
			int GetPages() const
			{
				return m_pages;
			}
		private:
			int m_pages;
		};
		
		class CYuwen : public CBook
		{

		};
		// class default derivered access is : private
		class CShuxue : CBook
		{

		};
		// struct default derivered access is public
		struct SLishi : CBook
		{

		};
		struct SHuihua : private CBook
		{

		};



		void test()
		{
			CBook book;
			CYuwen yuwen;
			CShuxue shuxue;
			SLishi lishi;
			SHuihua huihua;


			yuwen.GetPages();
			// shuxue.GetPages();	// error, private 方式 继承的类 对象 不允许访问基类成员
			

			lishi.GetPages();
			// huihua.GetPages();	// error, private derivered is not access to base member function

		}
	}

	namespace derivered_construct
	{
		class CBook
		{
		public:
			CBook()
			{
				std::cout << "CBook default constructor called ... " << std::endl;
			}
			CBook( int _pages )
				:m_pages( _pages )
			{
				std::cout << "CBook constructor called ... " << std::endl;
			}
		public:
			int GetPages() const
			{
				return m_pages;
			}
		private:
			int m_pages;
		};
		
		class CYuwen : public CBook
		{
		public:
			// base class constructor is ignored, then base class default constructor called implicitly
			CYuwen()
			{
				std::cout << "CYuwen default constructor called ... " << std::endl;
			}
			CYuwen( int _level )
				:m_level( _level )
			{
				std::cout << "CYuwen constructor : " << __FUNCSIG__ << " called ... " << std::endl;
			}
			CYuwen( int _level, int _price )
				:CBook(100), m_level(_level), m_price( _price )
			{
				std::cout << "CYuwen constructor : " << __FUNCSIG__ << " called ... " << std::endl;
			}

		private:
			int m_level;
			int m_price;
		};


		void test()
		{
			std::cout << "// ------------------------------------------" << std::endl;

			CYuwen yuwen_01;
			CYuwen yuwen_02( 3 );
			CYuwen yuwen_03( 3, 30 );
		}

	}
	namespace derivered_base_construct
	{
		class CBook
		{
		public:
			CBook()
			{}
			CBook( int _pages )
				:m_pages( _pages )
			{

			}
		private:
			int m_pages;
		};

		class CYuwen : public CBook
		{
		public:
			using CBook::CBook;		// derivered constructor from base class;
		private:
			int m_level = 0;
		};

		void test()
		{
			// CYuwen yuwen( 10 );	// error, vc++2013 不支持该种用法
		}

	}
	namespace derivered_change_access
	{
		namespace scenario_common
		{
			class CBook
			{
			public:
				int GetPages() const
				{
					return m_pages;
				}

			protected:
				void SetPages( const int _level )
				{
					m_pages = _level;
				}

			private:
				void Print()
				{

				}


			private:
				int m_pages = 0;
			};

			class CYuwen : public CBook
			{
			public:
				void Report()
				{
					// Print(); // error, can't be access
					GetPages();
					SetPages( 20 );
				}

			private:


			};

			void test()
			{
				CYuwen yuwen;
				// yuwen.SetPages();	// error, can't access out of class area
			}
		}
		namespace scenario_changed
		{
			class CBamboo
			{
			public:
				int GetPages() const
				{
					return m_pages;
				}

			protected:
				void SetPages( const int _level )
				{
					m_pages = _level;
				}

			private:
				void Print()
				{

				}

			private:
				int m_pages = 0;
			};
			
			class CBook : public CBamboo
			{
			public:
				int GetPages() const
				{
					return m_pages;
				}

			protected:
				void SetPages( const int _level )
				{
					m_pages = _level;
				}
				void SayHello() const
				{}
			private:
				void Print()
				{

				}


			private:
				int m_pages = 0;
			};

			class CYuwen : public CBook
			{
			public:
				void Report()
				{
					// Print(); // error, can't be access
					GetPages();
					//SetPages( 20 );
					CBook::SetPages( 20 );
				}

			private:
				using CBook::GetPages;	// direct base class
				using CBamboo::SetPages; // indirect base class
			public:
				// error , using key word just can be at those can be access by derivered class
				// using CBook::m_pages; 

				using CBook::SetPages;
				using CBook::SayHello;



			};

			void test()
			{
				CYuwen yuwen;
				// yuwen.GetPages(); // error, we changed the access right
				//yuwen.SetPages( 20 );
				yuwen.SayHello();
				
			}
		}

	}
	namespace base_derivered_type_conversion
	{
		class CBook
		{
		public:
			void SayHello() const
			{
				std::cout << "CBook say hello ... " << std::endl;
			}
		};
		
		// public derivered
		class CYuwen : public CBook
		{

		};
		
		// private derivered
		class CLishi : private CBook
		{

		};
		class CDili : protected CBook
		{

		};

		void test()
		{
			
			std::cout << "// --------------------------------------" << std::endl;
			
			CBook book;			
			CBook &bookRef = book;
			book.SayHello();


			CYuwen yuwen;
			CBook *pBook_01 = &yuwen;
			CBook &bookRef_01 = yuwen;
			
			yuwen.SayHello();
			pBook_01->SayHello();
			bookRef_01.SayHello();


			CLishi lishi;
			// CBook *pBook_02 = &lishi;	// error, base class is private

			CDili dili;
			// CBook *pbook_03 = &dili;		// error, base class is protected
		}
	}
	namespace static_member_derivered
	{
		class CBook
		{
		public:
			int GetPages() const
			{
				//return m_pages;
				//return this->m_pages;
				return CBook::m_pages;
			}
		private:
			static int m_pages;
		};

		int CBook::m_pages = 100;

		class CYuwen : public CBook
		{

		};

		void test()
		{
			CYuwen yuwen;
			yuwen.GetPages();
			
			// int pages = CYuwen::m_pages; // error m_pages is inaccessble
		}

	}
	namespace avoid_derive
	{
		class CBook final
		{

		};
		// error, a final class is not allowed to be derivered
		//class CYuwen : public CBook
		//{};

		void test()
		{

		}
	}

	// virtual function
	namespace virtual_function
	{
		namespace scenario_virtual_destructor
		{
			class CBook
			{
			public:
				virtual ~CBook()
				{
					std::cout << "CBook destructor called ... " << std::endl;
				}
			private:
				int m_pages;
			};

			class CYuwen : public CBook
			{
			public:
				~CYuwen()
				{
					std::cout << "CYuwen destructor called .. " << std::endl;
				}
			private:

			};


			class CLowYuwen : public CYuwen
			{
			public:
				~CLowYuwen()
				{
					std::cout << "CLowYuwen destructor called ..." << std::endl;
				}
			};


			void test()
			{
				std::cout << "// ------------------------------------------" << std::endl;
				CBook *pBook = new CYuwen;
				delete pBook;
				pBook = nullptr;
				
				std::cout << std::endl << std::endl << "// ---------" << std::endl;
				pBook = new CLowYuwen;
				delete pBook;
			}

		}
		namespace scenario_pure_virtual_function
		{
			// pure virtual class if there any virtual function in it
			class CCreature
			{
			public:
				~CCreature() = default;

			public:
				virtual int Move() = 0;		// pure virtual function
				virtual int Speed() const
				{
					return 0;
				}
				virtual char* Speak()
				{
					return nullptr;
				}


			private:
				char*		m_charName;
			};

			class CPanda : public CCreature
			{
			public:
				int Move()
				{
					// walk 
					return 10;
				}
				int Speed() const final
				{
					return 20;
				}

				char* Speak() override
				{
					return "panda says : hello world !";
				}

			private:

			};


			void test()
			{
				
				std::cout << "// ---------------------------------------" << std::endl;
				
				// CCreature creature;		// error, abstract class
				CPanda panda;
				panda.Move();				
				panda.Speed();

				std::cout << panda.Speak() << std::endl;

			}
		}
		namespace scenario_test_virtual_function_01
		{
			enum EMove
			{
				Run = 0,
				Fly,
				Walk,
				Sweam,
				Crawl,
				Jump
			};

			class CCreature
			{
			public:
				virtual ~CCreature()
				{
					std::cout << "CCreature destructor called ... " << std::endl;
				}

			public:
				virtual int Move()
				{
					std::cout << __FUNCSIG__ << std::endl;
					return 0;
				}
				int Move( EMove _emove )	// 该函数并非虚函数
				{
					std::cout << __FUNCSIG__ << std::endl;
					return _emove;
				}

			};

			class CPanda : public CCreature
			{
			public:
				~CPanda()
				{
					std::cout << "CPanda destructor called ... " << std::endl;
				}

			public:
				int Move()
				{
					std::cout << "panda move ... " << std::endl;
					return 10;
				}
				int Move( EMove _emove )	// 该函数并非虚函数
				{
					std::cout << "panda enum move " << std::endl;
					return EMove::Fly;
				}

			};



			void test()
			{
				std::cout << "// ----------------------------------------" << std::endl;

				CCreature creature;
				creature.Move();
				creature.Move( EMove::Fly );


				std::cout << "// ----------------------------------------" << std::endl;

				CPanda panda;
				CCreature *pcc = &panda;
				pcc->Move();
				pcc->Move( EMove::Fly );

			}


		}
		namespace scenario_test_virtual_function_02
		{
			enum EMove
			{
				Run = 0,
				Fly,
				Walk,
				Sweam,
				Crawl,
				Jump
			};


			class CBook
			{
			public:
				~CBook() = default;
			private:

			};
			class CYuwen : public CBook
			{

			};



			class CCreature
			{
			public:
				virtual ~CCreature()
				{
					std::cout << "CCreature destructor called ... " << std::endl;
				}

			public:
				virtual int Move()
				{
					std::cout << __FUNCSIG__ << std::endl;
					return 0;
				}
				virtual int Move( EMove _emove )
				{
					std::cout << __FUNCSIG__ << std::endl;
					return _emove;
				}

			public:
				virtual CCreature* GetSelf()
				{
					std::cout << "CCreature GetSelf called ... " << std::endl;
					return this;
				}
				virtual CBook* ReadBook()
				{
					std::cout << "Creature ReadBook called ... " << std::endl;
					return nullptr;
				}


			};

			class CPanda : public CCreature
			{
			public:
				~CPanda()
				{
					std::cout << "CPanda destructor called ... " << std::endl;
				}

			public:
				int Move()
				{
					std::cout << "panda move ... " << std::endl;
					return 10;
				}
				/*
					覆盖虚函数，参数，返回值都必须一样.
					返回值有一个例外情况，
					当基类虚函数返回值是类的指针或引用类型，
					派生类覆盖的虚函数返回值可以是能转换成基类虚函数返回值类型的派生类
				*/
				int /*EMove*/ Move( EMove _emove )	
				{
					std::cout << "panda enum move " << std::endl;
					return EMove::Fly;
				}

			public:
				/*
					覆盖虚函数，参数，返回值都必须一样.
					返回值有一个例外情况，
					当基类虚函数返回值是类的指针或引用类型，
					派生类覆盖的虚函数返回值可以是能转换成基类虚函数返回值类型的派生类
				*/
				CPanda* GetSelf()
				{
					std::cout << "panda GetSelf called ... " << std::endl;
					return this;
				}
				CYuwen* ReadBook()
				{
					std::cout << "Panda ReadBook called ... " << std::endl;
					return nullptr;
				}


			};



			void test()
			{
				std::cout << "// ----------------------------------------" << std::endl;

				CCreature creature;
				creature.Move();
				creature.Move( EMove::Fly );


				std::cout << "// ----------------------------------------" << std::endl;

				CPanda panda;
				CCreature *pcc = &panda;
				pcc->Move();
				pcc->Move( EMove::Fly );



				std::cout << "// ----------------------------------------" << std::endl;
				pcc->GetSelf();
				pcc->ReadBook();


				std::cout << "// ----------------------------------------" << std::endl;

			}


		}
		namespace derivered_virtual_function_access_permission
		{
			// 被改写的虚函数的访问权限在派生类中可变动，不受影响

			class CBook
			{
			public:
				virtual void Name()
				{
					std::cout << "public virtual void CBook::Name() called ..." << std::endl;
				}
			};

			class CYuwen : public CBook
			{
			public:
				friend void test();
			public:
				CYuwen()
				{					
				}
			private:
				void Name()
				{
					std::cout << "void CYuwen::Name() called ..." << std::endl;
				}
			};			

			void test()
			{
				std::cout << "// ---------------------------------------------" << std::endl;
				CBook *pBook = new CYuwen;
				pBook->Name();


				std::cout << "// ---------------------------------------------" << std::endl;
			}
		}

	}
}
namespace mutiple_inheritance
{
	namespace mutiple_inheritance_definition
	{
		class CCreature
		{
		public:
			CCreature()
			{
				std::cout << "CCreature constructor called ... " << std::endl;
			}
			virtual ~CCreature()
			{
				std::cout << "CCreature destructor called ... " << std::endl;
			}
		};

		class CMovable
		{
		public:
			CMovable()
			{
				std::cout << "CMovale constructor called ... " << std::endl;
			}
			virtual ~CMovable()
			{
				std::cout << "CMovable destructor called ... " << std::endl;
			}
		};

		class CPanda : public CCreature, public CMovable
		{
		public:
			CPanda()
			{
				std::cout << "CPanda constructor called ... " << std::endl;
			}
			~CPanda()
			{
				std::cout << "CPanda destructor called ... " << std::endl;
			}

		public:


		};

		void test()
		{
			std::cout << " // ---------------------------------------------------" << std::endl;
			CPanda panda;
		}

	}
	namespace constructor_order
	{
		class CCreature
		{
		public:
			CCreature()
			{
				std::cout << "CCreature constructor called ... " << std::endl;
			}
			virtual ~CCreature()
			{
				std::cout << "CCreature destructor called ... " << std::endl;
			}
		};

		class CMovable
		{
		public:
			CMovable()
			{
				std::cout << "CMovale constructor called ... " << std::endl;
			}
			virtual ~CMovable()
			{
				std::cout << "CMovable destructor called ... " << std::endl;
			}
		};

		class CPanda : public CCreature, public CMovable
		{
		public:
			CPanda()
				:CMovable(), CCreature()
			{
				std::cout << "CPanda constructor called ... " << std::endl;
			}
			~CPanda()
			{
				std::cout << "CPanda destructor called ... " << std::endl;
			}

		public:


		};

		void test()
		{
			std::cout << " // ---------------------------------------------------" << std::endl;
			CPanda panda;
		}

	}
	namespace type_convert
	{
		class CCreature
		{
		public:
			CCreature()
			{
				std::cout << "CCreature constructor called ... " << std::endl;
			}
			virtual ~CCreature()
			{
				std::cout << "CCreature destructor called ... " << std::endl;
			}

		public:
			void ReportAddress() const
			{
				std::cout << "CCreature::this :  " << this << std::endl
					<< "CCreature::m_ages address :  " << &m_ages << std::endl;
			}

		private:
			int m_ages;
		};

		class CMovable
		{
		public:
			CMovable()
			{
				std::cout << "CMovale constructor called ... " << std::endl;
			}
			virtual ~CMovable()
			{
				std::cout << "CMovable destructor called ... " << std::endl;
			}

		public:
			void ReportAddress() const
			{
				std::cout << "CMovable::this :  " << this << std::endl
					<< "CMovable::m_bMove address :  " << &m_bMove << std::endl;
			}

		private:
			bool m_bMove = true;
		};

		class CPanda : public CCreature, public CMovable
		{
		public:
			CPanda()
			{
				std::cout << "CPanda constructor called ... " << std::endl;
			}
			~CPanda()
			{
				std::cout << "CPanda destructor called ... " << std::endl;
			}

		public:
			void ReportAddress() const
			{
				std::cout << "CPanda::this :  " << this << std::endl
					<< "CPanda::m_yell address :  " << &m_yell << std::endl;
			}

		private:
			bool m_yell = true;

		};

		void test()
		{
			std::cout << " // ---------------------------------------------------" << std::endl;
			CPanda panda;

			CCreature *pct = &panda;
			CMovable *pm = &panda;

			int first = 1;
			int second = 2;

			std::cout << "panda address : " << &panda << std::endl
				<< "creature pct address : " << pct << std::endl
				<< "movale pm address : " << pm << std::endl;

			std::cout << "size of panda : " << sizeof( panda ) << std::endl;
			
			std::cout << " // ---------------------------------------------------" << std::endl;
			panda.ReportAddress();
			pct->ReportAddress();
			pm->ReportAddress();




			std::cout << " // ---------------------------------------------------" << std::endl;

			int *pf = &first;
			int *ps = &second;

			std::cout << "first address pf :  " << pf << std::endl
				<< "size of first :  " << sizeof( first ) << std::endl
				<< "second address ps :  " << ps << std::endl
				<< "sizeof second :  " << sizeof( second ) << std::endl;


			std::cout << " // ---------------------------------------------------" << std::endl;
		}

	}
	namespace ambiguous
	{
		namespace scenario_mutiple_ambiguous
		{
			class CCreature
			{
			public:
				CCreature()
				{
					std::cout << "CCreature constructor called ... " << std::endl;
				}
				virtual ~CCreature()
				{
					std::cout << "CCreature destructor called ... " << std::endl;
				}

			public:
				void Report() const
				{
					std::cout << "CCreature Report ... " << std::endl;
				}
				void SayHi() const
				{
					std::cout << "CCreature SayHi ... " << std::endl;
				}
			};

			class CMovable
			{
			public:
				CMovable()
				{
					std::cout << "CMovale constructor called ... " << std::endl;
				}
				virtual ~CMovable()
				{
					std::cout << "CMovable destructor called ... " << std::endl;
				}

			public:
				void Report() const
				{
					std::cout << "CMovable Report ... " << std::endl;
				}
				void SayHi( int _i ) const
				{
					++_i;
					std::cout << "CMoveable SayHi ... " << std::endl;
				}
			};

			class CPanda : public CCreature, public CMovable
			{
			public:
				CPanda()
				{
					std::cout << "CPanda constructor called ... " << std::endl;
				}
				~CPanda()
				{
					std::cout << "CPanda destructor called ... " << std::endl;
				}

			public:


			};

			void test()
			{
				std::cout << " // ---------------------------------------------------" << std::endl;
				CPanda panda;

				std::cout << " // ---------------------------------------------------" << std::endl;

				// 二义性，须 使用 作用域运算符
				panda.CCreature::Report();	//
				panda.CMovable::SayHi( 3 );


				std::cout << " // ---------------------------------------------------" << std::endl;
			}

		}
		namespace scenario_advanced_level_ambiguous
		{
			class CCreature
			{
			public:
				CCreature()
				{
					std::cout << "CCreature constructor called ... " << std::endl;
				}
				virtual ~CCreature()
				{
					std::cout << "CCreature destructor called ... " << std::endl;
				}

			public:
				void Report() const
				{
					std::cout << "CCreature Report ... " << std::endl;
				}

			};
			class CBear : public CCreature
			{
			public:

			public:
				void Report() const
				{
					std::cout << "CBear Report ... " << std::endl;
				}
				
			private:

			};


			class CMovable
			{
			public:
				CMovable()
				{
					std::cout << "CMovale constructor called ... " << std::endl;
				}
				virtual ~CMovable()
				{
					std::cout << "CMovable destructor called ... " << std::endl;
				}

			public:
				void SayHi() const
				{
					std::cout << "CMovable SayHi ... " << std::endl;
				}

			};




			class CPanda : public CBear, public CMovable
			{
			public:
				CPanda()
				{
					std::cout << "CPanda constructor called ... " << std::endl;
				}
				~CPanda()
				{
					std::cout << "CPanda destructor called ... " << std::endl;
				}

			public:
			};

			void test()
			{
				std::cout << " // ---------------------------------------------------" << std::endl;
				CPanda panda;

				std::cout << " // ---------------------------------------------------" << std::endl;

				// 二义性，但是直接基类有优先级
				panda.Report();				

				std::cout << " // ---------------------------------------------------" << std::endl;
			}
		}

	}

	namespace share_virtual_base
	{
		namespace two_base_example
		{

			class CCreature
			{
			public:
				virtual ~CCreature()
				{

				}

			public:
				bool Move()
				{
					std::cout << "CCreature Move called ... " << std::endl;
					return false;
				}
			};
			class CLandCreature : public CCreature
			{

			};
			class CWaterCreature : public CCreature
			{

			};

			class CAmphibian : public CLandCreature, public CWaterCreature
			{

			};

			void test()
			{
				std::cout << "// ---------------------------------------------------" << std::endl;
				CAmphibian qw;
				//	qw.Move();	// error, ambiguous
				qw.CLandCreature::Move();

				std::cout << "sizeof CAmphibian :  " << sizeof( qw ) << std::endl;
			}

		}
		namespace virtual_derivered
		{

			class CCreature
			{
			public:
				virtual ~CCreature()
				{

				}

			public:
				bool Move()
				{
					std::cout << "CCreature Move called ... " << std::endl;
					return false;
				}
			};
			class CLandCreature : virtual public CCreature
			{

			};
			class CWaterCreature : public virtual CCreature
			{

			};

			class CAmphibian : public CLandCreature, public CWaterCreature
			{

			};

			void test()
			{
				std::cout << "// ---------------------------------------------------" << std::endl;
				CAmphibian qw;
				qw.Move();	// virtual derivered, code ok
				qw.CLandCreature::Move();


				std::cout << "sizeof CAmphibian :  " << sizeof( qw ) << std::endl;
			}
		}
		namespace virtual_base_constructor_order
		{
			class CCreature
			{
			public:
				CCreature()
				{
					std::cout << "CCreature constructor called ... " << std::endl;
				}
				virtual ~CCreature()
				{

				}

			public:
				bool Move()
				{
					std::cout << "CCreature Move called ... " << std::endl;
					return false;
				}
			};
			class CLandCreature : virtual public CCreature
			{
			public:
				CLandCreature()
					:CCreature()
				{
					std::cout << "CLandCreature constructor called ... " << std::endl;
				}
			};
			class CWaterCreature : public virtual CCreature
			{
			public:
				CWaterCreature()
					:CCreature()
				{
					std::cout << "CWaterCreature constructor called ... " << std::endl;
				}
			};

			class CAmphibian : public CLandCreature, public CWaterCreature
			{
			public:
				CAmphibian()
					:CCreature(), // virtual base constructor must be called in the last derivered class
					CLandCreature(), CWaterCreature()
				{
					std::cout << "CAmphibian constructor called ... " << std::endl;
				}
			};

			void test()
			{
				std::cout << "// ---------------------------------------------------" << std::endl;
				CAmphibian qw;

			}
		}

	}
}



namespace test_RTTI
{
	namespace test_dynamic_cast
	{
		namespace scenario_has_virtual_function
		{
			class CCreature
			{
			public:
				CCreature()
				{
					std::cout << "CCreature constructor called ... " << std::endl;
				}
				virtual ~CCreature()
				{

				}

			public:
				virtual bool Move()
				{
					std::cout << "CCreature Move called ... " << std::endl;
					return false;
				}
			};

			class CLandCreature : virtual public CCreature
			{
			public:
				CLandCreature()
					:CCreature()
				{
					std::cout << "CLandCreature constructor called ... " << std::endl;
				}
			public:
				bool Move() override
				{
					std::cout << "CLandCreature Move called ... " << std::endl;
					return false;
				}
			};

			class CWaterCreature : public virtual CCreature
			{
			public:
				CWaterCreature()
					:CCreature()
				{
					std::cout << "CWaterCreature constructor called ... " << std::endl;
				}
			public:
				bool Move() override
				{
					std::cout << "CWaterCreature Move called ... " << std::endl;
					return false;
				}
			};


			class CAmphibian : public CLandCreature, public CWaterCreature
			{
			public:
				CAmphibian()
					:CCreature(), // virtual base constructor must be called in the last derivered class
					CLandCreature(), CWaterCreature()
				{
					std::cout << "CAmphibian constructor called ... " << std::endl;
				}

			public:
				// 如果不提供 自定义版本的 Move覆盖， 则会报错ambiguous
				bool Move() override
				{
					std::cout << "CAmphibian Move called ... " << std::endl;
					return false;
				}

			};

			void test()
			{
				std::cout << "// ---------------------------------------------------" << std::endl;
				CCreature *pct = new CAmphibian;
				CLandCreature *plct = dynamic_cast<CLandCreature*>( pct );
				CWaterCreature *pwct = dynamic_cast<CWaterCreature*>( pct );

				pct->Move();
				plct->Move();
				pwct->Move();


				CCreature *pct_01 = dynamic_cast<CCreature*>( pwct );

			}
		}
		namespace scenario_no_virtual_function
		{
			class CBook
			{

			};
			class CYuwen : public CBook
			{
			public:
				virtual ~CYuwen() = default;
			};


			void test()
			{
				std::cout << "// -----------------------------------" << std::endl;
				
				CBook *pbook = new CYuwen;
				// CYuwen *pyw = dynamic_cast<CYuwen*>( pbook );	// error, 基类无虚函数
				

			}
		}
	}
	namespace test_typeid
	{
		namespace scenario_has_virtual_function
		{
			class CBook
			{

			};
			class CYuwen : public CBook
			{
			public:
				virtual ~CYuwen() = default;
			};


			void test()
			{
				std::cout << "// -----------------------------------" << std::endl;

				CBook *pbook = new CYuwen;
				std::cout << "typeid( *pbook ) :  " << typeid( *pbook ).name() << std::endl;

			}
		}

		namespace scenario_no_virtual_function
		{
			class CBook
			{
			public:
				virtual ~CBook() = default;
			};
			class CYuwen : public CBook
			{
			public:
				virtual ~CYuwen() = default;
			};


			void test()
			{
				std::cout << "// -----------------------------------" << std::endl;


				// 基类必须要有 虚函数 才能识别出来，否则识别的是 静态类型
				CBook *pbook = new CYuwen;
				std::cout << "typeid( *pbook ) :  " << typeid( *pbook ).name() << std::endl;

			}
		}
	}

	
}


void CTestor::Test()
{
	{
		using namespace test_derivered;
		derivered_definition::test();
		derivered_construct::test();
		derivered_base_construct::test();
		derivered_change_access::scenario_common::test();
		derivered_change_access::scenario_changed::test();
		base_derivered_type_conversion::test();
		static_member_derivered::test();
		avoid_derive::test();
		virtual_function::scenario_virtual_destructor::test();
		virtual_function::scenario_pure_virtual_function::test();
		virtual_function::scenario_test_virtual_function_01::test();
		virtual_function::scenario_test_virtual_function_02::test();
		virtual_function::derivered_virtual_function_access_permission::test();
	}
	{
		using namespace mutiple_inheritance;
		mutiple_inheritance_definition::test();
		constructor_order::test();
		type_convert::test();
		ambiguous::scenario_mutiple_ambiguous::test();
		ambiguous::scenario_advanced_level_ambiguous::test();

		share_virtual_base::two_base_example::test();
		share_virtual_base::virtual_derivered::test();
		share_virtual_base::virtual_base_constructor_order::test();
	}

	{
		using namespace test_RTTI;
		test_dynamic_cast::scenario_has_virtual_function::test();
		test_dynamic_cast::scenario_no_virtual_function::test();
		test_typeid::scenario_has_virtual_function::test();
		test_typeid::scenario_no_virtual_function::test();
	}
}