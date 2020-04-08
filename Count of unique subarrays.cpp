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

void f(vector <int> &p, vector <int> &c) {
	int n = p.size();
	vector <int> cnt(n), pos(n), ans(n);
	for (auto i : c) ++cnt[i];
	for (int i = 1; i < n; ++i) pos[i] = pos[i - 1] + cnt[i - 1];
	for (int i = 0; i < n; ++i) ans[pos[c[p[i]]]++] = p[i];
	swap(p, ans);
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
//	ifstream cin("input.txt");
//	ofstream cout("output.txt");
	int n;
	cin >> n;
	vector <ll> s(n);
	for (auto &i : s) cin >> i;
	s.push_back(-inf), ++n;
	vector <int> p(n), c(n);
	{
		vector < pair <ll, int> > v(n);
		for (int i = 0; i < n; ++i) v[i] = {s[i], i};
		sort(all(v));
		for (int i = 0; i < n; ++i) p[i] = v[i].second;
		for (int i = 1; i < n; ++i) {
			c[p[i]] = c[p[i - 1]] + (v[i].first != v[i - 1].first);
		}
	}
	{
		int k = 0;
		while ((1 << k) < n) {
			for (auto &i : p) {
				i = (i - (1 << k) + n) % n;
			}
			f(p, c);
			vector <int> C(n);
			for (int i = 1; i < n; ++i) {
				auto prev = make_pair(c[p[i - 1]], c[ (p[i - 1] + (1 << k)) % n ]);
				auto next = make_pair(c[p[i]], c[ (p[i] + (1 << k)) % n ]);
				C[p[i]] = C[p[i - 1]] + (prev != next);	
			}
			swap(C, c), ++k;
		}
	}
	int k = 0;
	vector <int> lcp(n);
	for (int i = 0; i < n - 1; ++i) {
		int j = c[i]; int z = p[j - 1];
		while (s[i + k] == s[z + k]) ++k;
		lcp[j] = k; k = max(k - 1, 0);
	}
	ll ans = 0;
	for (int i = 0; i < n; ++i) {
		ans += (p[i] - lcp[p[i]]);
	}
	cout << ans;
}
