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
    if (n == 1)
        return vector <cd> (1, ar[0]);
    vector <cd> w(n);
    for (int i = 0; i < n; ++i)
    {
        double a = 2.0 * PI * i / (n * 1.0);
        w[i] = cd(cos(a), sin(a));
    }
    vector <cd> a(n >> 1), b(n >> 1);
    for (int i = 0; i < (n >> 1); ++i)
    {
        a[i] = ar[2 * i];
        b[i] = ar[2 * i + 1];
    }
    a = fft(a), b = fft(b);
    vector <cd> res(n);
    for (int i = 0; i < n; ++i)
    {
        res[i] = a[i % (n >> 1)] + w[i] * b[i % (n >> 1)];
    }
    return res;
}

vector <cd> fft_rev(vector <cd> &ar)
{
    int n = ar.size();
    ar = fft(ar);
    for (int i = 0; i < n; ++i)
    {
        ar[i] /= n;
    }
    reverse(ar.begin() + 1, ar.end());
    return ar;
}

int main()
{
    ios_base::sync_with_stdio(false);
//    ifstream cin("input.txt");
//    ofstream cout("output.txt");
    int n;
    cin >> n;
    vector <cd> a(2 * n), b(2 * n);
    for (int i = 0; i < n; ++i)
    {
        int x, y;
        cin >> x >> y;
        a[i] = x; b[i] = y;
    }
    a = fft(a), b = fft(b);
    vector <cd> res(2 * n);
    for (int i = 0; i < 2 * n; ++i)
    {
        res[i] = a[i] * b[i];
    }
    res = fft_rev(res);
    for (auto i : res)
    {
        cout << ((i.real() <= 0.0001) ? 0 : i.real()) << " ";
    }
}
