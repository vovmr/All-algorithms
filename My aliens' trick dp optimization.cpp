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

void solve() {
	int n, k, l;
	cin >> n >> k >> l;
	string s; cin >> s;

	vector <ll> ar(n);
	for (int i = 0; i < n; ++i) ar[i] = isupper(s[i]);
	auto calc_dp = [&](ll lambda) {
		vector < pair <ll, ll> > dp(n + 1); dp[0] = {0, 0};
		for (int i = 1; i <= n; ++i) {
			dp[i] = {dp[i - 1].fi + ar[i - 1], dp[i - 1].se};
			if (i >= l) dp[i] = min(dp[i], {dp[i - l].fi + lambda, dp[i - l].se + 1});
			else dp[i] = min(dp[i], {lambda, 1});
		}
		return dp[n];
	};
	auto solve = [&]() {
		ll l = 0, r = 1e9, mid, ans = 0;
		while (l <= r) {
			mid = l + r >> 1;
			auto x = calc_dp(mid);
			if (x.se <= k) ans = mid, r = mid - 1;
			else l = mid + 1;
		}
		auto x = calc_dp(ans);
		return (x.fi - k * ans);
	};
	ll ans = solve();
	for (int i = 0; i < n; ++i) ar[i] ^= 1;
	cout << min(ans, solve());
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
//	ifstream cin("input.txt");
//	ofstream cout("output.txt");
	int q = 1; // cin >> q;
	while (q--) solve();
}
