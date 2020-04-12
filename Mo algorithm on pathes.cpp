// Given a tree with (n) nodes and queries:
// Find the count of unique numbers on path fron (u) to (v)

#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")

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

const int sz = 420;

struct query {
	int l, r, lca, id;
	inline pair <int, int> toPair() const {
		return { (l / sz), (((l / sz) & 1) ? -r : r) };
	}
};

bool operator < (const query &a, const query &b) {
	return (a.toPair() < b.toPair());
}

int lg = 0, t = 0;
const int N = 1e5 + 1;

vector <int> ord;
vector <int> gr[N], up[N];
int in[N], out[N], st[N], en[N], h[N];

void dfs(int v, int p) {

	in[v] = ++t;
	up[v][0] = p;
	ord.push_back(v); st[v] = ord.size() - 1;

	for (int i = 1; i <= lg; ++i) {
		up[v][i] = up[up[v][i - 1]][i - 1];
	}

	for (auto to : gr[v]) {
		if (to != p) {
			h[to] = h[v] + 1;
			dfs(to, v);
		}
	}

	out[v] = ++t;
	ord.push_back(v); en[v] = ord.size() - 1;
}

bool ac(int a, int b) {
	return (in[a] <= in[b] && out[b] <= out[a]);
}

int lca(int a, int b) {
	if (ac(a, b)) return a;
	if (ac(b, a)) return b;
	for (int i = lg; i >= 0; --i) {
		if (!ac(up[a][i], b)) {
			a = up[a][i];
		}
	}
	return up[a][0];
}

query make(int v, int u, int id) {
	if (h[v] > h[u]) swap(v, u);

	int lc = lca(v, u);
	if (v == lc || u == lc) return (query){st[v], st[u], lc, id};
	else return (query){en[v], st[u], lc, id};
}

int nonZ = 0;
int cnt[N], mp[N + 100];

inline void add(int x, int col) {
	if (cnt[x] && ((--mp[col]) == 0)) --nonZ;
	else if (!cnt[x] && ((mp[col]++) == 0)) ++nonZ;
	cnt[x] ^= 1;
}

void solve() {
	int n, m;
	cin >> n >> m;

	while ((1 << lg) <= n) ++lg;
	++lg;

	vector <int> comp(n);
	vector < pair <ll, int> > col(n);
	for (int i = 0; i < n; ++i) up[i].resize(lg + 1);

	for (int i = 0; i < n; ++i) {
		cin >> col[i].fi; col[i].se = i;
	}
	sort(all(col));
	for (int i = 0; i < n; ++i) {
		if (i == 0) {
			comp[col[i].se] = 0;
		}
		else {
			comp[col[i].se] = comp[col[i - 1].se] + (col[i].fi != col[i - 1].fi);
		}
	}

	for (int i = 0; i < n - 1; ++i) {
		int v, u;
		cin >> v >> u; --v; --u;
		gr[v].push_back(u); gr[u].push_back(v);
	}
	dfs(0, 0);
	vector <query> q;
	for (int i = 0; i < m; ++i) {
		int v, u;
		cin >> v >> u; --v; --u;

		q.push_back(make(v, u, i));
	}
	sort(all(q));
	vector <int> ans(m);

	int l = q[0].l, r = q[0].l - 1;
	for (int i = 0; i < m; ++i) {

		while (l < q[i].l) add(ord[l], comp[ord[l]]), ++l;
		while (r > q[i].r) add(ord[r], comp[ord[r]]), --r;

		while (l > q[i].l) --l, add(ord[l], comp[ord[l]]);
		while (r < q[i].r) ++r, add(ord[r], comp[ord[r]]);

		int fir = ord[l], sec = ord[r];

		if (q[i].lca != fir && q[i].lca != sec) add(q[i].lca, comp[q[i].lca]);

		ans[q[i].id] = nonZ;

		if (q[i].lca != fir && q[i].lca != sec) add(q[i].lca, comp[q[i].lca]);

	}
	for (auto i : ans) cout << i << '\n';
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
