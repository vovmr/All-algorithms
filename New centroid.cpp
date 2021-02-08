#include <bits/stdc++.h>
#define fi first
#define se second
#define ll long long
#define ld long double
#define all(x)              (x).begin(), (x).end()
#define inf                 1e18

using namespace std;

const int N = 1e5 + 5;

int sz[N];
int h[N], used[N];
vector < pair <int, ll> > gr[N];

void sizes(int v, int p) { sz[v] = 1;
	for (auto [to, w] : gr[v]) if (to != p && !used[to]) {
		sizes(to, v); sz[v] += sz[to];
	}
}

int centroid(int v, int p, int n) {
	for (auto [to, w] : gr[v]) if (to != p && !used[to] && sz[to] > n / 2) {
		return centroid(to, v, n);
	}
	return v;
}

struct bit {
	int n;
	vector <ll> f;
	bit(int n = 0) : n(n) { f.resize(n + 5); }
	void upd(int i, int x) { i += 2; for (; i < f.size(); i += i & -i) f[i] += x; }
	ll get(int i) { i += 2; ll ans = 0; for (; i > 0; i -= i & -i) { ans += f[i]; } return ans; }
};

ll L, W;
vector < pair <int, ll> > ar;

void dfs(int v, int p, int l, ll ww) {
	if (l > L || ww > W) return;

	ar.push_back({ww, l});
	for (auto [to, w] : gr[v]) if (to != p && !used[to]) {
		dfs(to, v, l + 1, w + ww);
	}
}

bit f(1e5 + 5);

ll solve1() {
	ll ans = 0;
	sort(all(ar));
	int l = 0, r = -1;
	for (; l < ar.size(); ++l) {
		while (r + 1 < l && ar[l].fi + ar[r + 1].fi <= W) { ++r; f.upd(ar[r].se, 1); }
		while (~r && ar[l].fi + ar[r].fi > W) { f.upd(ar[r].se, -1); --r; }
		ans += f.get(L - ar[l].se);
	}
	while (~r) { f.upd(ar[r].se, -1); --r; }
	ar.clear(); return ans;
}

ll dec(int v, int p, int n) {
	sizes(v, p); dfs(v, p, 0, 0); ll ans = solve1();
	for (auto [to, w] : gr[v]) if (to != p && !used[to]) { dfs(to, v, 1, w); ans -= solve1(); }

	used[v] = 1;
	for (auto [to, w] : gr[v]) if (to != p && !used[to]) {
		int c = centroid(to, v, sz[to]);
		ans += dec(c, v, sz[to]);
	}
	return ans;
}

void solve() {
	int n;
	cin >> n >> L >> W;
	for (int i = 1; i < n; ++i) {
		int v, w;
		cin >> v >> w; --v;
		gr[v].push_back({i, w});
		gr[i].push_back({v, w});
	}
	cout << dec(0, 0, n);
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
//	ifstream cin("input.txt");
//	ofstream cout("output.txt");
	int q = 1; // cin >> q;
	while (q--) solve();
}
