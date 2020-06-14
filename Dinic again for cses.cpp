/// Solution to cses.com "Police chase" (1694)
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
 
#pragma GCC optimize("-O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
 
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

struct edge {
	int v = 0, u = 0, flow = 0, cap = 0;
};

int n, m, s, t;

queue <int> q;
vector <int> d, ptr;
vector <edge> edges;
vector < vector <int> > gr;

void add(int v, int u, int c) {
	edges.push_back((edge){v, u, 0, c});
	edges.push_back((edge){u, v, 0, c});
	gr[v].push_back(edges.size() - 2);
	gr[u].push_back(edges.size() - 1);
}

bool bfs() {
	d.assign(n, -1); d[s] = 0; q.push(s);
	while (!q.empty()) {
		int v = q.front(); q.pop();
		for (auto to : gr[v]) {
			int u = edges[to].u;
			if (d[u] == -1 && edges[to].cap - edges[to].flow > 0) {
				d[u] = d[v] + 1;
				q.push(u);
			}
		}
	}
	return (d[t] >= 0);
}

ll dfs(int v, ll flow) {
	if (v == t || !flow) return flow;
	for (int& a = ptr[v]; a < gr[v].size(); ++a) {
		int to = gr[v][a];
		int u = edges[to].u;
		if (d[u] == d[v] + 1 && edges[to].cap - edges[to].flow > 0) {
			ll f = dfs(u, min(flow, edges[to].cap * 1LL - edges[to].flow));
			if (!f) continue;

			edges[to].flow += f, edges[to ^ 1].flow -= f;
			return f;
		}
	}
	return 0;
}

ll maxFlow() {
	ll f = 0;
	while (bfs()) {
		ptr.assign(n, 0);
		while (ll push = dfs(s, inf)) f += push;
	}
	return f;
}

vector <bool> used;

void go(int v) {
	used[v] = 1;
	for (auto to : gr[v]) {
		if (edges[to].cap - edges[to].flow > 0 && !used[edges[to].u]) {
			go(edges[to].u);
		}
	}
}
 
void solve() {
	cin >> n >> m; s = 0, t = n - 1;
	gr.resize(n); ptr.resize(n); d.resize(n);

	for (int i = 0; i < m; ++i) {
		int v, u;
		cin >> v >> u;
		add(--v, --u, 1);
	}
	cout << maxFlow() << '\n';

	used.resize(n); go(0);
	for (auto &x : edges) {
		if (x.cap - x.flow == 0 && !used[x.u] && used[x.v]) {
			cout << x.v + 1 << " " << x.u + 1 << '\n';
		}
	}
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
