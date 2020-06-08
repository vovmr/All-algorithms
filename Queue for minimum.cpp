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

void solve() {
	int q;
	cin >> q;
	stack < pair <ll, ll> > s, s1;

	auto push = [&](ll x) {
		ll mn = ((s.empty()) ? x : min(s.top().se, x));
		s.push({x, mn});
	};
	auto get = [&]() {
		if (s.empty() || s1.empty()) return ((s.empty()) ? s1.top().se : s.top().se);
		return min(s.top().se, s1.top().se);
	};
	auto pop = [&]() {
		if (s1.empty()) {
			while (!s.empty()) {
				ll x = s.top().fi; s.pop();
				ll mn = ((s1.empty()) ? x : min(s1.top().se, x)); s1.push({x, mn});
			}
		}
		s1.pop();
	};

	while (q--) {
		char t;
		cin >> t;
		if (t == 'A') {
			ll x;
			cin >> x; push(x);
		}
		else if (t == 'E') pop();
		else cout << get() << '\n';
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
