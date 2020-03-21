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
using ordered_set = tree <T, null_type, less_equal <T>, rb_tree_tag, tree_order_statistics_node_update>;

struct DynamicCHT {

	struct line {
	       	bool q; ld x;
	       	ll k, b, val;
	       	line(ll k = 0, ll b = 0) : k(k), b(b), x(-inf), q(false), val(0) {}
	       	bool operator < (const line &a) const {
	       		if (a.q) {
       				return x < a.val;
       			}
	       		else {
       				return (k < a.k);
       			}
       		}
	       	bool parallel(const line &a) const {
       			return (k == a.k);
	       	}
       		ld intersection(const line &a) const {
	       		if (parallel(a)) return inf;
       			return ((double)(b - a.b) / (double)(a.k - k));
       		}
	       	ld getv(ll x) const {
       			return (k * x + b);
       		}
	};

	set <line> st;
	typedef set <line>::iterator iter;

	DynamicHull() {}

	bool hPrev(iter a) { return (a != st.begin()); }
	bool hNext(iter a) { return (a != st.end() && next(a) != st.end()); }
	bool bad(const line &a, const line &b, const line &c) {
		return (a.intersection(c) <= a.intersection(b));
	}
	bool bad(iter it) {
		return (hPrev(it) && hNext(it) && bad(*prev(it), *it, *next(it)));
	}

	iter update(iter it) {
		if (!hPrev(it)) {
			return it;
		}
		ld x = it->intersection(*prev(it));
		line temp(*it); temp.x = x;
		it = st.erase(it);
		return st.insert(it, temp);
	}
	void add_line(ll k, ll b) {
		line cur = line(k, b);
		iter it = st.lower_bound(cur);
		if (it != st.end() && cur.parallel(*it)) {
			if (cur.b > it->b) {
				it = st.erase(it);
			}
			else {
				return;
			}
		}
		it = st.insert(it, cur);
		if (bad(it)) {
			return (void)st.erase(it);
		}
		while (hPrev(it) && bad(prev(it))) st.erase(prev(it));
		while (hNext(it) && bad(next(it))) st.erase(next(it));
		it = update(it);
		if (hPrev(it)) update(prev(it));
		if (hNext(it)) update(next(it));
	}
	ld query(ld x) {
		if (st.empty()) return 0.5;
		line cur; cur.q = 1, cur.val = x;
		return (--st.lower_bound(cur))->getv(x);
	}

};

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
//	ifstream cin("input.txt");
//	ofstream cout("output.txt");
	int n;
	cin >> n;
	int id = 0;
	vector < pair <int, int> > q(n + 1);
	DynamicCHT *cht = new DynamicCHT();
	while (n--) {
		int t;
		cin >> t;
		if (t == 1) {
			ld x, y;
			cin >> x >> y;
			cht->add_line(x, y);
		}
		else {
			ld x;
			cin >> x;
			ld ans = cht->query(x);
			if (ans == 0.5) {
				cout << "EMPTY SET" << '\n';
			}
			else {
				cout << ans << '\n';
			}
		}
		++id;
	}
}
