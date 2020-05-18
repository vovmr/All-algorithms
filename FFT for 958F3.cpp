/// Just FFT with modulo
/// We can calculate complex FFT and then round each coefficient and take it modulo p
/// Because the maximal coefficient can be only 2n * p^2 (which fits in long long)

#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
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

const ll mod = 1009;

typedef complex <double> cd;
const double pi = 3.141592653589793223846264338327950;

inline cd operator + (const cd &a, const cd &b) { return cd(a.re + b.re, a.im + b.im); }
inline cd operator - (const cd &a, const cd &b) { return cd(a.re - b.re, a.im - b.im); }
inline cd operator * (const cd &a, const cd &b) { return cd(a.re * b.re - a.im * b.im, a.re * b.im + a.im * b.re); }
inline cd operator / (const cd &a, const ld &b) { return cd(a.re / b, a.im / b); }

inline void fft(vector <cd> &ar, bool inv) {
        int n = ar.size();
        if (n <= 1) return;

        vector <cd> w(n); w[0] = 1;
        for (int i = 1; i < n; ++i) {
                double a = 2.0 * ((inv) ? -1.0 : 1.0) * pi * i / (double)n;
                w[i] = cd(cos(a), sin(a));
        }
        for (int i = 1, j = 0; i < n; i++) {
                int bit = n >> 1;
                for (; j & bit; bit >>= 1)
                        j ^= bit;
                j ^= bit;
                if (i < j) swap(ar[i], ar[j]);
        }
        for (int len = 2; len <= n; len <<= 1) {
                int step = n / len;
                for (int i = 0; i < n; i += len) {
                        for (int j = 0; j < len / 2; ++j) {
                                cd a = ar[i + j], b = ar[i + j + (len / 2)] * w[j * step];
                                ar[i + j] = a + b;
                                ar[i + j + (len / 2)] = a - b;
                        }
                }
        }
        if (inv) {
                for (auto &i : ar) i /= n;
        }
}

int cnt[(int)2e5 + 3];

void solve() {

        int n, m, k;
        cin >> n >> m >> k;
        for (int i = 0; i < n; ++i) {
                int x;
                cin >> x; --x; ++cnt[x];
        }
        multiset < vector <ll> > st;
        for (int i = 0; i < m; ++i) {
                if (cnt[i]) {
                        vector <ll> v(cnt[i] + 1, 1);
                        st.insert(v);
                }
        }

        while (st.size() > 1) {
                auto a = *st.begin(); st.erase(st.begin());
                auto b = *st.begin(); st.erase(st.begin());

                int Sz = a.size() + b.size();
                int sz = 1LL << (64 - __builtin_clzll(Sz - 1));

                vector <cd> f(sz), g(sz);
                for (int i = 0; i < sz; ++i) {
                        if (i < a.size()) f[i] = a[i];
                        if (i < b.size()) g[i] = b[i];
                }

                fft(f, 0); fft(g, 0);
                for (int i = 0; i < sz; ++i) f[i] *= g[i];
                fft(f, 1);

                vector <ll> res(sz);
                for (int i = 0; i < sz; ++i) res[i] = (ll)round(f[i].re) % mod;

                while (res.size() > 1 && res.back() == 0) res.pop_back();
                while (res.size() > k + 1) res.pop_back();
                st.insert(res);
        }
        vector <ll> res = *st.begin();
        cout << ((res.size() - 1 < k) ? 0 : res[k]);
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
