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

typedef complex <double> cd;

void fft(vector <cd> &ar) {
	int n = ar.size();
	vector <cd> w(n); w[0] = 1;
	for (double i = 1; i < n; ++i) {
		double a = 2.0 * 3.141592635897932384626433832895 * i / (double)n;
		w[i] = cd(cos(a), sin(a));
	}
	int lg = 0;
	while ((1 << lg) < n) ++lg;

	auto inv = [&](int x) {

		deque <int> bit;
		while (x) {
			bit.push_back(x & 1);
			x >>= 1;
		}
		while (bit.size() < lg) bit.push_back(0);

		int res = 0;
		for (int i = 0; i < lg; ++i) {
			res += (1 << (lg - i - 1)) * bit[i];
		}
		return res;
	};

	vector <cd> v(n);
	for (int i = 0; i < n; ++i) {
		v[i] = ar[inv(i)];
	}
	swap(v, ar);

	for (int len = 2; len <= n; len <<= 1) {
		int step = n / len;
		for (int i = 0; i < n; i += len) {
			for (int j = 0; j < len / 2; ++j) {
				cd a = ar[i + j], b = ar[i + j + (len / 2)] * w[j * step];
				ar[i + j] = a + b;
				ar[i + j + (len / 2)] = a - b;
			}
		}
	}
}

void inv(vector <cd> &ar) {
	double n = (double)ar.size(); fft(ar);
	reverse(ar.begin() + 1, ar.end());
	for (auto &i : ar) i /= n;
}

const int MOD = 1e6 + 3;

void solve() {
	
	int n = 131072;
	vector <cd> ar(2 * n), v(2 * n);
	for (int i = 0; i < n; ++i) {
		int x = rand() % MOD; ar[n + i] = x;
	}
	for (int i = 0; i < n; ++i) {
		int x = rand() % MOD; v[n + i] = x;
	}

	double cl = clock();

	fft(ar); fft(v);
	for (int i = 0; i < ar.size(); ++i) ar[i] *= v[i];
	inv(ar);

	cout << "Excution time: " << (clock() - cl) / (double)CLOCKS_PER_SEC;
	
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
