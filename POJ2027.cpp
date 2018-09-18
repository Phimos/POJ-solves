#include<iostream>
using namespace std;
#define Pi 3.1415926

int main()
{
	double r;
	int N;
	cin >> N;
	for (int i = 1; i <= N; ++i)
	{
		int year;
		double x,y;
		cin >> x >> y;
		year=ceil((x*x+y*y)*Pi / 100);
		cout << "Property " << i << ": This proerty will begin eroding in year " << year << "." << endl;
	}
	cout << "END OF OUTPUT." << endl;
	return 0;
}