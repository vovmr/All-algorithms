/// NTT (Number theory transform) is a cool version of FFT
/// While FFT is based on the roots of unity (x^n = 1), NTT is based on
/// primitive roots x^n == 1 ( mod p )
/// It can do whatever FFT can, but calculates every coefficient by modulo p
/// which makes it good, when you need to multiply two polynomials and print each coefficient modulo p

#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("avx,avx2,fma")

#define fi first
#define se second
#define ll long long
#define ld long double
#define all(x)              (x).begin(), (x).end()
#define inf                 1e18

using namespace std;
using namespace __gnu_pbds;

template <typename T>
using ordered_set = tree <T, null_type, less <T>, rb_tree_tag, tree_order_statistics_node_update>;

const int mod = 998244353; /// our modulo, 998244353 = 119 * 2^23 + 1
const int root = 15311432; /// first primitive root: root = pow( 3, (mod - 1) / pw )
const int rootI = 469870224; /// rootI is root modulo inverse in Z/pZ
const int pw = 1 << 23; /// from our modulo

int w[2][pw];
/// w[0] - roots of unity over the field Z/pZ
/// w[1] - inverse roots of unity over the field Z/pZ

inline int mul(int a, int b) { return ((a * 1LL * b) % mod); }

int bp(int a, int n) {
        int res = 1;
        while (n) {
                if (n & 1) res = mul(res, a);
                a = mul(a, a);
                n >>= 1;
        }
        return res;
}

inline void fft(vector <int> &ar, bool inv) { just like casual fft
        if (ar.size() == 1) return;

        int n = ar.size();
        for (int i = 1, j = 0; i < n; i++) {
                int bit = n >> 1;
                for (; j & bit; bit >>= 1)
                        j ^= bit;
                j ^= bit;
                if (i < j) swap(ar[i], ar[j]);
        }

        for (int len = 2; len <= n; len <<= 1) {
                int step = pw / len;
                for (int i = 0; i < n; i += len) {
                        for (int j = 0; j < len / 2; ++j) {
                                int a = ar[i + j], b = mul(ar[i + j + (len / 2)], w[inv][j * step]);
                                ar[i + j] = ((a + b < mod) ? (a + b) : (a + b - mod));
                                ar[i + j + (len / 2)] = ((a - b >= 0) ? (a - b) : (a - b + mod));
                        }
                }
        }
        if (inv) {
                int cur = bp(n, mod - 2);
                for (auto &i : ar) i = mul(i, cur);
        }
}

inline ll get(ll a) { /// prints the first power of 2, that is greater or equal to 'a'
        if (a == 1 || !(a & (a - 1))) return a;
        return (1LL << (64 - __builtin_clzll(a - 1)));
}

inline void mult(vector <int> &a, vector <int> b) {
        int sz = 2 * max(get(a.size()), get(b.size()));
        while (a.size() < sz) a.push_back(0);
        while (b.size() < sz) b.push_back(0);

        fft(a, 0); fft(b, 0);
        for (int i = 0; i < a.size(); ++i) a[i] = mul(a[i], b[i]);

        fft(a, 1);
        while (a.back() == 0) a.pop_back();
}

void solve() {
        int n, k;
        cin >> n >> k;
        vector <int> ar(get(5 * n));
        for (int i = 0; i < k; ++i) {
                int x;
                cin >> x; ar[x] = 1;
        }

        w[0][0] = 1; w[1][0] = 1;
        for (int i = 1; i < pw; ++i) {
                w[0][i] = mul(w[0][i - 1], root);
                w[1][i] = mul(w[1][i - 1], rootI);
        }
        fft(ar, 0);
        for (auto &i : ar) i = bp(i, n / 2);

        fft(ar, 1);
        
        ll ans = 0;
        for (auto i : ar) {
                ans += mul(i, i);
                if (ans >= mod) ans -= mod;
        }
        cout << ans;
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
