#include<iostream>
#include<algorithm>
using namespace std;
#define maxn 24
#define EPS 1e-6
//计算几何  线段相交
struct Point
{
	double x, y;
	Point(double x, double y): x(x), y(y) {}
	Point() {}
};

struct Line
{
	Point a, b;
	Line(Point a, Point b): a(a), b(b) {}
	Line() {}
	bool operator^(Line other)
	{
		double x1 = b.x - a.x;
		double y1 = b.y - a.y;
		double x2 = other.b.x - other.a.x;
		double y2 = other.b.y - other.a.y;
		return x1 * y2 - x2 * y1;
	}
};

Point upper[maxn], bottom[maxn];
int n;
double maxx;

int leftside(const Point& a, const Point& b, const Point& p)
{
	double ans = Line(a, b)^Line(a, p);
	if ( ans > EPS)
		return 1;
	else if (ans < -EPS)
		return -1;
	else
		return 0;
}

double getx(Line l1, Line l2)
{
	double x1 = l1.a.x, x2 = l1.b.x, y1 = l1.a.y, y2 = l1.b.y;
	double x3 = l2.a.x, x4 = l2.b.x, y3 = l2.a.y, y4 = l2.b.y;
	double x;
	double temp1 = x1 * (y2 - y1) - y1 * (x2 - x1);
	double temp2 = x3 * (y4 - y3) - y3 * (x4 - x3);
	x = (temp1 * (x4 - x3) - temp2 * (x2 - x1)) / ((y2 - y1) * (x4 - x3) - (y4 - y3) * (x2 - x1));
	return x;
}

bool check(Line t)
{
	for (int i = 0; i < n; ++i)
	{
		if (leftside(t.a, t.b, upper[i])*leftside(t.a, t.b, bottom[i]) == 1)
		{
			if (t.a.x > t.b.x)
				swap(t.a, t.b);
			if (leftside(t.a, t.b, upper[i]) == 1)
			{
				maxx = max(maxx, getx(t, Line(bottom[i - 1], bottom[i])));
			}
			else//-1
			{
				maxx = max(maxx, getx(t, Line(upper[i - 1], upper[i])));
			}
			return false;
		}
	}
	return true;
}

int main()
{
	while (cin >> n, n)
	{
		for (int i = 0; i < n; ++i)
		{
			cin >> upper[i].x >> upper[i].y;
			bottom[i].x = upper[i].x;
			bottom[i].y = upper[i].y - 1;
		}

		for (int i = 0; i < n; ++i)
		{
			for (int j = 0; j < n; ++j)
			{
				if (i == j)
					continue;
				Line temp(upper[i], bottom[j]);
				if (check(temp))
					cout << "Through all the pipe." << endl;
			}
		}
		cout << maxx << endl;
	}
}