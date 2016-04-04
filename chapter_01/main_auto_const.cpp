#include <iostream>
using namespace std;


int main()
{
	// two diffent  forms
	const int i = -1;
	int const e = 1;

	const int &iref = i;
	int const &eref = e;

	int const &cref = 3;

	auto ai = iref; // ai will ignore the ref property, therefore ai is just int type
	ai = 5; // auto ai  lost the const property

	auto ai_01 = i;
	ai_01 = 5;

	const auto ai_01 = eref;


	auto &airef = iref; // airef is const ref type, "airef = 5;" will be wrong
	// airef = 5;   // airef has the const property

	auto const &acref = 5;  // const auto ref
	


	return 0;
}