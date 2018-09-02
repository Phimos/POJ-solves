#include<iostream>
using namespace std;

int main()
{
	int N, M, P, C;
	while (cin >> N >> M >> P >> C && N&&M&&P&&C)
		cout << P - M + N << endl;
	return 0;
}