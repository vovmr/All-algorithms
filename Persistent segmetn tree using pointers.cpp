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

struct _tree {
	ll sum;
	_tree *l, *r;
	_tree() : l(nullptr), r(nullptr), sum(0) {}
	_tree(ll x) : l(nullptr), r(nullptr), sum(x) {}
	_tree(_tree *l, _tree *r) : l(l), r(r), sum(l->sum + r->sum) {}
};

vector <ll> ar;

_tree * build(int vl, int vr) {
	if (vl == vr) return new _tree(ar[vl]);
	int m = (vl + vr) >> 1;
	return new _tree(build(vl, m), build(m + 1, vr));
}

_tree * upd(_tree *v, int vl, int vr, int pos, ll x) {
	if (vl == vr) return new _tree(x);
	int m = (vl + vr) >> 1;
	if (pos <= m) return new _tree(upd(v->l, vl, m, pos, x), v->r);
	else return new _tree(v->l, upd(v->r, m + 1, vr, pos, x));
}

ll get(_tree *v, int vl, int vr, int l, int r) {
	if (l > r) return 0;
	else if (vl == l && vr == r) return v->sum;
	int m = (vl + vr) >> 1;
	return ( get(v->l, vl, m, l, min(r, m)) + get(v->r, m + 1, vr, max(l, m + 1), r) );
}

void solve() {
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
//	ifstream cin("input.txt");
//	ofstream cout("output.txt");
	int q = 1; cin >> q;
	while (q--) {
		solve();
	}
}
