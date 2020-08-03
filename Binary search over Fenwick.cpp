#include <bits/stdc++.h>
#define fi first
#define se second
#define ll long long
#define ld long double
#define all(x)              (x).begin(), (x).end()
#define inf                 1e18

using namespace std;

vector <ll> f;
void upd(int i, ll x) { for (; i < f.size(); i += i & -i) f[i] += x; }
ll sum(int i) { ll ans = 0; for (; i; i -= i & -i) { ans += f[i]; } return ans; }

int dix(ll x) {
	ll s = 0, pos = 0;
	for (int i = 21; ~i; --i) {
		if (pos + (1 << i) < f.size() && s + f[pos + (1 << i)] < x) {
			pos += (1 << i);
			s += f[pos];
		}
	}
	return pos + 1;
}

void solve() {
	int n, q;
	cin >> n >> q;
	f.resize(n + 10);
	for (int i = 0; i < n; ++i) {
		int x;
		cin >> x;
		upd(x, 1);
	}
	while (q--) {
		int x;
		cin >> x;
		if (x > 0) upd(x, 1);
		else upd(dix(-x), -1);
	}
	ll s = sum(f.size() - 1);
	cout << ((!s) ? 0 : dix(1));
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
//	ifstream cin("input.txt");
//	ofstream cout("output.txt");
	int q = 1; // cin >> q;
	while (q--) solve();
}
