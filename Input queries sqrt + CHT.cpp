#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("avx,avx2,fma")

#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#define fi first
#define se second
#define ll long long
#define ld long double
#define all(x)              (x).begin(), (x).end()
#define inf                 3e18

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

const int N = 3e5 + 1;
const int block = 2500;

ll ans[N];
bool del[N], dele[N];

struct query {
	int t, a, b;
	query() : t(0), a(0), b(0) {}
	query(int t, int a, int b) : t(t), a(a), b(b) {}
};

void solve() {
    
    for (auto &i : dele) i = 1;
    
	int n;
	cin >> n;
	vector <query> q(n);
	for (int i = 0; i < n; ++i) {
		int t, a, b;
		cin >> t >> a;
		if (t == 1) cin >> b;

		q[i] = query(t, a - (t == 2), b);
	}
	for (int l = 0; l < n; l += block) {
		int r = min(n - 1, l + block - 1);

		Hull *cht = new Hull();

        for (int i = 0; i < n; ++i) del[i] = 0;
		for (int i = 0; i <= r; ++i) {
			if (q[i].t == 2) del[q[i].a] = 1;
		}
		for (int i = 0; i < l; ++i) {
			if (q[i].t == 1 && !del[i]) cht->ins(q[i].a, q[i].b);
		}
		for (int i = l; i <= r; ++i) {
			if (q[i].t == 3) {
				ll x = q[i].a;

				ans[i] = -inf;
				if (!cht->empty()) ans[i] = cht->eval(x);
				for (int j = l; j <= r; ++j) {
					if (q[j].t == 1 && !dele[j]) {
						ans[i] = max(ans[i], q[j].a * x + q[j].b);
					}
					else if (q[j].t == 2 && !dele[q[j].a]) {
						ans[i] = max(ans[i], q[q[j].a].a * x + q[q[j].a].b);
					}
				}
			}
			else if (q[i].t == 1) {
				dele[i] = 0;
			}
			else if (q[i].t == 2) {
				dele[q[i].a] = 1;
			}
		}
		cht->clear();
		delete cht;
	}
	for (int i = 0; i < n; ++i) {
		if (q[i].t == 3) {
			if (ans[i] == -inf) {
				cout << "EMPTY SET" << '\n';
			}
			else {
				cout << ans[i] << '\n';
			}
		}
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
