#include <bits/stdc++.h>
#define ll long long
#define ld long double
#define all(x)              (x).begin(), (x).end()
#define inf                 1e18
#define PI                  -2 * atan2(-1, 0)

using namespace std;

typedef complex <double> cd;

vector <cd> fft(vector <cd> &ar)
{
    int n = ar.size();
    vector <cd> w(n, 1);
    for (int i = 1; i < n; ++i)
    {
        double a = 2.0 * PI * i / (double)n;
        w[i] = cd(cos(a), sin(a));
    }
    for (int i = 1, j = 0; i < n; ++i)
    {
		int bit = n >> 1;
		for (; j >= bit; bit >>= 1)
			j -= bit;
		j += bit;
		if (i < j)
			swap(ar[i], ar[j]);
	}
    for (int len = 2; len <= n; len <<= 1)
    {
        for (int i = 0; i < n; i += len)
        {
            for (int j = 0; j < (len >> 1); ++j)
            {
                cd a = ar[i + j], b = w[j] * ar[i + j + (len >> 1)];
                ar[i + j] = a + b;
                ar[i + j + (len >> 1)] = a - b;
            }
        }
    }
    return ar;
}

vector <cd> inv_fft(vector <cd> &ar)
{
    vector <cd> res = fft(ar);
    for (auto &i : res)
        i /= (double)ar.size();
    reverse(res.begin() + 1, res.end());
    return res;
}

int main()
{
    ios_base::sync_with_stdio(false);
//    ifstream cin("shelf.in");
//    ofstream cout("shelf.out");
    int n = 1e5;
//    cin >> n;
    vector <cd> a(n), b(n);
    for (int i = 0; i < n; ++i)
    {
        int x;
        x = 1 + rand() % 10;
//        cin >> x;
        a[i] = x;
    }
    for (int i = 0; i < n; ++i)
    {
        int x;
        x = 1 + rand() % 10;
//        cin >> x;
        b[i] = x;
    }
    while ((a.size() & (a.size() - 1)))
    {
        a.push_back(0);
        b.push_back(0);
        ++n;
    }
    n *= 2;
    while (a.size() < n)
    {
        a.push_back(0);
        b.push_back(0);
    }
    a = fft(a), b = fft(b);
    vector <cd> res(n);
    for (int i = 0; i < n; ++i)
        res[i] = a[i] * b[i];
    res = inv_fft(res);
//    for (int i = 0; i < n; ++i)
//    {
//        cout << round(res[i].real());
//    }
    cout << clock() / 1000.0;
}
