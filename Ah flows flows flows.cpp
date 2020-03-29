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

struct Dinic {

	struct edge {
		int v, u, flow, cap;
		edge() : v(0), u(0), flow(0), cap(0) {}
		edge(int v, int u, int cap) : v(v), u(u), cap(cap), flow(0) {}
	};
	
	queue <int> q;
	int n, m = 0, s, t;
	vector <edge> edges;
	vector <int> d, ptr;
	vector < vector <int> > gr;

	Dinic(int n, int s, int t) {
		this->n = n, this->s = s, this->t = t;
		gr.resize(n); ptr.resize(n); d.resize(n);
	}
	void add_edge(int v, int u, int cap) {
		gr[v].push_back(m++); gr[u].push_back(m++);
		edges.push_back(edge(v, u, cap)); edges.push_back(edge(u, v, 0));
	}
	bool bfs() {
		q.push(s);
		d.assign(n, -1); d[s] = 0;
		while (!q.empty()) {
			int x = q.front(); q.pop();
			for (auto to : gr[x]) {
				int u = edges[to].u;
				int flow = edges[to].flow, cap = edges[to].cap;
				if (d[u] == -1 && cap - flow >= 1) {
					q.push(u); d[u] = d[x] + 1;
				}
			}
		}
		return (d[t] != -1);
	}
	int dfs(int v, int flow) {
		if (!flow || v == t) {
			return flow;
		}
		for (int& to = ptr[v]; to < gr[v].size(); ++to) {
			int to1 = gr[v][to]; int u = edges[to1].u, _flow = edges[to1].flow, cap = edges[to1].cap;
			if (d[u] == d[v] + 1 && cap - _flow >= 1) {
				int new_flow = dfs(u, min(flow, cap - _flow));
				if (new_flow == 0) {
					continue;
				}
				edges[to1].flow += new_flow;
				edges[to1 ^ 1].flow -= new_flow;
				return new_flow;
			}
		}
		return 0;
	}
	int get_flow() {
		int flow = 0;
		while (1) {
			if (!bfs()) {
				break;
			}
			ptr.assign(n, 0);
			while (int pushed = dfs(s, INT_MAX)) {
				flow += pushed;
			}
		}
		return flow;
	}

};

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
//	ifstream cin("input.txt");
//	ofstream cout("output.txt");
	int n, m, s, t;
	cin >> n >> m >> s >> t; --s; --t;

	Dinic network(n, s, t);
	for (int i = 0; i < m; ++i) {
		int v, u, cap;
		cin >> v >> u >> cap; --v; --u;
		network.add_edge(v, u, cap);
	}
	cout << network.get_flow();
}
