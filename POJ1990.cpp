#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
//树状数组，先对v排序，不用考虑max
//结果需要用long long来存
#define maxn 20010
int n;
long long xmax = 0;

struct Cow
{
	long long v, x;
	bool operator<(const Cow& b)const
	{
		return v < b.v;
	}
} cows[maxn];

int lowbit(int x)
{
	return x & (-x);
}

long long xarr[maxn], numarr[maxn];

void update(long long arr[], long long k, long long inc)
{
	for (int i = k; i <= xmax; i += lowbit(i))
		arr[i] += inc;
}

long long getSum(long long arr[], long long k)
{
	long long ans = 0;
	for (int i = k; i > 0; i -= lowbit(i))
		ans += arr[i];
	return ans;
}

int main()
{
	scanf("%d", &n);
	for (int i = 0; i < n; ++i)
	{
		scanf("%lld%lld", &cows[i].v, &cows[i].x);
		xmax = max(xmax, cows[i].x);
	}
	sort(cows, cows + n);
	long long ans = 0, xSum = 0;
	for (int i = 0; i < n; ++i)
	{
		//ans+=cows[i].v*((xSum-getSum(xarr,cows[i].x))-cows[i].x*(i-getSum(numarr,cows[i].x))+cows[i].x*getSum(numarr,cows[i].x)-getSum(xarr,cows[i].x))
		ans += cows[i].v * (xSum - 2 * getSum(xarr, cows[i].x) + cows[i].x * (2 * getSum(numarr, cows[i].x) - i));	//此处为化简
		update(xarr, cows[i].x, cows[i].x);
		update(numarr, cows[i].x, 1);
		xSum += cows[i].x;
	}
	printf("%lld\n", ans);
}