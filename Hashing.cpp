#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#define ll long long
#define ld long double
#define all(x)              (x).begin(), (x).end()
#define inf                 1e18

using namespace std;
using namespace __gnu_pbds;

template <typename T>
using ordered_set = tree <T, null_type, less_equal <T>, rb_tree_tag, tree_order_statistics_node_update>;

ll bin_pow(ll a, ll n, ll mod) {
	ll res = 1;
	while (n) {
		if (n & 1) {
			res *= a, res %= mod;
		}
		a *= a, a %= mod;
		n >>= 1;
	}
	return res;
}

ll division(ll a, ll b, ll mod) {
	ll cur = bin_pow(b, mod - 2, mod) * (a % mod);
	return (cur % mod);
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
//	ifstream cin("input.txt");
//	ofstream cout("output.txt");

	ll mod = 1e9 + 7;

	int q;
	string s;
	cin >> s >> q;
	int n = s.size();
	vector <ll> pows(n, 1);
	for (int i = 1; i < n; ++i) {
		pows[i] = (pows[i - 1] * 29) % mod;
	}
	vector <ll> hsh(n); hsh[0] = s[0] - 'a' + 1;
	for (int i = 1; i < n; ++i) {
		hsh[i] = ( (hsh[i - 1] + ((pows[i] * (s[i] - 'a' + 1)) % mod)) % mod);
	}
	auto ghash = [&](int l, int r) {
		ll a = (hsh[r] - ((l == 0) ? 0 : hsh[l - 1]) + 4 * mod) % mod;
		return (division(a, pows[l], mod) % mod);
	};
	while (q--) {
		int l, r, x, y;
		cin >> l >> r >> x >> y; --l; --r; --x; --y;
		cout << ((ghash(l, r) == ghash(x, y)) ? "Identical" : "Diffirent") << endl;
	}
}
