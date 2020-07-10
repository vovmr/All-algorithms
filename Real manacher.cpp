#include <bits/stdc++.h>
#define fi first
#define se second
#define ll long long
#define ld long double
#define all(x)              (x).begin(), (x).end()
#define inf                 1e18

using namespace std;

string real_solve(string &s) {
	int n = s.size();
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

//	for (auto i : d) cout << i << " ";
//	cout << endl;
//	for (auto i : d1) cout << i << " ";
//	cout << endl;

	int mx = 0;
	string T = s; reverse(all(T));
	for (int i = 0; i < (n + 1) / 2; ++i) {
		if (s[i] != T[i]) break;
		++mx;
	}

	auto check = [&](int l, int r) {
		int len = r - l + 1;
		if (len & 1 ^ 1) {
			int mid = l + (len / 2);
			return (d[mid] >= (len / 2));
		}
		else {
			int mid = l + (len / 2);
			return (d1[mid] >= (len + 1) / 2);
		}
	};

	auto isect = [](int l, int r, int x) {
		return (l <= x && x <= r);
	};

	int L = 0;
	for (int len = 1; len <= n; ++len) {
		int l = mx, r = mx + len - 1;
		if (isect(n - mx, n - 1, r) || l >= n || r >= n || l > r) break;

		if (check(l, r)) L = max(L, len);
	}

	if (check(0, n - 1) || s.size() == 1) return s;

	string t = s.substr(0, mx + L);
	for (int i = n - mx; i < n; ++i) t += s[i];

	int mxpf = 0, mxsf = 0;
	for (int len = 1; len <= n; ++len) {
		if (check(0, len - 1)) mxpf = len;
		if (check(n - len, n - 1)) mxsf = len;
	}
	string h = "";
	if (mxpf > mxsf) h = s.substr(0, mxpf);
	else if (mxsf > mxpf || (mxsf == mxpf && mxpf != 0)) h = s.substr(n - mxsf, mxsf);

	if (h.size() > t.size()) swap(t, h);

	return t;
}

void solve() {
	string s; cin >> s;
	string t = s; reverse(all(t));
	string a = real_solve(s), b = real_solve(t);

	if (a.size() < b.size()) swap(a, b);
	cout << a << '\n';
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
//	ifstream cin("input.txt");
//	ofstream cout("output.txt");
	int q = 1; cin >> q;
	while (q--) solve();
}
