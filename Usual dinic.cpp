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
 
struct Dinic {
 
	struct edge {
		int v = 0, u = 0, flow = 0, cap = 0;
	};
 
	int n, s, t;
	vector <edge> edges;
	vector <int> d, ptr, res;
	vector < vector <int> > gr;
 
	Dinic(int n, int s, int t) : n(n), s(s), t(t) {
		d.resize(n); ptr.resize(n); gr.resize(n);
	}
 
	void add(int v, int u, int cap) {
		edges.push_back((edge){v, u, 0, cap});
		gr[v].push_back(edges.size() - 1);
 
		edges.push_back((edge){u, v, 0, 0});
		gr[u].push_back(edges.size() - 1);
	}
	bool bfs() {
		d.assign(n, -1); d[s] = 0;
		queue <int> q; q.push(s);
		while (!q.empty()) {
			int v = q.front(); q.pop();
			for (auto to : gr[v]) {
				int u = edges[to].u;
				ll flow = edges[to].flow, cap = edges[to].cap;
				if (d[u] == -1 && cap - flow > 0) {
					d[u] = d[v] + 1;
					q.push(u);
				}
			}
		}
		return (d[t] != -1);
	}
	ll pushFlow(int v, ll flow) {
		if (v == t || !flow) return flow;
 
		for (int& a = ptr[v]; a < gr[v].size(); ++a) {
			
			int to = gr[v][a];
			ll u = edges[to].u, Flow = edges[to].flow, cap = edges[to].cap;
 
			if (d[u] == d[v] + 1 && cap - Flow > 0) {
 
				ll newFlow = pushFlow(u, min(flow, cap - Flow));
				if (!newFlow) continue;
 
				res.push_back(u);
				edges[to].flow += newFlow;
				edges[to ^ 1].flow -= newFlow;
				return newFlow;
			}
		}
		return 0;
	}
	vector < vector <int> > maxFlow() {
		 vector < vector <int> > ans;
		 while (1) {
		 	if (!bfs()) break;
		 	ptr.assign(n, 0); res.clear();
		 	while (ll push = pushFlow(s, inf)) {
		 		res.push_back(s); reverse(all(res)); ans.push_back(res); res.clear();
		 	}
		 }
		 return ans;
	}
};
 
void solve() {
	int n, m;
	cin >> n >> m;
 
	Dinic net(n, 0, n - 1);
	for (int i = 0; i < m; ++i) {
		int v, u;
		cin >> v >> u; --v; --u;
		net.add(v, u, 1);
	}
 
	vector < vector <int> > ans = net.maxFlow();
	
	cout << ans.size() << '\n';
	for (auto &i : ans) {
		cout << i.size() << '\n';
		for (auto &j : i) cout << j + 1 << ' ';
		cout << '\n';
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
