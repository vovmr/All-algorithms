#include <bits/stdc++.h>
#define ll long long
#define ld long double
#define all(x)              (x).begin(), (x).end()
#define inf                 1e18
#define PI                  -2 * atan2(-1, 0)

using namespace std;

typedef complex <double> cd;

ll rev(ll a, int n) {
    deque <int> bin;
    while (a) {
        bin.push_front(a % 2);
        a >>= 1;
    }
    while (bin.size() < n) {
        bin.push_front(0);
    }
    reverse(all(bin));
    ll res = 0;
    for (int i = 0; i < n; ++i) {
        res += bin[i] * (1LL << (n - i - 1));
    }
    return res;
}

vector <cd> fft_by_vovamr(vector <int> &ar) {
    int n = (int)ar.size();
    vector <cd> v(n), w(n, 1);
    for (int i = 1; i < n; ++i) {
        double a = 2.0 * PI * i / (double)n;
        w[i] = cd(cos(a), sin(a));
    }
    int lg = 1;
    while ((1LL << lg) < n) {
        ++lg;
    }
    for (int i = 0; i < n; ++i) {
        v[i] = rev(i, lg);
        v[i] = ar[(int)v[i].real()];
    }
    for (int len = 2; len <= n; len <<= 1) {
        double a = 2.0 * PI / (double)len;
        cd cur = cd(cos(a), sin(a));
        for (int i = 0; i < n; i += len) {
            cd now = 1;
            for (int j = 0; j < (len >> 1); ++j) {
                cd a = v[i + j], b = v[i + j + (len >> 1)] * now;
                v[i + j] = a + b;
                v[i + j + (len >> 1)] = a - b;
                now *= cur;
            }
        }
    }
    return v;
}

int main() {
    ios_base::sync_with_stdio(false);
//    ifstream cin("input.txt");
//    ofstream cout("output.txt");
    int n;
    cin >> n;
    vector <int> ar(n);
    for (int i = 0; i < n; ++i) {
        int x;
        cin >> x;
        ar[i] = x;
    }
    vector <cd> ar1 = fft_by_vovamr(ar);
    cout << "Compare with mine: " << endl;
    for (auto i : ar1) {
        cout << i.real() << ((i.imag() < 0) ? " - " : " + ") << abs(i.imag()) << "i" << endl;
    }
}
