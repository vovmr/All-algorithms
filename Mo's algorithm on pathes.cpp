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

constexpr int block = 401;

struct query {
	int l, r, id, need, c;
	query() : l(0), r(0), id(0), need(-1), c(0) {}
	query(int l, int r, int id, int need, int c) : l(l), r(r), id(id), need(need), c(c) {}

	inline pair <int, int> toPair() const {
		return { l / block, (((l / block) & 1) ? -r : r) };
	}
};

bool operator < (const query &a, const query &b) {
	return (a.toPair() < b.toPair());
}

int ti = 0, lg;

vector <int> h, ar, ord, in, out, st, en;
vector < vector <int> > gr, up;

void dfs(int v, int _h, int p = 0) {
	h[v] = _h;
	st[v] = ord.size(); ord.push_back(v);

	up[v][0] = p; in[v] = ++ti;
	for (int i = 1; i <= lg; ++i) up[v][i] = up[up[v][i - 1]][i - 1];

	for (auto to : gr[v]) if (to != p) {
		dfs(to, _h + 1, v);
	}
	out[v] = ++ti;
	en[v] = ord.size(); ord.push_back(v);
}

bool anc(int a, int b) {
	return (in[a] <= in[b] && out[b] <= out[a]);
}

int lca(int a, int b) {
	if (anc(a, b)) return a;
	if (anc(b, a)) return b;
	for (int i = lg; ~i; --i) {
		if (!anc(up[a][i], b)) {
			a = up[a][i];
		}
	}
	return up[a][0];
}

inline query make(int v, int u, int id, int c) {

	int lc = lca(v, u);
	if (st[v] > st[u]) swap(v, u);
	if (lc == v || lc == u) return query(st[v], st[u], id, -1, c);
	else return query(en[v], st[u], id, lca(v, u), c);
}

const int N = 1e5 + 5;
int mp[N], parity[N];

void upd(int x) {
	if (parity[x] & 1) --mp[ar[x]];
	else if (parity[x] & 1 ^ 1) ++mp[ar[x]];
	parity[x] ^= 1;
}

void solve() {
	ifstream cin("milkvisits.in");
	ofstream cout("milkvisits.out");

	int n, m;
	cin >> n >> m;
	while ((1 << lg) <= n) ++lg;
	gr.resize(n); up.resize(n); st.resize(n); en.resize(n); in.resize(n); out.resize(n); ar.resize(n); h.resize(n);

	for (int i = 0; i < n; ++i) up[i].resize(lg + 1);

	for (auto &i : ar) cin >> i;
	for (int i = 1; i < n; ++i) {
		int v, u;
		cin >> v >> u; --v; --u;
		gr[v].push_back(u); gr[u].push_back(v);
	}
	dfs(0, 0);
	vector <query> q(m);
	for (int i = 0; i < m; ++i) {
		int v, u, c;
		cin >> v >> u >> c;

		--v; --u;
		q[i] = make(v, u, i, c);
	}
	sort(all(q));
	vector <char> res(m);
	int l = q[0].l, r = q[0].l - 1;
	for (int i = 0; i < m; ++i) {
		while (l < q[i].l) upd(ord[l]), ++l;
		while (r > q[i].r) upd(ord[r]), --r;
		while (l > q[i].l) --l, upd(ord[l]);
		while (r < q[i].r) ++r, upd(ord[r]);
		
		int ans = mp[q[i].c];
		if (q[i].need != -1) { upd(q[i].need); ans = mp[q[i].c]; }

		res[q[i].id] = (ans ? '1' : '0');
		if (q[i].need != -1) upd(q[i].need);
	}
	debug() << imie(ord);
	for (auto i : res) cout << i;
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
//	ifstream cin("input.txt");
//	ofstream cout("output.txt");
	int q = 1; // cin >> q;
	while (q--) solve();
}

