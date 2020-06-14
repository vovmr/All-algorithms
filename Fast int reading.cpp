#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

#pragma GCC optimize("-O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")

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

int getint() { /// can read int or long long faster that scanf
	bool minus = false;
	int result = 0;
	char ch;
	ch = getchar();

	while (true) {
		if (ch == '-') break;
		if (ch >= '0' && ch <= '9') break;
		ch = getchar();
	}
	if (ch == '-') minus = true;
	else result = ch - '0';
	while (true) {
		ch = getchar();
		if (ch < '0' || ch > '9') break;
		result = result * 10 + (ch - '0');
	}
	if (minus) return -result;
	else return result;
}

int ar[1001][1001];

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
//	ifstream cin("input.txt");
//	ofstream cout("output.txt");

	int n, m;
	n = getint(); m = getint();
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			ar[i][j] = getint();
		}
	}
	vector < vector <int> > pf(n, vector <int> (m));
	for (int j = 0; j < m; ++j) {
		for (int i = 0; i < n; ++i) {
			pf[i][j] = ar[i][j];
			if (i) pf[i][j] += pf[i - 1][j];
		}
	}

	ll res = -inf;
	pair <int, int> x = {0, 0}, y = {0, 0};

	for (int l = 0; l < n; ++l) {
		for (int r = l; r < n; ++r) {
			
			vector <int> p(m);
			for (int i = 0; i < m; ++i) p[i] = pf[r][i] - ((l == 0) ? 0 : pf[l - 1][i]);

			ll L = 0, R = 0, ans = p[0], sum = 0, mn = 0, pos_mn = -1;
			for (int i = 0; i < m; ++i) {
				sum += p[i];
				if (ans < sum - mn) {
					L = pos_mn + 1, R = i, ans = sum - mn;
				}
				if (mn > sum) {
					mn = sum, pos_mn = i;
				}
			}

//			cout << l + 1 << " " << r + 1 << " " << L + 1 << " " << R + 1 << '\n';
//			for (auto i : p) cout << i << " ";
//			cout << '\n' << ans << '\n' << '\n';

			if (ans > res) {
				x = {l, L}, y = {r, R};
				res = ans;
			}
		}
	}
	cout << x.fi + 1 << " " << x.se + 1 << '\n' << y.fi + 1 << " " << y.se + 1;
}
