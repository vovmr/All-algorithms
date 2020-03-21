// Task from the BelOI 2019 1_3
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

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	ifstream cin("input.txt");
	ofstream cout("output.txt");
	int n, k;
	cin >> n >> k;
	vector <ll> v(n);
	for (auto &i : v) {
		cin >> i;
	}

	vector < vector <ll> > inv(n + 1, vector <ll> (n + 1));
	for (int l = 1; l <= n; ++l) {
		ll sum = 0;
		ordered_set <ll> st; st.insert(-v[l - 1]);
		for (int r = l + 1; r <= n; ++r) {
			inv[l][r] += sum + st.order_of_key(-v[r - 1]);
			sum += st.order_of_key(-v[r - 1]);
			st.insert(-v[r - 1]);
		}
	}

	ll l = 0, r = 1e7, mid, ans = 0;
	while (l <= r) {
		
		mid = (l + r) / 2.0;
		vector <int> cnt(n + 1);
		vector <ll> dp(n + 1, inf); dp[0] = 0;
		for (int i = 1; i <= n; ++i) {
			for (int j = 0; j < i; ++j) {
				if (dp[i] > dp[j] + inv[j + 1][i] + mid) {
					dp[i] = dp[j] + inv[j + 1][i] + mid;
					cnt[i] = cnt[j] + 1;
				}
			}
		}
		if (cnt[n] <= k) {
			ans = mid, r = mid - 1;
		}
		else {
			l = mid + 1;
		}

	}
	ll c = ans;
	vector <int> cnt(n + 1);
	vector <ll> dp(n + 1, inf); dp[0] = 0;
	for (int i = 1; i <= n; ++i) {
		for (int j = 0; j < i; ++j) {
			if (dp[i] > dp[j] + inv[j + 1][i] + c) {
				dp[i] = dp[j] + inv[j + 1][i] + c;
				cnt[i] = cnt[j] + 1;
			}
		}
	}
	cout << (ll)round(dp[n] - c * k);
}
