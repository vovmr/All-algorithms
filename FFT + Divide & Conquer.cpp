#include <bits/stdc++.h>
#define fi first
#define se second
#define ll long long
#define ld long double
#define all(x)              (x).begin(), (x).end()
#define inf                 1e18

using namespace std;

#define re real()
#define im imag()

typedef complex <double> cd;
const double pi = 3.141592653589793223846264338327950;
 
inline cd operator + (const cd &a, const cd &b) { return cd(a.re + b.re, a.im + b.im); }
inline cd operator - (const cd &a, const cd &b) { return cd(a.re - b.re, a.im - b.im); }
inline cd operator * (const cd &a, const cd &b) { return cd(a.re * b.re - a.im * b.im, a.re * b.im + a.im * b.re); }
inline cd operator / (const cd &a, const ld &b) { return cd(a.re / b, a.im / b); }

const ll mod = 99991;
const ll phi = 55048;
const ll phiinv = 44944;
const ll rootinv = 22019;

inline ll get(ll a) {
	if (!a) return 1;
	if (!(a & (a - 1))) return a;
	return (1LL << (64 - __builtin_popcountll(a - 1)));
}

inline void fft(vector <cd> &ar, bool in = 0) {
	if (ar.size() == 1) return;

	int n = ar.size(), lg = 0;
	while ((1 << lg) < n) ++lg;
	for (int i = 0; i < n; ++i) {
		int j = 0;
		for (int k = 0; k < lg; ++k) {
			if ((i >> k) & 1) {
				j += (1 << (lg - k - 1));
			}
		}
		if (i < j) swap(ar[i], ar[j]);
	}

	vector <cd> w(n); w[0] = 1;
	for (int i = 1; i < n; ++i) {
		double a = 2.0 * pi * i * (in ? -1.0 : 1.0) / (double)n;
		w[i] = cd(cos(a), sin(a));
	}
	for (int len = 2; len <= n; len <<= 1) {
		int s = n / len;
		for (int i = 0; i < n; i += len) {
			for (int j = 0; j < len / 2; ++j) {
				cd a = ar[i + j], b = w[j * s] * ar[i + j + (len / 2)];
				ar[i + j] = a + b;
				ar[i + j + (len / 2)] = a - b;
			}
		}
	}
	if (in) for (auto &x : ar) x /= n;
}

struct polynomial {
	vector <ll> a;
	polynomial() {}
};

inline polynomial mult(const polynomial &A, const polynomial &B) {
	vector <ll> a = A.a, b = B.a;
	int s = 2 * get(max(a.size(), b.size())); vector <cd> f(s), g(s);

	for (int i = 0; i < a.size(); ++i) f[i] = a[i];
	for (int i = 0; i < b.size(); ++i) g[i] = b[i];

	fft(f); fft(g); for (int i = 0; i < s; ++i) f[i] = f[i] * g[i];
	fft(f, 1);

	polynomial ans; ans.a.resize(s);
	for (int i = 0; i < s; ++i) ans.a[i] = (ll)roundl(f[i].re) % mod;
	return ans;
}

vector < polynomial > ar;

polynomial DC(int l, int r) {
	if (l == r) return ar[l];

	int m = l + r >> 1;
	polynomial a = DC(l, m);
	polynomial b = DC(m + 1, r);
	return (mult(a, b));
}

inline ll bp(ll a, ll n) {
	ll res = 1;
	while (n) {
		if (n & 1) res *= a, res %= mod;
		a *= a, a %= mod;
		n >>= 1;
	}
	return res;
}

void solve() {
	int n, k;
	cin >> n >> k;
	vector <ll> v(n);
	for (auto &i : v) cin >> i;

	ar.resize(n);
	for (int i = 0; i < n; ++i) {
		ar[i].a.push_back(1);
		ar[i].a.push_back(bp(phi, v[i]));
	}

	polynomial ans = DC(0, ar.size() - 1);
	for (int i = 0; i < n; ++i) {
		ar[i].a.clear();
		ar[i].a.push_back(1);
		ar[i].a.push_back(bp(phiinv, v[i]));
	}
	polynomial answer = DC(0, ar.size() - 1);
	cout << ((ans.a[k] - answer.a[k] + 3 * mod) * rootinv) % mod;

}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
//	ifstream cin("input.txt");
//	ofstream cout("output.txt");
	int q = 1; // cin >> q;
	while (q--) solve();
}

