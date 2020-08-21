#include <bits/stdc++.h>
#define fi first
#define se second
#define ll long long
#define ld long double
#define all(x)              (x).begin(), (x).end()
#define inf                 1e18

using namespace std;

inline void sortt(vector <int> &p, vector <int> &c) {
	int n = p.size();
	vector <int> cnt(n), pos(n), ans(n);
	for (auto i : c) ++cnt[i];
	for (int i = 1; i < n; ++i) pos[i] = pos[i - 1] + cnt[i - 1];
	for (int i = 0; i < n; ++i) ans[pos[c[p[i]]]++] = p[i];
	swap(p, ans);
}

void solve() {
	string s; cin >> s; s += '$'; int n = s.size();

	vector <int> p(n), c(n);
	vector < pair <char, int> > v(n);
	for (int i = 0; i < n; ++i) v[i] = {s[i], i};

	sort(all(v));
	for (int i = 0; i < n; ++i) {
		p[i] = v[i].se;
		if (i) c[p[i]] = c[p[i - 1]] + (v[i].fi != v[i - 1].fi);
	}

	int k = 0;
	while ((1 << k) < n) {
		for (int i = 0; i < n; ++i) p[i] = (p[i] - (1 << k) + n) % n;
		sortt(p, c);
		vector <int> C(n);
		for (int i = 1; i < n; ++i) {
			pair <int, int> prev = {c[p[i - 1]], c[(p[i - 1] + (1 << k)) % n]};
			pair <int, int> next = {c[p[i]], c[(p[i] + (1 << k)) % n]};
			C[p[i]] = C[p[i - 1]] + (prev != next);
		}
		swap(c, C); ++k;
	}
	for (auto i : p) cout << i << " " << s.substr(i, n - i) << '\n';
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
//	ifstream cin("input.txt");
//	ofstream cout("output.txt");
	int q = 1; // cin >> q;
	while (q--) solve();
}
