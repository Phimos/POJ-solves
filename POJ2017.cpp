#include<iostream>
#include<algorithm>
#include<string>
using namespace std;

int main()
{
	int n;
	while (cin >> n && n != -1)
	{
		int speed, apparent_hour, hours = 0, miles = 0;
		while (n--)
		{
			cin >> speed >> apparent_hour;
			miles += speed * (apparent_hour - hours);
			hours = apparent_hour;
		}
		cout << miles << "miles" << endl;
	}
	return 0;
}