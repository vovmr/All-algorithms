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

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
inline int rnd(int l, int r) { return (l + (rng() % (r - l + 1))); }

struct pnode {
	char x;
	int cnt[10];
	int sz = 1, pr, fl = 0;
	pnode *l = nullptr, *r = nullptr;
	pnode(char x) : x(x) { memset(cnt, 0, sizeof(cnt)); pr = rnd(1, 1e9); ++cnt[x - 'a']; }
};

typedef pnode* node;

inline int sz(node t) { return (!t ? 0 : t->sz); }
inline int get(node t, int pos) { return (!t ? 0 : t->cnt[pos]); }

inline void upd(node t) {
	if (!t) return;
	t->sz = sz(t->l) + 1 + sz(t->r);
	for (int i = 0; i < 10; ++i) t->cnt[i] = get(t->l, i) + get(t->r, i) + (t->x - 'a' == i);
}

inline void push(node t) {
	if (!t || !t->fl) return;
	if (t->l) t->l->fl ^= t->fl;
	if (t->r) t->r->fl ^= t->fl;
	if (t->fl) swap(t->l, t->r);
	t->fl = 0;
}

node merge(node a, node b) {
	push(a); push(b);
	if (!a || !b) return !a ? b : a;
	if (a->pr > b->pr) { a->r = merge(a->r, b); upd(a); return a; }
	else { b->l = merge(a, b->l); upd(b); return b; }
}

void split(node t, int x, node &a, node &b) {
	if (!t) return void(a = b = nullptr);
	push(t);
	int q = sz(t->l);
	if (q < x) split(t->r, x - q - 1, t->r, b), a = t;
	else split(t->l, x, a, t->l), b = t;
	upd(t);
}

node root;

vector <int> get(int l, int r) {
	node a, b, c, d;
	split(root, l, a, b);
	split(b, r - l + 1, c, d);
 
	vector <int> f(10);
	for (int i = 0; i < 10; ++i) f[i] = get(c, i);

	root = merge(a, merge(c, d));
	return f;
}

void insert(int pos, char x) {
	node f = new pnode(x);
	node a, b; split(root, pos, a, b);
	root = merge(merge(a, f), b);
}

void reverse(int l, int r) {
	node a, b, c, d;
	split(root, l, a, b);
	split(b, r - l + 1, c, d);
	c->fl ^= 1;
	root = merge(merge(a, c), d);
}

const int mod = 1e9 + 7;

void solve() {
	int n, q;
	cin >> n >> q;
	string s; cin >> s;

	root = nullptr;
	for (int i = 0; i < n; ++i) insert(i, s[i]);

	vector <ll> iv(n + 1); iv[0] = iv[1] = 1;
	for (int i = 2; i <= n; ++i) iv[i] = (mod - (mod / i)) * iv[mod % i] % mod;

	vector <ll> f(n + 1), ivf(n + 1); f[0] = ivf[0] = 1;
	for (int i = 1; i <= n; ++i) f[i] = f[i - 1] * i % mod, ivf[i] = ivf[i - 1] * iv[i] % mod;

	while (q--) {
		int type, l, r;
		cin >> type >> l >> r; --l, --r;

		if (type == 2) {
			vector <int> d = get(l, r);

			int s = 0;
			for (int i = 0; i < 10; ++i) s += (d[i] & 1);

			if (s > 1) { cout << 0 << '\n'; continue; }

			for (int i = 0; i < 10; ++i) d[i] -= (d[i] & 1), d[i] >>= 1;

			int len = r - l + 1 - (s == 1); ll ans = f[(len + 1) / 2];
			for (int i = 0; i < 10; ++i) ans = ans * ivf[d[i]] % mod;

			cout << ans << '\n';
		}
		else reverse(l, r);
	}
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
//	ifstream cin("input.txt");
//	ofstream cout("output.txt");
	int q = 1; // cin >> q;
	while (q--) solve();
}
