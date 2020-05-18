/// Just casual FFT for mutiplying two polynomials using complex numbers

#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("avx,avx2,fma")

#define fi first
#define se second
#define ll long long
#define ld long double
#define all(x)              (x).begin(), (x).end()
#define inf                 1e18

#define re real()
#define im imag()

using namespace std;
using namespace __gnu_pbds;

template <typename T>
using ordered_set = tree <T, null_type, less <T>, rb_tree_tag, tree_order_statistics_node_update>;

typedef complex <double> cd;
const double pi = 3.14159265358979323846264338327950;

inline cd operator + (const cd &a, const cd &b) { return cd(a.re + b.re, a.im + b.im); }
inline cd operator - (const cd &a, const cd &b) { return cd(a.re - b.re, a.im - b.im); }
inline cd operator * (const cd &a, const cd &b) { return cd(a.re * b.re - a.im * b.im, a.re * b.im + a.im * b.re); }
inline cd operator / (const cd &a, const ld &b) { return cd(a.re / b, a.im / b); }

void fft(vector <cd> &ar) {
        int n = ar.size();
        if (n == 1) return;

        vector <cd> w(n); w[0] = 1;
        for (int i = 1; i < n; ++i) {
                double a = 2 * pi * i / (double)n;
                w[i] = cd(cos(a), sin(a));
        }
        auto rv = [&](int x, int k) {
                ll res = 0;
                for (int i = 0; i < k; ++i) {
                        if (x & (1 << i)) {
                                res += (1LL << (k - i - 1));
                        }
                }
                return res;
        };

        int lg = 0;
        while ((1 << lg) < n) ++lg;

        for (int i = 0; i < n; ++i) {
                int j = rv(i, lg);
                if (i < j) swap(ar[i], ar[j]);
        }

        for (int len = 2; len <= n; len <<= 1) {
                int step = n / len;
                for (int i = 0; i < n; i += len) {
                        for (int j = 0; j < len / 2; ++j) {
                                cd a = ar[i + j], b = w[j * step] * ar[i + j + (len / 2)];
                                ar[i + j] = a + b;
                                ar[i + j + (len / 2)] = a - b;
                        }
                }
        }
}

void inv_fft(vector <cd> &ar) {
        int n = ar.size(); fft(ar);

        for (auto &i : ar) i /= n;
        reverse(ar.begin() + 1, ar.end());
}

inline ll get(ll a) {
        if (!(a & (a - 1)) || a == 1) return a;
        return (1LL << (64 - __builtin_clzll(a - 1)));
}


void mult(vector <cd> &a, vector <cd> b) {
        for (int i = 0; i < a.size(); ++i) a[i] = bool(int(a[i].real() + 0.5));
        for (int j = 0; j < b.size(); ++j) b[j] = bool(int(b[j].real() + 0.5));

        ll sz = 2 * max(get(a.size()), get(b.size()));
        while (a.size() < sz) a.push_back(0);
        while (b.size() < sz) b.push_back(0);

        fft(a); fft(b);
        for (int i = 0; i < a.size(); ++i) a[i] *= b[i];

        inv_fft(a);
}

vector <cd> bp(vector <cd> &ar, ll n) {
        vector <cd> res(ar.size()); res[0] = 1;
        while (n) {
                if (n & 1) mult(res, ar);
                mult(ar, ar);
                n >>= 1;
        }
        return res;
}

int cnt[1001];

void solve() {
        int n, k;
        cin >> n >> k;

        ll mx = 0;
        for (int i = 0; i < n; ++i) {
                int x;
                cin >> x; ++cnt[x]; mx = max(mx, 1LL * x);
        }
        vector <cd> ar(mx + 1);
        for (int i = 0; i <= mx; ++i) {
                ar[i] = !!cnt[i];
        }

        ar = bp(ar, k);
        for (int i = 0; i < ar.size(); ++i) {
                if ((ll)round(ar[i].real()) > 0) {
                        cout << i << " ";
                }
        }
}

int main() {
        ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
//      freopen("input.txt", "r", stdin);
//      freopen("output.txt", "w", stdout);
        int q = 1; // cin >> q;
        while (q--) {
                solve();
        }
}
