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

template <typename T>
using ordered_set = tree <T, null_type, less <T>, rb_tree_tag, tree_order_statistics_node_update>;

const ll mod = 1e9 + 7;

int gr[21][21];
ll dp[1 << 20][20];

void solve() {
	int n, m;
	cin >> n >> m;
	for (int i = 0; i < m; ++i) {
		int v, u;
		cin >> v >> u; --v; --u; ++gr[v][u];
	}
	dp[1][0] = 1;
	for (int mask = 1; mask < (1 << n); ++mask) {
		for (int i = 0; i < n; ++i) {
			if (!((mask >> i) & 1)) continue;
			for (int j = 0; j < n; ++j) {
				if ((mask >> j) & 1) continue;
				( dp[mask | (1 << j)][j] += gr[i][j] * dp[mask][i] ) %= mod;
			}
		}
	}
	cout << dp[(1 << n) - 1][n - 1];
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
//	ifstream cin("input.txt");
//	ofstream cout("output.txt");
	int q = 1; // cin >> q;
	while (q--) {
		solve();
	}
}
