#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#define fi first
#define se second
#define ll long long
#define ld long double
#define all(x)              (x).begin(), (x).end()
#define inf                 1e18

using namespace std;
using namespace __gnu_pbds;

template <class T>
using oset = tree <T, null_type, less_equal <T>, rb_tree_tag, tree_order_statistics_node_update>;

const int block = 400;
oset <int> st[block + 1];

void solve() {
	int n, m;
	cin >> n >> m;
	vector <ll> v(n);
	for (int i = 0; i < n; ++i) {
		cin >> v[i];
		st[i / block].insert(v[i]);
	}
	while (m--) {
		char x;
		cin >> x;
		if (x == 'M') {
			ll pos, a;
			cin >> pos >> a; --pos;

			st[pos / block].erase(st[pos / block].lower_bound(v[pos] - 1));
			st[pos / block].insert(a);
			v[pos] = a;
		}
		else {
			ll l, r, k;
			cin >> l >> r >> k; --l; --r;

			int ans = 0;
			for (int i = l; i <= r; ) {
				if (i % block == 0 && i + block - 1 <= r) {
					ans += st[i / block].order_of_key(k + 1);
					i += block;
					continue;
				}
				ans += (v[i] <= k); ++i;
			}
			cout << ans << '\n';
		}
	}
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
//	ifstream cin("input.txt");
//	ofstream cout("output.txt");
	int q = 1; // cin >> q;
	while (q--) solve();
}
