#include<vector>
#include<iostream>
#include<cstring>
#include<algorithm>
#include<stack>
using namespace std;
#define maxn 140

struct exchange_point
{
    int a, b;
    double rate, cost;
    exchange_point(int a, int b, double rate, double cost) : a(a), b(b), rate(rate), cost(cost) {}
    exchange_point() {}
} currencies[maxn << 2];
double dist[maxn];
int cnt = 0;
int n, m, s;
double v;

void get_data(int m)
{
    int _a, _b;
    double _rate, _cost;
    for (int i = 0; i < m; ++i)
    {
        cin >> _a >> _b;
        cin >> _rate >> _cost;
        currencies[cnt++] = exchange_point(_a, _b, _rate, _cost);
        cin >> _rate >> _cost;
        currencies[cnt++] = exchange_point(_b, _a, _rate, _cost);
    }
    return;
}

bool BallmanFord()
{
    memset(dist, 0, sizeof(dist));
    dist[s] = v;
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < cnt; ++j)
        {
            int a = currencies[j].a, b = currencies[j].b;
            double rate = currencies[j].rate;
            double cost = currencies[j].cost;
            dist[b] = max(dist[b], (dist[a] - cost) * rate);
            if (dist[s] > v)
                return true;
        }
    }
    for (int i = 0; i < cnt; ++i)
    {
        int a = currencies[i].a, b = currencies[i].b;
        double rate = currencies[i].rate;
        double cost = currencies[i].cost;
        if (dist[b] < (dist[a] - cost)*rate)
            return true;
    }
    return false;
}

int main()
{
    cin >> n >> m >> s >> v;
    get_data(m);
    if (BallmanFord())
        cout << "YES" << endl;
    else
        cout << "NO" << endl;
}