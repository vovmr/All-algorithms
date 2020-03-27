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

vector <bool> used;
vector <int> ac, sz, d, h;
vector < vector <int> > gr;

void distances(int v, int p) {
	sz[v] = 1;
	for (auto to : gr[v]) {
		if (to != p && !used[to]) {
			distances(to, v);
			sz[v] += sz[to];
		}
	}
}

void h_es(int v, int p) {
	for (auto to : gr[v]) {
		if (to != p) {
			h[to] = h[v] + 1;
			h_es(to, v);
		}
	}
}

int centroid(int v, int p, int n) {
	for (auto to : gr[v]) {
		if (to != p && sz[to] > n / 2 && !used[to]) {
			return centroid(to, v, n);
		}
	}
	return v;
}

void build_cd(int v, int p, int n) {
	ac[v] = p;
	used[v] = 1;
	distances(v, p);
	for (auto to : gr[v]) {
		if (used[to]) {
			continue;
		}
		build_cd(centroid(to, v, sz[to]), v, sz[to]);
	}
}

int lg, t = 0;
vector <int> in, out;
vector < vector <int> > up;

void dfs(int v, int p) {
	in[v] = ++t;
	up[v][0] = p;
	for (int i = 1; i <= lg; ++i) {
		up[v][i] = up[up[v][i - 1]][i - 1];
	}
	for (auto to : gr[v]) {
		if (to != p) {
			dfs(to, v);
		}
	}
	out[v] = ++t;
}

bool upper(int a, int b) {
	return (in[a] <= in[b] && out[b] <= out[a]);
}

int lca(int a, int b) {
	if (upper(a, b)) {
		return a;
	}
	else if (upper(b, a)) {
		return b;
	}
	for (int i = lg; i >= 0; --i) {
		if (!upper(up[a][i], b)) {
			a = up[a][i];
		}
	}
	return up[a][0];
}

int dist(int a, int b) {
	return (h[a] + h[b] - 2 * h[lca(a, b)]);
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
//	ifstream cin("input.txt");
//	ofstream cout("output.txt");
	int n, m;
	cin >> n >> m;
	gr.resize(n); sz.resize(n); used.resize(n); d.resize(n, n + 5); ac.resize(n); h.resize(n);
	for (int i = 0; i < n - 1; ++i) {
		int v, u;
		cin >> v >> u; --v; --u;
		gr[v].push_back(u);
		gr[u].push_back(v);
	}
	distances(0, -1);
	int c = centroid(0, -1, n);
	build_cd(c, -1, n); h_es(c, -1);

	while ((1 << lg) <= n) {
		++lg;
	}
	up.resize(n); in.resize(n); out.resize(n);
	for (int i = 0; i < n; ++i) {
		up[i].resize(lg + 1);
	}
	dfs(c, c);

	int test = 0, cur_test = 0;
	while (1) {
		d[cur_test] = min(d[cur_test], dist(test, cur_test));
		if (ac[cur_test] == -1) {
			break;
		}
		cur_test = ac[cur_test];
	}
	while (m--) {
		int a, v;
		cin >> a >> v; --v;
		if (a == 1) {
			int cur = v;
			while (1) {
				d[cur] = min(d[cur], dist(v, cur));
				if (ac[cur] == -1) {
					break;
				}
				cur = ac[cur];
			}
		}
		else {
			ll ans = inf;
			int cur = v;
			while (1) {
				ans = min(ans, d[cur] +  1LL * dist(v, cur));
				if (ac[cur] == -1) {
					break;
				}
				cur = ac[cur];
			}
			cout << ans << '\n';
		}
	}
}
