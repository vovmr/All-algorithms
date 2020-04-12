// Task 375D on Codeforces

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

const int sz = 317;

struct query {
	int l, r, x, id;
	inline pair <int, int> toPair() const {
		return { (l / sz), (((l / sz) & 1) ? -r : r) };
	}
};

bool operator < (const query &a, const query &b) {
	return (a.toPair() < b.toPair());
}

int pos = 0;

vector < vector <int> > gr;
vector <int> pre_order, fir, last, col;

void dfs(int v, int p) {
	fir[v] = pre_order.size();
	pre_order.push_back(v);
	for (auto to : gr[v]) {
		if (to != p) {
			dfs(to, v);
		}
	}
	last[v] = pre_order.size() - 1;
}

const int N = 1e5 + 28;
int f[2 * N], mp[N];

int get(int j) {
	int ans = 0;
	for (; j >= 0; j = (j & (j + 1)) - 1) ans += f[j];
	return ans;
}

void upd(int j, int x) {
	for (; j < 2 * N; j |= (j + 1)) f[j] += x;
}

void add_to_set(int v) {
	int c = col[v];
	upd(N + mp[c], -1); ++mp[c]; upd(N + mp[c], 1);
}

void del_from_set(int v) {
	int c = col[v];
	upd(N + mp[c], -1); --mp[c]; upd(N + mp[c], 1);
}

void solve() {
	int n, m;
	cin >> n >> m;
	gr.resize(n); fir.resize(n); last.resize(n); col.resize(n);
	
	for (auto &i : col) cin >> i;
	for (int i = 0; i < n - 1; ++i) {
		int v, u;
		cin >> v >> u; --v; --u;
		gr[v].push_back(u);
		gr[u].push_back(v);
	}
	dfs(0, 0);
	vector < pair <int, int> > v(m);
	for (auto &i : v) {
		cin >> i.fi >> i.se; --i.fi;
	}

	vector <query> q(m);
	for (int i = 0; i < m; ++i) {
		q[i] = (query){ fir[v[i].fi], last[v[i].fi], v[i].se, i };
	}
	sort(all(q));

	upd(N, n);

	int l = 0, r = -1;
	vector <int> ans(m);
	for (int i = 0; i < m; ++i) {
		while (l < q[i].l) del_from_set(pre_order[l]), ++l;
		while (r > q[i].r) del_from_set(pre_order[r]), --r;

		while (l > q[i].l) --l, add_to_set(pre_order[l]);
		while (r < q[i].r) ++r, add_to_set(pre_order[r]);

		ans[q[i].id] = n - get(N + q[i].x - 1);
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
