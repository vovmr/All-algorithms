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

const int N = 500;

int c[N][N];
bitset <N> used;
vector <int> gr[N];

ll bfs(int s, int t, vector <int> &p) {
	int n = p.size();
	p.assign(n, -1);
	p[s] = -2;
	queue < pair <int, ll> > q;
	q.push({s, inf});
	while (!q.empty()) {
		auto d = q.front(); q.pop();
		int id = d.first;
		ll flow = d.second;
		for (auto to : gr[id]) {
			if (p[to] == -1 && c[id][to]) {
				p[to] = id;
				ll cur_flow = min(flow, 1LL * c[id][to]);
				if (to == t) {
					return cur_flow;
				}
				q.push({to, cur_flow});
			}
		}
	}
	return 0;
}

ll mx_flow(int s, int t) {
	int n = N;
	vector <int> parent(N);
	ll flow = 0, new_flow = 0;
	while (new_flow = bfs(s, t, parent)) {
		flow += new_flow;
		int cur = t;
		while (cur != s) {
			int prev = parent[cur];
			c[prev][cur] -= new_flow;
			c[cur][prev] += new_flow;
			cur = prev;
		}
	}
	return flow;
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
//	ifstream cin("input.txt");
//	ofstream cout("output.txt");
}
