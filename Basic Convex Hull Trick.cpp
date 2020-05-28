/// Codeforces 320E
/// Convex Hull Trick ( this works only if all the lines are sorted by slope )

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
	ld k, b, x;
	line() : k(0), b(0), x(inf) {}
	line(ld k, ld b) : k(k), b(b), x(inf) {}

	ld get(ld X) { return (k * X + b); }
};

ld inter(line a, line b) {
	return (ld)( (b.b - a.b) / (ld)(a.k - b.k) );
}

vector <line> st;

ld eval(ld x) {
	int l = 0, r = st.size() - 1, mid;
	while (l < r) {
		mid = (l + r) >> 1;
		if (st[mid].x >= x) r = mid;
		else l = mid + 1;
	}
	return st[r].get(x);
}

void insertL(line cur) {
	if (st.size() == 0) {
		st.push_back(cur);
		return;
	}
	while (st.size() >= 2) {
		line F = st.back(), G = st[st.size() - 2];
		if (inter(F, G) >= inter(cur, G)) st.pop_back();
		else break;
	}
	st.back().x = inter(st.back(), cur); st.push_back(cur);
}

void solve() {
	int n;
	cin >> n;
	vector <ll> v(n), ar(n);
	for (auto &i : v) cin >> i;
	for (auto &i : ar) cin >> i;

	vector <ll> dp(n);
	for (int i = 0; i < n; ++i) {
		if (i) dp[i] = eval(v[i]);
		insertL(line(ar[i], dp[i]));
	}
	cout << dp[n - 1] << '\n';
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
