#include<iostream>
#include<cmath>
using namespace std;
//ֱ��ģ��
int main()
{
	int R, M, Y;
	cin >> R >> M >> Y;
	cout << (int)(M * pow(1 + R / 100.0, Y)) << endl;
	return 0;
}