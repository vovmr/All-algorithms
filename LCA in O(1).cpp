#include <bits/stdc++.h>
#define fi first
#define se second
#define ll long long
#define ld long double
#define all(x)              (x).begin(), (x).end()
#define inf                 1e18

using namespace std;

#define sim template < class c
#define ris return * this
#define dor > debug & operator <<
#define eni(x) sim > typename \
  enable_if<sizeof dud<c>(0) x 1, debug&>::type operator<<(c i) {
sim > struct rge { c b, e; };
sim > rge<c> range(c i, c j) { return rge<c>{i, j}; }
sim > auto dud(c* x) -> decltype(cerr << *x, 0);
sim > char dud(...);
struct debug {
#ifdef LOCAL
~debug() { cerr << endl; }
eni(!=) cerr << boolalpha << i; ris; }
eni(==) ris << range(begin(i), end(i)); }
sim, class b dor(pair < b, c > d) {
  ris << "(" << d.first << ", " << d.second << ")";
}
sim dor(rge<c> d) {
  *this << "[";
  for (auto it = d.b; it != d.e; ++it)
	*this << ", " + 2 * (it == d.b) << *it;
  ris << "]";
}
#else
sim dor(const c&) { ris; }
#endif
};
#define imie(...) " [" << #__VA_ARGS__ ": " << (__VA_ARGS__) << "] "

string y;

vector <int> d, d1;
vector < pair <int, int> > eul;
vector < vector <int> > gr;

void dfs(int v, int h, int p = 0) {
	if (!v) {
		d[v] = (y[v] == 'H');
		d1[v] = (y[v] == 'G');
	}
	eul.push_back({h, v});
	for (auto to : gr[v]) if (to != p) {
		d[to] = d[v] + (y[to] == 'H');
		d1[to] = d1[v] + (y[to] == 'G');
		dfs(to, h + 1, v); eul.push_back({h, v});
	}
}

void solve() {
	ifstream cin("milkvisits.in");
	ofstream cout("milkvisits.out");

	int n, m;
	cin >> n >> m >> y;
	gr.resize(n); d.resize(n); d1.resize(n);

	for (int i = 1; i < n; ++i) {
		int v, u;
		cin >> v >> u; --v; --u;
		gr[v].push_back(u); gr[u].push_back(v);
	}
	dfs(0, 0);
	int k = eul.size();
	vector <int> lg(k + 1);
	for (int i = 2; i <= k; ++i) lg[i] = lg[i >> 1] + 1;

	int LG = lg[k];
	vector < vector < pair <int, int> > > s(k, vector < pair <int, int> > (LG + 1));

	for (int i = 0; i < k; ++i) s[i][0] = eul[i];
	for (int p = 1; p <= LG; ++p) {
		for (int i = 0; i + (1 << p) <= k; ++i) {
			s[i][p] = min(s[i][p - 1], s[i + (1 << (p - 1))][p - 1]);
		}
	}

	vector <int> fir(n, -1);
	for (int i = 0; i < k; ++i) if (fir[eul[i].se] == -1) fir[eul[i].se] = i;

	auto lca = [&](int v, int u) {
		v = fir[v], u = fir[u];
		if (v > u) swap(v, u);

		int len = lg[u - v + 1];
		auto x = min(s[v][len], s[u - (1 << len) + 1][len]); return x.se;
	};

	while (m--) {
		int v, u; char c; cin >> v >> u >> c; --v; --u;

		int lc = lca(v, u), ans = 0;
		if (c == 'H') ans = d[v] + d[u] - 2 * d[lc] + (y[lc] == 'H');
		else ans = d1[v] + d1[u] - 2 * d1[lc] + (y[lc] == 'G');
		cout << (ans ? 1 : 0);
	}
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
//	ifstream cin("input.txt");
//	ofstream cout("output.txt");
	int q = 1; // cin >> q;
	while (q--) solve();
}
