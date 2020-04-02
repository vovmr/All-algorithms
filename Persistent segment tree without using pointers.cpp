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

struct st {
	int l, r, sum;
	st() : l(0), r(0), sum(0) {}
};

int allw = 0;
vector <st> t;
vector <int> lst, root;

void build(int v, int vl, int vr) {
	lst[v] = v;
	allw = max(allw, v + 1);
	if (vl == vr) {
		return;
	}
	int m = (vl + vr) >> 1;
	t[v].l = 2 * v + 1, t[v].r = 2 * v + 2;
	build(t[v].l, vl, m); build(t[v].r, m + 1, vr);
}

void upd(int v, int x, int vl, int vr, int pos, ll val) {
	int cur = lst[x]; lst[x] = v;
	if (vl == vr) {
		t[v].sum += val;
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

ll get(int v, int vl, int vr, int l, int r) {
	if (l > r) return 0;
	else if (vl == l && vr == r) return t[v].sum;
	int m = (vl + vr) >> 1;
	return ( get(t[v].l, vl, m, l, min(r, m)) + get(t[v].r, m + 1, vr, max(l, m + 1), r) );
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
//	ifstream cin("input.txt");
//	ofstream cout("output.txt");
// Calculates k-th order statistics queries on a segment in O(log^2(n))
	int n;
	cin >> n;
	t.resize(16 * n, st()); lst.resize(4 * n); root.resize(n + 1);
	
	vector < pair <int, int> > v(n);
	for (int i = 0; i < n; ++i) {
		ll x;
		cin >> x;
		v[i] = {x, i};
	}
	sort(all(v));
	build(0, 0, n - 1);
	for (int i = 1; i <= n; ++i) {
		root[i] = ++allw;
		upd(root[i], 0, 0, n - 1, v[i - 1].second, 1);
		cout << i << " " << get(root[i], 0, n - 1, 0, n - 1) << endl;
	}
	int q;
	cin >> q;
	while (q--) {
		int l, r, k;
		cin >> l >> r >> k; --l; --r;

		int _l = 1, _r = n, mid, ans = n;
		while (_l <= _r) {
			mid = (_l + _r) >> 1;
			if (get(root[mid], 0, n - 1, l, r) >= k) {
				ans = mid, _r = mid - 1;
			}
			else {
				_l = mid + 1;
			}
		}
		cout << v[ans - 1].first << endl;
	}
}
