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

struct edge {
	int v = 0, u = 0, cap = 0, cost = 0;
};

vector <ll> d, p;
vector < vector <int> > gr, c, cost;

void dist(int s, int t, bool ok) {
	int n = gr.size();
	vector <bool> inq(n);
	p.assign(n, -1); d.assign(n, inf); d[s] = 0; p[s] = s; inq[s] = 1;

	queue <int> q; q.push(s);
	while (!q.empty()) {
		int v = q.front(); q.pop();

		inq[v] = 0;
		for (auto to : gr[v]) {
			if (c[v][to] > 0 && d[to] > d[v] + cost[v][to]) {
				d[to] = d[v] + cost[v][to]; p[to] = v;
				if (!inq[to]) {
					inq[to] = 1;
					q.push(to);
				}
			}
		}
	}
}

vector <edge> edges;

pair <ll, ll> minCostMaxFlow(int n, int s, int t, ll k, bool ok) {

	gr.resize(n); d.resize(n);
	c.resize(n, vector <int> (n));
	cost.resize(n, vector <int> (n)); p.resize(n);

	for (auto &e : edges) {
		int v = e.v, u = e.u;
		gr[v].push_back(u); gr[u].push_back(v);

		c[v][u] = e.cap;
		cost[v][u] = e.cost;
		cost[u][v] = -e.cost;
	}

	ll f = 0, cost = 0;
	while (f < k) {
		dist(s, t, ok);
		if (d[t] >= 0 && !ok) break;
		if (ok && d[t] >= inf) break;

		ll flow = k - f, v = t;
		while (v != s) {
			flow = min(flow, 1LL * c[p[v]][v]);
			v = p[v];
		}
		f += flow; cost += flow * d[t]; v = t;
		while (v != s) {
			c[p[v]][v] -= flow; c[v][p[v]] += flow;
			v = p[v];
		}
	}
	return {f, cost};
}

vector <int> ar;
vector < pair <int, int> > v;

ll killAttacking(int n, int m, int s, int t) {
	for (int i = 1; i <= m; ++i) edges.push_back((edge){s, i, 1, 0});
	for (int i = m + 1; i <= n + m; ++i) edges.push_back((edge){i, t, 1, 0});

	for (int j = 0; j < n; ++j) {
		for (int i = 0; i < m; ++i) {
			if (v[j].fi == 1 && ar[i] > v[j].se) {
				edges.push_back((edge){ i + 1, m + 1 + j, 1, v[j].se - ar[i] });
			}
		}
	}
	return -minCostMaxFlow(n + m + 2, s, t, inf, 0).se;
}

ll killAll(int n, int m) {
	edges.clear(); gr.clear(); c.clear(); d.clear(); p.clear(); cost.clear();

	int s = 0, t = 2 * m + 1;

	for (int i = 1; i <= m; ++i) edges.push_back((edge){s, i, 1, 0});
	for (int i = m + 1; i <= 2 * m; ++i) edges.push_back((edge){i, t, 1, 0});

	for (int i = 0; i < m; ++i) {
		for (int j = 0; j < m; ++j) {
			if (j < n) {
				if (v[j].fi == 1 && ar[i] >= v[j].se) {
					edges.push_back((edge){i + 1, m + 1 + j, 1, v[j].se - ar[i]});
				}
				else if (v[j].fi == 2 && ar[i] > v[j].se) {
					edges.push_back((edge){i + 1, m + 1 + j, 1, 0});
				}
			}
			else {
				edges.push_back((edge){ i + 1, m + 1 + j, 1, -ar[i] });
			}
		}
	}
	auto F = minCostMaxFlow(2 * m + 2, s, t, inf, 1);
	return ((F.fi == m) ? -F.se : 0LL);
}
 
void solve() {
	
	int n, m;
	cin >> n >> m;

	ar.resize(m); v.resize(n);

	for (auto &i : v) {
		string s; cin >> s >> i.se;
		if (s == "ATK") i.fi = 1;
		else i.fi = 2;
	}
	for (auto &i : ar) cin >> i;

	int s = 0, t = n + m + 1;
	ll res = killAttacking(n, m, s, t);
	if (m > n) res = max(res, killAll(n, m));

	cout << res << '\n';
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
