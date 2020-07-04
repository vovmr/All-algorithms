/// find maximun clique in a graph in O(n * 2^(n / 2)) time
#include <bits/stdc++.h>
#define fi first
#define se second
#define ll long long
#define ld long double
#define all(x)              (x).begin(), (x).end()
#define inf                 1e18

using namespace std;

vector <ll> gr;

int maxClique() {
	int n = gr.size();
	int mid = (n / 2) + 1;
	vector <ll> dp(1 << mid);

	for (int mask = 0; mask < (1 << mid); ++mask) {
		bool ok = 1;
		for (int i = 0; i < mid; ++i) {
			if ((mask >> i) & 1) {
				ll M = gr[i] | (1LL << i);
				ok &= ((M & mask) == mask);
			}
		}
		if (ok) dp[mask] = __builtin_popcountll(mask);
	}
	for (int mask = 0; mask < (1 << mid); ++mask) {
		for (int i = 0; i < mid; ++i) {
			if ((mask >> i) & 1) {
				dp[mask] = max(dp[mask], dp[mask ^ (1 << i)]);
			}
		}
	}

	ll res = *max_element(all(dp));

	int left = n - mid;
	for (ll mask = 1; mask < (1 << left); ++mask) {
		bool clique = 1;
		for (int i = 0; i < left; ++i) {
			if ((mask >> i) & 1) {
				int j = mid + i;
				ll M = gr[j] | (1LL << j);
				ll newMask = (mask << mid);
				clique &= ((newMask & M) == newMask);
			}
		}
		if (clique) {
			ll adj = (1 << mid) - 1;
			for (int i = 0; i < left; ++i) {
				if ((mask >> i) & 1) {
					int j = mid + i;
					adj &= gr[j];
				}
			}
			res = max(res, __builtin_popcountll(mask) + dp[adj]);
		}
	}
	return (int)res;
}

void solve() {
	int n, k;
	cin >> n >> k; gr.resize(n);
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			ll x;
			cin >> x;
			gr[i] |= (1LL << j) * x;
		}
	}
	ld q = k, cl = maxClique();
	cout << fixed << setprecision(20) << ((q * q) * (cl - 1) / (2.0 * cl));
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
//	ifstream cin("input.txt");
//	ofstream cout("output.txt");
	int q = 1; // cin >> q;
	while (q--) solve();
}
