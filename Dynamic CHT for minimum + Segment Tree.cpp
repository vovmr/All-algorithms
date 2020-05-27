/// Codechef 'Jump race'

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

struct line {
	mutable ld k, b, x1;
	line(ld k, ld b, ld x1) : k(k), b(b), x1(x1) {}
	bool operator < (const line &a) const { return (k > a.k); }
	bool operator < (ld _x) const { return (x1 < _x); }
};
                 
struct Hull : multiset < line, less <> > {
	Hull() {}
	ld eval(ld x) {
		if (empty()) return inf;
		auto it = *lower_bound(x);
		return (x * it.k + it.b);
	}
	bool intersect(iterator a, iterator b) {
		if (b == end()) {
			a->x1 = inf;
			return false;
		}
		if (a->k == b->k) {
			a->x1 = (a->b < b->b ? inf : -inf);
		}
		else {
			a->x1 = (a->b - b->b) / (double)(b->k - a->k);
		}
		return (a->x1 >= b->x1);
	}
	void ins(ld k, ld b) {
		auto it = insert(line(k, b, 0)), y = it++, x = y;
		while (intersect(y, it)) {
			it = erase(it);
		}
		if (x != begin() && intersect(--x, y)) {
			intersect(x, y = erase(y));
		}
		while ((y = x) != begin() && (--x)->x1 >= y->x1) {
			intersect(x, erase(y));
		}
	}
};

vector < Hull * > t;

void build(int v, int vl, int vr) {
	t[v] = new Hull();
	if (vl == vr) return;
	int m = (vl + vr) >> 1;
	build(2 * v + 1, vl, m);
	build(2 * v + 2, m + 1, vr);
}

void upd(int v, int vl, int vr, int pos, line cur) {
	t[v]->ins(cur.k, cur.b);

	if (vl == vr) return;
	int m = (vl + vr) >> 1;
	if (pos <= m) upd(2 * v + 1, vl, m, pos, cur);
	else upd(2 * v + 2, m + 1, vr, pos, cur);
}

ld eval(int v, int vl, int vr, int l, int r, ld x) {
	if (l > r) return inf;
	else if (vl == l && vr == r) return t[v]->eval(x);
	int m = (vl + vr) >> 1;
	return min( eval(2 * v + 1, vl, m, l, min(r, m), x), eval(2 * v + 2, m + 1, vr, max(l, m + 1), r, x) );
}

void solve() {
	int n;
	cin >> n;

	t.resize(4 * n);
	build(0, 0, n - 1);

	vector < pair <int, int> > p(n);
	for (int i = 0; i < n; ++i) {
		int x;
		cin >> x; --x;
		p[i] = make_pair(x, i);
	}
	sort(all(p));

	vector <ld> v(n);
	for (auto &i : v) cin >> i;

	vector <ld> h(n);
	for (auto &i : h) cin >> i;

	vector <ll> dp(n);
	dp[p[0].se] = v[p[0].se];

	auto insertL = [&](int i) {
		line w(-2.0 * h[i], dp[i] + h[i] * h[i], inf);
		upd(0, 0, n - 1, i, w);
	};

	insertL(p[0].se);

	for (int i = 1; i < n; ++i) {
		int id = p[i].se;
		ld cur = eval(0, 0, n - 1, 0, id - 1, h[id]);
		dp[id] = (ll)round(cur) + v[id] + h[id] * h[id];

		if (cur == inf) {
			while (1) {
				cout << "1";
			}
		}

		insertL(id);
	}
	cout << dp[n - 1];
}

int main() {
        ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
//      freopen("input.txt", "r", stdin);
//      freopen("output.txt", "w", stdout);
        int q = 1; // cin >> q;
        while (q--) {
                solve();
        }
}
