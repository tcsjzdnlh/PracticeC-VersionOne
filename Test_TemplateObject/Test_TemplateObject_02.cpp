#include <iostream> 
#include <cstdlib>
using namespace std;
class Sample
{
private:
	int counter;
public:
	Sample( int c = 0 )
	{
		counter = c;
	}

	Sample operator=( Sample& a )
	{
		counter = a.counter;
		return Sample( counter );
	}

	~Sample()
	{
		cout << "!" << endl;
	}
};
int main()
{

	Sample obj2, obj3;

	cout << "Q" << endl;
	obj2 = obj3;
	cout << "J" << endl;

	system( "PAUSE" );

	return 0;
}