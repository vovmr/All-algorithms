#include <bits/stdc++.h>
#define fi first
#define se second
#define ll long long
#define ld long double
#define all(x)              (x).begin(), (x).end()
#define inf                 1e18

using namespace std;

const int N = 5e6 + 5;
int c[N][2]; int w = 0;
int p[N], e[N];

void add(ll x) {
	int v = 0;
	for (ll i = 34 - 1; i >= 0; --i) {
		ll bit = ((x >> i) & 1);
		if (c[v][bit] == -1) {
			c[v][bit] = ++w;
			p[w] = v;
		}	
		v = c[v][bit];
	}
	++e[v];
}

ll find(ll x) {
	int v = 0; ll ans = 0;
	for (ll i = 34 - 1; i >= 0; --i) {
		ll bit = ((x >> i) & 1) ^ 1;
		if (c[v][bit] != -1) {
			ans += (1LL << i);
			v = c[v][bit];
		}
		else v = c[v][bit ^ 1];
	}
	return ans;
}

void erase(ll x) {
	int v = 0;
	for (ll i = 34 - 1; i >= 0; --i) {
		ll bit = ((x >> i) & 1);
		v = c[v][bit];
	}
	if (e[v] > 1) {
		--e[v]; return;
	}
	e[v] = 0;
	while (1) {
		if (c[v][0] != -1 || c[v][1] != -1 || p[v] == -1 || p[v] == v) break;

		int par = p[v]; bool lf = (c[par][0] == v); p[v] = -1;
		if (lf) { c[par][0] = -1; v = par; }
		else { c[par][1] = -1; v = par; }
	}
}

void solve() {

	for (int i = 0; i < N; ++i) {
		c[i][0] = c[i][1] = -1;
	}
	memset(p, -1, sizeof(p));
	memset(e, 0, sizeof(e));

	add(0);

	int q;
	cin >> q;
	while (q--) {
		ll x;
		char t;
		cin >> t >> x;
		if (t == '+') add(x);
		else if (t == '-') erase(x);
		else cout << find(x) << '\n';
	}
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
//	ifstream cin("input.txt");
//	ofstream cout("output.txt");
	int q = 1; // cin >> q;
	while (q--) solve();
}
