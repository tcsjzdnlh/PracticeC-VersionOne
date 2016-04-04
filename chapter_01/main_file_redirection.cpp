#include <iostream>

using namespace std;

int main()
{
	int nVal = 0;
	while( cin >> nVal )
	{
		if( 6 == nVal )
		{
			cout << "condition of exit process is ocur"<<endl;
			break;
		}
		cout<<endl<<"current value is: "<<nVal<<endl;
	}
	return 0;
}