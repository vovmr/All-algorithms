#include <bits/stdc++.h>
#define fi first
#define se second
#define ll long long
#define ld long double
#define all(x)              (x).begin(), (x).end()
#define inf                 1e18

using namespace std;

inline ll bp(ll a, ll n, ll m) {
	ll res = 1;
	while (n) {
		if (n & 1) res *= a, res %= m;
		a *= a, a %= m;
		n >>= 1;
	}
	return res;
}

// 998244353 = 119 * 2^23 + 1
const int mod = 998244353, g = 3, pw = 1 << 23; int w[2][pw];
const int r = bp(g, (mod - 1) / pw, mod); const int r1 = bp(r, mod - 2, mod);

inline void f() {
	w[0][0] = w[1][0] = 1;
	for (int i = 1; i < pw; ++i) {
		w[0][i] = ((ll)w[0][i - 1] * r) % mod;
		w[1][i] = ((ll)w[1][i - 1] * r1) % mod;
	}
}

inline void ntt(vector <int> &ar, bool iv) {
	if (ar.size() <= 1) return;
	int n = ar.size(), lg = (int)roundl(log2(n));

	for (int i = 0; i < n; ++i) {
		int j = 0;
		for (int k = 0; k < lg; ++k) {
			if ((i >> k) & 1) {
				j += (1 << (lg - k - 1));
			}
		}
		if (i < j) swap(ar[i], ar[j]);
	}

	for (int len = 2; len <= n; len <<= 1) {
		int s = pw / len;
		for (int i = 0; i < n; i += len) {
			for (int j = 0; j < (len / 2); ++j) {
				int a = ar[i + j], b = ((ll)ar[i + j + (len / 2)] * w[iv][j * s]) % mod;
				ar[i + j] = (a + b < mod ? a + b : a + b - mod);
				ar[i + j + (len / 2)] = (a - b >= 0 ? a - b : a - b + mod);
			}
		}
	}
	if (iv) {
		int n1 = bp(n, mod - 2, mod);
		for (auto &i : ar) i = ((ll)i * n1) % mod;
	}
}

inline ll get(ll a) {
	if (!a) return 1;
	return (1LL << (64 - __builtin_clzll(a - 1)));
}

void solve() { f();
	int n, k;
	cin >> n >> k;
	vector <int> ar(get(5 * n));
	for (int i = 0; i < k; ++i) {
		int x;
		cin >> x; ar[x] = 1;
	}
	ntt(ar, 0);
	for (auto &i : ar) i = bp(i, n / 2, mod);
	ntt(ar, 1);

	ll res = 0;
	for (auto &i : ar) {
		res += ((ll)i * i) % mod;
		if (res >= mod) res -= mod;
	}
	cout << res;
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
//	ifstream cin("input.txt");
//	ofstream cout("output.txt");
	int q = 1; // cin >> q;
	while (q--) solve();
}
