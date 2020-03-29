// solution to 932F on Codeforces

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

struct line {
	mutable ld k, b, x1;
	line(ld k, ld b, ld x1) : k(k), b(b), x1(x1) {}
	bool operator < (const line &a) const { return (k < a.k); }
	bool operator < (ld _x) const { return (x1 < _x); }
};
                 
struct DynamicHull : multiset < line, less <> > {
	DynamicHull() {}
	ld get(ld x) {
		auto it = *lower_bound(x);
		return (x * it.k + it.b);
	}
	bool intersect(iterator a, iterator b) {
		if (b == end()) {
			a->x1 = inf;
			return false;
		}
		if (a->k == b->k) {
			a->x1 = (a->b > b->b ? inf : -inf);
		}
		else {
			a->x1 = (a->b - b->b) / (double)(b->k - a->k);
		}
		return (a->x1 >= b->x1);
	}
	void __insert(ld k, ld b) {
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

vector <ll> a, b, dp;
vector < vector <int> > gr;
vector < DynamicHull * > dh;

void dfs_for_anses(int v, int p) {
	int mx = -1;
	for (auto to : gr[v]) {
		if (to != p) {
			dfs_for_anses(to, v);
			if (mx == -1 || dh[to]->size() > dh[mx]->size()) {
				mx = to;
				dh[v] = dh[to];
			}
		}
	}
	if (mx == -1) {
		dh[v] = new DynamicHull();
	}
	for (auto to : gr[v]) {
		if (to != mx && to != p) {
			for (auto x : *dh[to]) {
				dh[v]->__insert(x.k, x.b);
			}
		}
	}
	dp[v] = ((mx == -1) ? 0 : -dh[v]->get(a[v]));
	dh[v]->__insert(-b[v], -dp[v]);
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
//	ifstream cin("input.txt");
//	ofstream cout("output.txt");
	int n;
	cin >> n;
	gr.resize(n); a.resize(n); b.resize(n); dh.resize(n); dp.resize(n);
	for (auto &i : a) {
		cin >> i;
	}
	for (auto &i : b) {
		cin >> i;
	}
	for (int i = 0; i < n - 1; ++i) {
		int v, u;
		cin >> v >> u; --v; --u;
		gr[v].push_back(u);
		gr[u].push_back(v);
	}
	dfs_for_anses(0, 0);
	for (auto i : dp) {
		cout << i << " ";
	}
}
