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

#define mp make_pair

int ti = 0;

vector <int> used;
vector <int> in, f, comp, cnt;
vector < vector <int> > gr, gt;

map < pair <int, int>, bool > has;
map < pair <int, int>, bool > bridges;

void dfs(int v, int p = -1) {
	used[v] = 1;
	in[v] = f[v] = ++ti;
	for (auto to : gr[v]) {
		if (to == p) continue;
		if (!used[to]) {
			dfs(to, v);
			f[v] = min(f[v], f[to]);
			if (f[to] > in[v]) bridges[mp(v, to)] = bridges[mp(to, v)] = 1;
		}
		else f[v] = min(f[v], in[to]);
	}
}

void dye(int v, int c) {
	used[v] = 1; comp[v] = c;

	for (auto to : gr[v]) {
		if (bridges[mp(v, to)]) continue;
		if (has[mp(v, to)] || has[mp(to, v)]) ++cnt[c];

		if (used[to]) continue;
		dye(to, c);
	}
}

void rebuild() {
	int C = 0;
	used.assign(used.size(), 0);
	for (int i = 0; i < gr.size(); ++i) {
		if (used[i]) continue;
		dye(i, C); ++C;
	}

	gt.resize(C);
	for (int i = 0; i < gr.size(); ++i) {
		for (auto to : gr[i]) {
			if (!bridges[mp(i, to)] || !bridges[mp(to, i)]) continue;
			gt[comp[i]].push_back(comp[to]);
			gt[comp[to]].push_back(comp[i]);
		}
	}
	for (auto &i : gt) {
		sort(all(i));
		i.erase(unique(all(i)), i.end());
	}
	swap(gr, gt);
	used.assign(used.size(), 0);
}

vector <int> par;

void assign(int v, int p = -1) {
	par[v] = p;
	for (auto to : gr[v]) {
		if (to != p) assign(to, v);
	}
}

int get(int v, int u, int have) {
	if (v == u) {
		cout << (have ? "YES" : "NO");
		exit(0);
	}
	used[v] = 1;
	for (auto to : gr[v]) {
		if (!used[to]) {
			int have1 = have + cnt[to] + has[mp(v, to)];
			get(to, u, have1);
		}
	}
}

void solve() {
	int n, m;
	cin >> n >> m;
	gr.resize(n); comp.resize(n); f.resize(n);
	in.resize(n); par.resize(n); cnt.resize(n); used.resize(n);

	for (int i = 0; i < m; ++i) {
		int v, u, c;
		cin >> v >> u >> c; --v; --u;
		gr[v].push_back(u); gr[u].push_back(v);
		if (c == 1) has[mp(v, u)] = has[mp(u, v)] = 1;
	}

	dfs(0);
	debug() << imie(bridges) imie(has);

	rebuild();
	assign(0, 0);

	int a, b;
	cin >> a >> b; --a; --b;
	a = comp[a], b = comp[b];

	debug() << imie(comp) imie(cnt);

	map < pair <int, int>, bool > has1 = has; has.clear();
	for (auto &[a, b] : bridges) {
		if (!has1[mp(a.fi, a.se)]) continue;
		int v = comp[a.fi], u = comp[a.se];
		has[mp(v, u)] = has[mp(u, v)] = 1;
	}
	get(a, b, cnt[a]);
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
//	ifstream cin("input.txt");
//	ofstream cout("output.txt");
	int q = 1; // cin >> q;
	while (q--) solve();
}
