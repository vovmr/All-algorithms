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

struct edge {
	int v, u;
	ll flow, cap;
	edge(int v, int u, ll cap) : v(v), u(u), cap(cap), flow(0) {}
};

int n, s, t;
vector <int> d;
vector < vector <edge> > gr;

bool bfs() {
	queue <int> q;
	d.assign(n, -1); d[s] = 0; q.push(s);
	while (!q.empty()) {
		int v = q.front(); q.pop();
		for (int i = 0; i < gr[v].size(); ++i) {
			int to = gr[v][i].u;
			ll flow = gr[v][i].flow, cap = gr[v][i].cap;
			if (to != -1 && d[to] == -1 && cap - flow >= 1) {
				d[to] = d[v] + 1;
				q.push(to);
			}
		}
	}
	return (d[t] != -1);
}

ll dfs(int v, ll flow) {
	if (!flow || v == t) {
		return flow;
	}
	for (int i = 0; i < gr[v].size(); ++i) {
		int to = gr[v][i].u;
		ll _flow = gr[v][i].flow, cap = gr[v][i].cap;
		if (to != -1 && d[to] == d[v] + 1 && cap - _flow >= 1) {
			ll new_flow = dfs(to, min(flow, cap - _flow));
			if (new_flow == 0) {
				continue;
			}
			gr[v][i].flow += new_flow;
			gr[i][v].flow -= new_flow;
			return new_flow;
		}
	}
	return 0;
}

ll mx_flow() {
	ll flow = 0;
	while (1) {
		if (!bfs()) {
			break;
		}
		while (ll pushed = dfs(s, inf)) {
			flow += pushed;
		}
	}
	return flow;
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
//	ifstream cin("input.txt");
//	ofstream cout("output.txt");
	int m;
	cin >> n >> m; n += 2; s = n - 2, t = n - 1;
	d.resize(n, -1); gr.resize(n, vector <edge> (n, edge(-1, -1, 0)));
	for (int i = 0; i < m; ++i) {
		int v, u;
		cin >> v >> u; --v; --u;
		gr[s][v] = edge(s, v, 1); gr[v][s] = edge(v, s, 0);
		gr[u][t] = edge(u, t, 1); gr[t][u] = edge(t, u, 0);
		gr[v][u] = edge(v, u, 1);
		gr[u][v] = edge(u, v, 0);
	}
	cout << mx_flow();

}
