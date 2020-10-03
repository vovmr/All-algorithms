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

struct cht {
	struct line {
		ld k, b, x, q;
		line() : x(-inf), k(0), b(0), q(0) {}
		line(ld k, ld b) : x(-inf), k(k), b(b), q(0) {}

		inline ld eval(ld X) const { return k * X + b; }
		inline bool parallel(const line &cur) const { return k == cur.k; }
		inline ld isec(line cur) const { return (parallel(cur) ? inf : ((b - cur.b) / (cur.k - k))); }
		inline bool operator < (const line &a) const {
			if (a.q) return x < a.x;
			else return k < a.k;
		}
	};

	set <line> st;
	typedef set <line>::iterator iter;

	inline bool hp(iter x) { return x != st.begin(); }
	inline bool hn(iter x) { return (x != st.end() && next(x) != st.end()); }
	inline bool bad(const line &a, const line &b, const line &c) { return (a.isec(b) >= b.isec(c)); }
	inline bool bad(iter x) {
		if (!hp(x) || !hn(x)) return 0;
		return bad(*prev(x), *x, *next(x));
	}

	inline iter update(iter x) {
		if (!hp(x)) return x;
		line f = *x; f.x = x->isec(*prev(x));
		x = st.erase(x); return (st.insert(x, f));
	}
	inline void add(ld k, ld b) {
		line cur(k, b); auto it = st.lower_bound(cur);
		if (it != st.end() && cur.parallel(*it)) {
			if (cur.b > it->b) it = st.erase(it);
			else return;
		}
		it = st.insert(it, cur);
		if (bad(it)) return (void)(st.erase(it));
		while (hp(it) && bad(prev(it))) st.erase(prev(it));
		while (hn(it) && bad(next(it))) st.erase(next(it));
		it = update(it);
		if (hp(it)) update(prev(it));
		if (hn(it)) update(next(it));
	}
	inline ld eval(ld x) {
		line cur; cur.x = x; cur.q = 1;
		auto it = *--st.lower_bound(cur);
		return it.eval(x);
	}
};

void solve() {
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
//	ifstream cin("input.txt");
//	ofstream cout("output.txt");
	int q = 1; // cin >> q;
	while (q--) solve();
}
