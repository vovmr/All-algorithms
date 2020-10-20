#include <bits/stdc++.h>
#define fi first
#define se second
#define ll long long
#define ld long double
#define all(x)              (x).begin(), (x).end()
#define inf                 1e18
 
using namespace std;
 
#define sim template < class c
#define ris return * this
#define dor > debug & operator <<
#define eni(x) sim > typename \
  enable_if<sizeof dud<c>(0) x 1, debug&>::type operator<<(c i) {
sim > struct rge { c b, e; };
sim > rge<c> range(c i, c j) { return rge<c>{i, j}; }
sim > auto dud(c* x) -> decltype(cerr << *x, 0);
sim > char dud(...);
struct debug {
#ifdef LOCAL
~debug() { cerr << endl; }
eni(!=) cerr << boolalpha << i; ris; }
eni(==) ris << range(begin(i), end(i)); }
sim, class b dor(pair < b, c > d) {
  ris << "(" << d.first << ", " << d.second << ")";
}
sim dor(rge<c> d) {
  *this << "[";
  for (auto it = d.b; it != d.e; ++it)
	*this << ", " + 2 * (it == d.b) << *it;
  ris << "]";
}
#else
sim dor(const c&) { ris; }
#endif
};
#define imie(...) " [" << #__VA_ARGS__ ": " << (__VA_ARGS__) << "] "

struct DSU {
	ll ans = 0;
	int v, rnkv = 1, rv = 0, gv = 0;
	int u, rnku = 1, ru = 0, gu = 0;
	DSU(int v, int rnkv, int rv, int gv, int u, int rnku, int ru, int gu, ll ans) 
	: v(v), rnkv(rnkv), rv(rv), gv(gv), u(u), rnku(rnku), ru(ru), gu(gu), ans(ans) {}
};

struct dsu {
/// Solution to https://codeforces.com/contest/1140/problem/F
/// we maintain usual DSU, but also
/// we'll need to somehow do rollbacks(undo the last operation)
/// In order to do that, we can notice, that at most two vertices change their parents, rank and some other information
/// Thus we can keep a stack of operations, that change our DSU(we maintain the previous states for these vertices)

/// Then transform all queries in form "some edge exist on [l; r] time segment"
/// Run DFS on our segment tree, when entering a node, apply all operations, when leaving a node, do all the rollbacks
	ll ans = 0;
	stack <DSU> oper;
	vector <ll> p, rnk, r, g;
	dsu(int n = 0) { p.resize(n); r.resize(n); g.resize(n); rnk.resize(n); }

	void make(int v, int f) { p[v] = v, rnk[v] = 1; r[v] = f, g[v] = !f; }
	int par(int v) { if (p[v] == v) { return v; } return par(p[v]); }

	bool unite(int a, int b) {
		a = par(a), b = par(b);
		if (a == b) return 0;

		if (rnk[a] > rnk[b]) swap(a, b);
		oper.push(DSU(a, rnk[a], r[a], g[a], b, rnk[b], r[b], g[b], ans));

		ans -= r[a] * g[a] + r[b] * g[b];
		ans += (r[a] + r[b]) * (g[a] + g[b]);

		p[a] = b, rnk[b] += rnk[a]; r[b] += r[a], g[b] += g[a];
		return 1;
	}

	void rick_roll() {
		if (oper.empty()) return;
		auto x = oper.top(); oper.pop();

		ans = x.ans;
		p[x.v] = x.v, r[x.v] = x.rv, g[x.v] = x.gv, rnk[x.v] = x.rnkv;
		p[x.u] = x.u, r[x.u] = x.ru, g[x.u] = x.gu, rnk[x.u] = x.rnku;
	}
};

struct query {
	int v, u, ok = 0;
	query(int v, int u) : v(v), u(u) {}
};

struct SegmentTree {
	dsu f;
	vector < vector <query> > t;

	SegmentTree(int _t, int n) {
		f = dsu(n);
		t.resize(4 * _t);
	}

	void upd(int v, int vl, int vr, int l, int r, query &x) {
		if (l > r) return;
		else if (vl == l && vr == r) { t[v].push_back(x); return; }
		int m = vl + vr >> 1;
		upd(2 * v + 1, vl, m, l, min(r, m), x);
		upd(2 * v + 2, m + 1, vr, max(l, m + 1), r, x);
	}

	void answer(int v, int vl, int vr, vector <ll> &ans) {
		for (auto &x : t[v]) x.ok = f.unite(x.v, x.u);
		if (vl == vr) ans[vl] = f.ans;
		else {
			int m = vl + vr >> 1;
			answer(2 * v + 1, vl, m, ans);
			answer(2 * v + 2, m + 1, vr, ans);
		}
		for (auto x : t[v]) if (x.ok) f.rick_roll();
	}
};
 
void solve() {
	int n;
	cin >> n;
	map <int, int> a, b;
	vector < pair <int, int> > v(n);

	for (int i = 0; i < n; ++i) {
		cin >> v[i].fi >> v[i].se;
		++a[v[i].fi], ++b[v[i].se];
	}

	int c = 0;
	for (auto &x : a) x.se = c++;
	for (auto &x : b) x.se = c++;

	int m = c;
	SegmentTree st(n, m);
	for (auto x : a) st.f.make(x.se, 0);
	for (auto x : b) st.f.make(x.se, 1);

	map < pair <int, int>, int > lst;

	for (int i = 0; i < n; ++i) {
		if (lst.count(v[i])) {
			query u(a[v[i].fi], b[v[i].se]);
			st.upd(0, 0, n - 1, lst[v[i]], i - 1, u); lst.erase(v[i]);
		}
		else lst[v[i]] = i;
	}
	for (auto [a1, b1] : lst) {
		auto [v, u] = a1; v = a[v], u = b[u]; query f(v, u);
		st.upd(0, 0, n - 1, b1, n - 1, f);
	}

	vector <ll> ans(n);
	st.answer(0, 0, n - 1, ans);
	for (auto i : ans) cout << i << " ";
}
 
int main() {
	ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
//	ifstream cin("input.txt");
//	ofstream cout("output.txt");
	int q = 1; // cin >> q;
	while (q--) solve();
}
