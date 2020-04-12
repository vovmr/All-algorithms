// Solution for 538F on Codeforces

#pragma GCC optimize("-O3")
#pragma GCC optimize("unroll-loops")

#include <bits/stdc++.h>
//#include <ext/pb_ds/assoc_container.hpp>
//#include <ext/pb_ds/tree_policy.hpp>
#define fi first
#define se second
#define ll long long
#define ld long double
#define all(x)              (x).begin(), (x).end()
#define inf                 1e18

using namespace std;
//using namespace __gnu_pbds;

//template <typename T>
//using ordered_set = tree <T, null_type, less <T>, rb_tree_tag, tree_order_statistics_node_update>;

struct tree {
	ll sum, l, r;
	tree() : l(0), r(0), sum(0) {}
};

int allw = 0;
const int N = 1e6 + 2e5;

tree t[5 * N];
int root[N], lst[N];

void build(int v, int vl, int vr) {
	lst[v] = v;
	allw = max(allw, v + 1);
	if (vl == vr) {
		t[v].sum = 0;
		return;
	}
	int m = (vl + vr) >> 1;
	t[v].l = 2 * v + 1, t[v].r = 2 * v + 2;
	build(2 * v + 1, vl, m); build(2 * v + 2, m + 1, vr);
}

ll get(int v, int vl, int vr, int l, int r) {
	if (l > r) return 0;
	else if (vl == l && vr == r) return t[v].sum;
	int m = (vl + vr) >> 1;
	return ( get(t[v].l, vl, m, l, min(r, m)) + get(t[v].r, m + 1, vr, max(l, m + 1), r) );
}

void upd(int v, int x, int vl, int vr, int pos, int val) {
	int cur = lst[x]; lst[x] = v;
	if (vl == vr) {
		t[v].sum = val;
		return;
	}
	int m = (vl + vr) >> 1; t[v] = t[cur];
	if (pos <= m) {
		t[v].l = ++allw;
		upd(t[v].l, 2 * x + 1, vl, m, pos, val);
	}
	else {
		t[v].r = ++allw;
		upd(t[v].r, 2 * x + 2, m + 1, vr, pos, val);
	}
	t[v].sum = t[t[v].l].sum + t[t[v].r].sum;
}

void solve() {

	int n;
	cin >> n;
	vector < pair <ll, int> > v(n);
	for (int i = 0; i < n; ++i) {
		cin >> v[i].fi;
		v[i].se = i + 1;
	}
	sort(all(v));

	build(0, 0, n);
	vector <ll> add(n + 1); add[0] = -inf;

	for (int i = 1; i <= n; ++i) {

		add[i] = v[i - 1].fi;

		root[i] = ++allw;
		upd(root[i], 0, 0, n, v[i - 1].se, 1);
	}

	auto cnt = [&](int l, int r, ll x) {

		int ans = lower_bound(all(add), x) - add.begin() - 1;

		if (ans == 0) return 0LL;
		return get(root[ans], 0, n, l, r);
	};

	vector <ll> ans(n);

	sort(all(v), [&](const pair <ll, int> &a, const pair <ll, int> &b) { return (a.se < b.se); });

	for (int i = 1; i <= n; ++i) {
		for (int k = 1; k < n; ++k) {

			int l = k * (i - 1) + 2, r = k * i + 1;
			if (l > n || min(r, n) < l) break;

			r = min(r, n);
			ans[k] += cnt(l, r, v[i - 1].fi);

		}
	}

	for (int i = 1; i < n; ++i) cout << ans[i] << " ";
	cout << '\n';
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
