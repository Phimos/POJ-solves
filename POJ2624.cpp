#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
double coord[4][2];

class CVector {
public:
	double x, y;
	CVector(double x, double y) : x(x), y(y) {}
	CVector() {}
};

CVector operator +(CVector p, CVector q) {
	return CVector(p.x + q.x, p.y + q.y);
}

CVector operator -(CVector p, CVector q) {
	return CVector(p.x - q.x, p.y - q.y);
}

int main()
{
	while (cin >> coord[0][0] >> coord[0][1] >> coord[1][0] >> coord[1][1] >> coord[2][0] >> coord[2][1] >> coord[3][0] >> coord[3][1])
	{
		int i, j;
		for (i = 0; i <= 1; ++i)
			for (j = 2; j <= 3; ++j)
				if (coord[i][0] == coord[j][0] && coord[i][1] == coord[j][1])
					goto OUT;
OUT:
		CVector temp = CVector(coord[i][0], coord[i][1]) + CVector(coord[i ^ 1][0] - coord[i][0], coord[i ^ 1][1] - coord[i][1]) + CVector(coord[j ^ 1][0] - coord[j][0], coord[j ^ 1][1] - coord[j][1]);
		printf("%.3lf %.3lf\n", temp.x, temp.y);
	}
}