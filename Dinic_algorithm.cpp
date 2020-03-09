// solution to 499E on codeforces using
// maximal flow dinic's algorithm

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

struct Dinic {

	queue <int> q;
	int n, m = 0, s, t;
	vector <edge> edges;
	vector <int> d, ptr;
	vector < vector <int> > gr;

	Dinic(int n, int s, int t) {
		this->n = n, this->s = s, this->t = t;
		gr.resize(n); ptr.resize(n); d.resize(n);
	}

	void add_edge(int v, int u, ll cap) {
		edges.push_back(edge(v, u, cap));
		edges.push_back(edge(u, v, 0));
		gr[v].push_back(m);
		gr[u].push_back(m + 1); ++++m;
	}
	bool bfs() {
		while (!q.empty()) {
			int v = q.front(); q.pop();
			for (auto to : gr[v]) {
				int u = edges[to].u;
				ll flow = edges[to].flow, cap = edges[to].cap;
				if (d[u] == -1 && cap - flow >= 1) {
					d[u] = d[v] + 1;
					q.push(u);
				}
			}
		}
		return (d[t] != -1);
	}
	ll dfs(int v, ll flow) {
		if (!flow || v == t) {
			return flow;
		}
		for (int& to = ptr[v]; to < gr[v].size(); ++to) {
			int to1 = gr[v][to];
			int u = edges[to1].u;
			ll _flow = edges[to1].flow, cap = edges[to1].cap;
			if (d[u] == d[v] + 1 && cap - _flow >= 1) {
				ll new_flow = dfs(u, min(flow, cap - _flow));
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
	ll mx_flow() {
		ll flow = 0;
		while (1) {
			d.assign(n, -1); d[s] = 0; q.push(s);
			if (!bfs()) {
				break;
			}
			ptr.assign(n, 0);
			while (ll pushed = dfs(s, inf)) {
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
	int n, m;
	cin >> n >> m;
	map <ll, bool> used;
	vector < map <ll, ll> > mp(n);
	for (int i = 0; i < n; ++i) {
		ll x;
		cin >> x;
		for (ll j = 2; j * j <= x; ++j) {
			while (x % j == 0) {
				used[j] = 1;
				++mp[i][j];
				x /= j;
			}
		}
		if (x > 1) {
			++mp[i][x];
			used[x] = 1;
		}
	}
	vector < pair <int, int> > q;
	for (int i = 0; i < m; ++i) {
		int a, b;
		cin >> a >> b; --a; --b;
		q.push_back(make_pair(a, b));
	}
	ll flow = 0;
	for (auto x : used) {
		ll cur_prime = x.first;
		Dinic network(n + 2, n, n + 1);
		for (int i = 0; i < n; ++i) {
			if (!(i & 1)) {
				network.add_edge(n, i, mp[i][cur_prime]);
			}
			else {
				network.add_edge(i, n + 1, mp[i][cur_prime]);
			}
		}
		for (int i = 0; i < m; ++i) {
			if (!(q[i].second & 1)) {
				swap(q[i].first, q[i].second);
			}
			network.add_edge(q[i].first, q[i].second, mp[q[i].first][cur_prime]);
		}
		flow += network.mx_flow();
	}
	cout << flow;
}
