#include <bits/stdc++.h>
#define fi first
#define se second
#define ll long long
#define ld long double
#define all(x)              (x).begin(), (x).end()
#define inf                 1e18

using namespace std;

struct line {
	mutable ld k, b, x1;
	line(ld k, ld b, ld x1) : k(k), b(b), x1(x1) {}
	bool operator < (const line &a) const { return (k < a.k); }
	bool operator < (ld _x) const { return (x1 < _x); }
};
                 
struct Hull : multiset < line, less <> > {
	Hull() {}
	ld eval(ld x) {
		if (empty()) return -inf;
		auto it = *lower_bound(x);
		return (x * it.k + it.b);
	}
	bool intersect(iterator a, iterator b) {
		if (b == end()) { a->x1 = inf; return false; }
		if (a->k == b->k) a->x1 = (a->b > b->b ? inf : -inf);
		else a->x1 = (a->b - b->b) / (double)(b->k - a->k);
		return (a->x1 >= b->x1);
	}
	void insert_line(ld k, ld b) {
		auto it = insert(line(k, b, 0)), y = it++, x = y;
		while (intersect(y, it)) it = erase(it);
		if (x != begin() && intersect(--x, y)) intersect(x, y = erase(y));
		while ((y = x) != begin() && (--x)->x1 >= y->x1) intersect(x, erase(y));
	}
};

void solve() {
	int n, k;
	cin >> n >> k;
	vector <ll> v(n);
	for (auto &i : v) cin >> i;

	vector < vector <ll> > dp(n + 1, vector <ll> (k + 1, inf)); dp[0][0] = 0;

	for (int j = 0; j < k; ++j) {
		Hull cht;
		for (int i = 1; i <= n; ++i) {
			cht.insert_line(2 * v[i - 1], -v[i - 1] * v[i - 1] - dp[i - 1][j]);
			ll val = -cht.eval(v[i - 1]) + v[i - 1] * v[i - 1];
			dp[i][j + 1] = min(dp[i][j + 1], val);
		}
	}
	cout << dp[n][k];
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
//	ifstream cin("input.txt");
//	ofstream cout("output.txt");
	int q = 1; // cin >> q;
	while (q--) solve();
}
