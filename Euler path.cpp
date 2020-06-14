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

vector < vector <int> > gr;
vector < pair <int, int> > e;

vector <int> euler, used, ans;

void dfs(int v) {
	while (gr[v].size()) {
		int u = gr[v].back(); gr[v].pop_back();
		if (used[u]) continue;

		used[u] = 1;
		dfs(e[u].se); ans.push_back(v);
	}
}

void solve() {
	int n, m;
	cin >> n >> m;
	gr.resize(n); e.resize(m); used.resize(m);

	vector <int> deg(n);

	for (int i = 0; i < m; ++i) {
		cin >> e[i].fi >> e[i].se; --e[i].fi, --e[i].se;
		gr[e[i].fi].push_back(i);

		++deg[e[i].fi], ++deg[e[i].se];
	}

	int cnt = 0;
	for (int i = 0; i < n; ++i) {
		if ((i == 0 || i == n - 1) && (deg[i] & 1 ^ 1)) {
			cout << "IMPOSSIBLE";
			exit(0);
		}
		else if (i != 0 && i != n - 1 && (deg[i] & 1)) {
			cout << "IMPOSSIBLE";
			exit(0);
		}
	}

	dfs(0);
	reverse(all(ans));

	if (ans.size() != m) {
		cout << "IMPOSSIBLE";
		return;
	}

	for (auto i : ans) {
		cout << i + 1 << " ";
	}
	cout << n;
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
