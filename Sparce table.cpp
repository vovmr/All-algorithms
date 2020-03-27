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
using ordered_set = tree <T, null_type, less <T>, rb_tree_tag, tree_order_statistics_node_update>;

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
//	ifstream cin("input.txt");
//	ofstream cout("output.txt");
	int n;
	cin >> n;
	int lg = 1;
	while ((1LL << lg) <= n) {
		++lg;
	}
	vector <ll> v(n);
	vector < vector <ll> > f(n, vector <ll> (lg + 1));
	for (int i = 0; i < n; ++i) {
		cin >> v[i];
		f[i][0] = v[i];
	}
	for (int k = 1; k <= lg; ++k) {
		for (int v = 0; v < n; ++v) {
			if (v + (1LL << (k - 1)) >= n) {
				continue;
			}
			f[v][k] = f[v][k - 1] + f[v + (1LL << (k - 1))][k - 1];
		}
	}
	int q;
	cin >> q;
	while (q--) {
		int l, r;
		ll ans = 0;
		cin >> l >> r; --l; --r;
		for (int k = lg; k >= 0; --k) {
			if ((1LL << k) <= r - l + 1) {
				ans += f[l][k];
				l += 1LL << k;
			}
		}
		cout << ans << endl;
	}
}
