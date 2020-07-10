#include <bits/stdc++.h>
#define fi first
#define se second
#define ll long long
#define ld long double
#define all(x)              (x).begin(), (x).end()
#define inf                 1e18

using namespace std;

void solve() {
	string s; cin >> s; int n = s.size();

	vector <int> d(n), d1(n);
	for (int i = 0, l = 0, r = -1; i < n; ++i) {
		int k = ((i > r) ? 1 : min(r - i + 1, d1[l + r - i]));
		while (i - k >= 0 && i + k < n && s[i - k] == s[i + k]) ++k;

		d1[i] = k--;
		if (i + k > r) l = i - k, r = i + k;
	}
	for (int i = 0, l = 0, r = -1; i < n; ++i) {
		int k = ((i > r) ? 0 : min(r - i + 1, d[l + r - i + 1]));
		while (i - k - 1 >= 0 && i + k < n && s[i - k - 1] == s[i + k]) ++k;

		d[i] = k--;
		if (i + k > r) l = i - k - 1, r = i + k;
	}
	for (auto i : d) cout << i << " ";
	cout << '\n';
	for (auto i : d1) cout << i << " ";
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
//	ifstream cin("input.txt");
//	ofstream cout("output.txt");
	int q = 1; // cin >> q;
	while (q--) solve();
}
