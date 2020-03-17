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

void fast_sort(vector <int> &p, vector <int> &c) {
	int n = p.size();
	vector <int> cnt(n), pos(n);
	for (int i = 0; i < n; ++i) {
		++cnt[c[i]];
	}
	for (int i = 1; i < n; ++i) {
		pos[i] = pos[i - 1] + cnt[i - 1];
	}
	vector <int> ar(n);
	for (int i = 0; i < n; ++i) {
		ar[pos[c[p[i]]]++] = p[i];
	}
	p = ar;
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
//	ifstream cin("input.txt");
//	ofstream cout("output.txt");
	string s;
	cin >> s; s += "$";
	int n = s.size();
	vector <int> p(n), c(n);
	{
		vector < pair <char, int> > v(n);
		for (int i = 0; i < n; ++i) {
			v[i] = {s[i], i};
		}
		sort(all(v));
		for (int i = 0; i < n; ++i) {
			p[i] = v[i].second;
		}
		for (int i = 1; i < n; ++i) {
			if (v[i].first == v[i - 1].first) {
				c[p[i]] = c[p[i - 1]];
			}
			else {
				c[p[i]] = c[p[i - 1]] + 1;
			}
		}
	}
	{
		int k = 0;
		while ((1 << k) < n) {
			for (int i = 0; i < n; ++i) {
				p[i] = (p[i] - (1 << k) + 2 * n) % n;
			}
			fast_sort(p, c);
			vector <int> C(n);
			for (int i = 1; i < n; ++i) {
				auto prev = make_pair(c[p[i - 1]], c[(p[i - 1] + (1 << k)) % n]);
				auto cur = make_pair(c[p[i]], c[(p[i] + (1 << k)) % n]);
				if (cur == prev) {
					C[p[i]] = C[p[i - 1]];
				}
				else {
					C[p[i]] = C[p[i - 1]] + 1;
				}
			}
			c = C; ++k;
		}
	}
	for (auto i : p) {
		cout << i << " " << s.substr(i, n - i) << '\n';
	}
}
