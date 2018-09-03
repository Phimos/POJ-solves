#include<iostream>
#include<algorithm>
#include<string>
using namespace std;
//my_gcd为求最大公因数
//注意可能运算完后为整数
int my_gcd(int a, int b)
{
	while (a % b)
	{
		a %= b;
		swap(a, b);
	}
	return b;
}
int main()
{
	string equation;
	while(cin>>equation)
	{
		int a = equation[0] - '0', b = equation[2] - '0', c = equation[4] - '0', d = equation[6] - '0';
		char op = equation[3];
		int numerator, denominator;
		denominator = b * d;
		if (op == '+')
			numerator = a * d + c * b;
		else
			numerator = a * d - c * b;
		int gcd = my_gcd(abs(numerator), denominator);
		if (numerator%denominator == 0)
			cout << numerator / denominator << endl;
		else
			cout << numerator / gcd << '/' << denominator / gcd << endl;
	}
	return 0;
}