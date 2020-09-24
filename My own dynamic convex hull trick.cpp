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

struct hull {

	struct line {
		bool q;
		ld k, b, x, val;
		line(ld k = 0, ld b = 0) : x(-inf), q(0), k(k), b(b), val(0) {}

		inline bool parallel(const line &a) const { return (k == a.k); }
		inline ld inter(const line &a) const {
			if (parallel(a)) return inf;
			return (ld)((b - a.b) / (a.k - k));
		}
		inline ld eval(ld X) const { return (k * X + b); }
		inline bool operator < (const line &a) const {
			if (a.q) return (x < a.val);
			else return (k < a.k);
		}
	};

	set <line> st;
	typedef set <line>::iterator iter;

	inline bool hprev(iter &x) { return (x != st.begin()); }
	inline bool hnext(iter &x) { return (x != st.end() && next(x) != st.end()); }
	inline bool bad(const line &a, const line &b, const line &c) { return (a.inter(b) >= b.inter(c)); }

	inline bool bad(iter x) {
		if (!hprev(x) || !hnext(x)) return 0;
		return bad(*prev(x), *x, *next(x));
	}

	iter update(iter x) {
		if (!hprev(x)) return x;
		line temp = *x; temp.x = x->inter(*prev(x));
		x = st.erase(x); return st.insert(x, temp);
	}
	void add_line(ld k, ld b) {
		line cur(k, b);
		auto it = st.lower_bound(cur);
		if (it != st.end() && cur.parallel(*it)) {
			if (cur.b > it->b) it = st.erase(it);
			else return;
		}
		it = st.insert(it, cur);
		if (bad(it)) return (void)(st.erase(it));
		while (hprev(it) && bad(prev(it))) st.erase(prev(it));
		while (hnext(it) && bad(next(it))) st.erase(next(it));
		it = update(it);
		if (hprev(it)) update(prev(it));
		if (hnext(it)) update(next(it));
	}
	inline ld eval(ld f) {
		line cur(0, 0); cur.q = 1; cur.val = f;
		auto x = *--st.lower_bound(line(cur));
		return x.eval(f);
	}
};

vector <hull> ar;
vector <ll> ans, a, b;
vector < vector <int> > gr;

void dfs(int v, int p = -1) {
	int mx = -1;
	for (auto to : gr[v]) if (to != p) {
		dfs(to, v);
		if (mx == -1 || ar[to].st.size() > ar[mx].st.size()) mx = to;
	}
	if (mx != -1) swap(ar[v], ar[mx]);
	for (auto to : gr[v]) if (to != p && to != mx) {
		for (auto x : ar[to].st) ar[v].add_line(x.k, x.b);
	}
	ans[v] = (mx == -1 ? 0 : -ar[v].eval(a[v]));
	
//	cout << "Convex hull of vertex " << v + 1 << " is: " << ans[v] << '\n';
//	for (auto x : ar[v].st) cout << x.k << " * x + " << x.b << '\n';
//	cout << '\n';

	ar[v].add_line(-b[v], -ans[v]);
}

void solve() {
	int n;
	cin >> n;
	a.resize(n); b.resize(n);
	gr.resize(n); ar.resize(n); ans.resize(n);

	for (auto &i : a) cin >> i;
	for (auto &i : b) cin >> i;

	for (int i = 1; i < n; ++i) {
		int v, u;
		cin >> v >> u; --v; --u;
		gr[v].push_back(u); gr[u].push_back(v);
	}
	dfs(0);
	for (auto i : ans) cout << i << " ";
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
//	ifstream cin("input.txt");
//	ofstream cout("output.txt");
	int q = 1; // cin >> q;
	while (q--) solve();
}
