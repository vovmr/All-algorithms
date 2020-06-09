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

struct node {
	int mn, mx, add;
	node() { mn = mx = add = 0; }
	node(ll x) { mn = mx = x; add = 0; }
	node(node a, node b) { mn = min(a.mn, b.mn); mx = max(a.mx, b.mx); add = 0; }
};

node neutral;
node t[(1 << 21) | 1];

inline void push(int v, int vl, int vr) {
	if (vl != vr) {
		int add = t[v].add;
		t[2 * v + 1].mn += add; t[2 * v + 1].mx += add; t[2 * v + 1].add += add;
		t[2 * v + 2].mn += add; t[2 * v + 2].mx += add; t[2 * v + 2].add += add;
		t[v].add = 0;
	}
}

node get(int v, int vl, int vr, int l, int r) {
	if (l > r) return neutral;
	else if (vl == l && vr == r) return t[v];

	push(v, vl, vr);
	int m = (vl + vr) >> 1;
	return node(get(2 * v + 1, vl, m, l, min(r, m)), get(2 * v + 2, m + 1, vr, max(l, m + 1), r));
}

void upd(int v, int vl, int vr, int l, int r, int x) {
	push(v, vl, vr);
	if (l > r) return;
	else if (vl == l && vr == r) {
		if (vl == vr) {
			t[v].mn += x; t[v].mx += x;
			return;
		}
		t[v].add += x;
		push(v, vl, vr);
		t[v] = node(t[2 * v + 1], t[2 * v + 2]);
		return;
	}
	int m = (vl + vr) >> 1;
	upd(2 * v + 1, vl, m, l, min(r, m), x);
	upd(2 * v + 2, m + 1, vr, max(l, m + 1), r, x);
	t[v] = node(t[2 * v + 1], t[2 * v + 2]);
}

void solve() {
	int n;
	cin >> n;
	vector <char> st(n, 'u');

	neutral.mn = INT_MAX; neutral.mx = -INT_MAX; neutral.add = 0;

	int sz = 1, pos = 0, opened = 0, closed = 0;
	for (int i = 0; i < n; ++i) {
		char F;
		cin >> F;
		if (F == 'R') ++pos, sz = max(sz, pos + 1);
		else if (F == 'L') pos = max(0, pos - 1), sz = max(sz, pos + 1);
		else {
			if (st[pos] == '(') upd(0, 0, n - 1, pos, n - 1, -1), --opened;
			else if (st[pos] == ')') upd(0, 0, n - 1, pos, n - 1, 1), --closed;

			st[pos] = F;
			if (st[pos] == '(') upd(0, 0, n - 1, pos, n - 1, 1), ++opened;
			else if (st[pos] == ')') upd(0, 0, n - 1, pos, n - 1, -1), ++closed;
		}

		if (opened != closed || t[0].mn != 0) cout << -1 << " ";
		else cout << t[0].mx << " ";
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
