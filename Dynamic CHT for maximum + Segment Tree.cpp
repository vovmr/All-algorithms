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
        mutable ld k, b, x;
        line(ld k, ld b, ld x) : k(k), b(b), x(x) {}
        bool operator < (const line &a) const { return (k < a.k); }
        bool operator < (ld x1) const { return (x < x1); }
 
        ld get(ld x1) {
                return (k * x1 + b);
        }
};
 
struct Hull : multiset < line, less <> > {
        Hull() {}
        ld eval(ld x) {
        	if (empty()) return -inf;
                auto l = *lower_bound(x);
                return l.get(x);
        }
        bool isect(iterator a, iterator b) {
                if (b == end()) { a->x = inf; return false; };
                if (a->k == b->k) { a->x = ((a->b > b->b) ? inf : -inf); }
                else a->x = (ld)( (ld)(a->b - b->b) / (ld)(b->k - a->k) );
                return (a->x >= b->x);
        }
        void ins(ld k, ld b) {
                auto z = insert(line(k, b, 0)), y = z++, x = y;
                while (isect(y, z)) z = erase(z);
                if (x != begin() && isect(--x, y)) isect(x, y = erase(y));
                while ((y = x) != begin() && (--x)->x >= y->x) isect(x, erase(y));
        }
};

vector < Hull * > t;

void build(int v, int vl, int vr) {
	if (vl == vr) {
		t[v] = new Hull();
		return;
	}
	int m = (vl + vr) >> 1;
	build(2 * v + 1, vl, m);
	build(2 * v + 2, m + 1, vr);
	t[v] = new Hull();
}

void upd(int v, int vl, int vr, int pos, line cur) {
	t[v]->ins(cur.k, cur.b);
	if (vl == vr) return;

	int m = (vl + vr) >> 1;
	if (pos <= m) upd(2 * v + 1, vl, m, pos, cur);
	else upd(2 * v + 2, m + 1, vr, pos, cur);
}

ll eval(int v, int vl, int vr, int l, int r, ld x) {
	if (l > r) return inf;
	else if (vl == l && vr == r) return -t[v]->eval(x);
	int m = (vl + vr) >> 1;
	return min( eval(2 * v + 1, vl, m, l, min(r, m), x), eval(2 * v + 2, m + 1, vr, max(l, m + 1), r, x) );
}

void solve() {
	int n;
	cin >> n;

	t.resize(4 * n); build(0, 0, n - 1);

	vector <int> p(n);
	for (auto &i : p) { cin >> i; --i; }

	vector <ll> v(n);
	for (auto &i : v) cin >> i;

	vector <ll> h(n);
	for (auto &i : h) cin >> i;

	vector <ll> dp(n); dp[0] = v[0];

	auto insertL = [&](int i) {
		line w(2.0 * h[i], -dp[i] - h[i] * h[i], inf);
		upd(0, 0, n - 1, p[i], w);
	};

	insertL(0);

	for (int i = 1; i < n; ++i) {
		ld cur = eval(0, 0, n - 1, 0, p[i], h[i]);
		dp[i] = (ll)round(cur) + v[i] + h[i] * h[i];

		insertL(i);
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
