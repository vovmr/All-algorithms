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
	ll v = 0, u = 0, flow = 0, cap = 0;
};

int n, m, s, t;

queue <int> q;
vector <int> d, ptr;
vector <edge> edges;
vector < vector <int> > gr;

void add(ll v, ll u, ll c) {
	edges.push_back((edge){v, u, 0, c});
	edges.push_back((edge){u, v, 0, 0});
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
 
void solve() {
	cin >> n >> m; s = 0, t = n - 1;
	gr.resize(n); ptr.resize(n); d.resize(n);

	for (int i = 0; i < m; ++i) {
		ll v, u, c;
		cin >> v >> u >> c;
		add(--v, --u, c);
	}
	cout << maxFlow() << '\n';
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
