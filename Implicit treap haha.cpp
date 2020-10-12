#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")
#define fi first
#define se second
#define ll long long
#define ld long double
#define all(x)              (x).begin(), (x).end()
#define inf                 1e18

using namespace std;
using namespace __gnu_pbds;

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

template <class C>
using oset = tree <C, null_type, less_equal <C>, rb_tree_tag, tree_order_statistics_node_update>;

const int mod = 1e9 + 7;

inline int mult(const int &a, const int &b) {
	return ((ll)a * b) % mod;
}

inline int bp(int a, int n) {
	int res = 1;
	if (!n) return res;
	while (n > 0) {
		if (n & 1) res = mult(res, a);
		a = mult(a, a);
		n >>= 1;
	}
	return res;
}

inline int inv(int a) { return bp(a, mod - 2); }

mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
ll gen(ll l, ll r) { return (l + (rnd() % (r - l + 1))); }

struct pnode {
	int s = 1, val = 0, p = 0, sz = 0;
	pnode *l = nullptr, *r = nullptr;
	pnode(int val) : val(val), s(val), sz(1) { p = gen(1, 1e9 + 7); }
};

typedef pnode* node;

inline int sz(node t) { return (t ? t->sz : 0); }
inline int s(node t) { return (t ? t->s : 1); }
inline bool ex(node t) { return t != nullptr; }

void upd(node t) {
	if (t == nullptr) return;
	t->sz = sz(t->l) + sz(t->r) + 1;
	t->s = mult(mult(s(t->l), s(t->r)), t->val);
}

node merge(node a, node b) {
	if (!ex(a) || !ex(b)) return (!ex(a) ? b : a);
	if (a->p > b->p) { a->r = merge(a->r, b); upd(a); return a; }
	else { b->l = merge(a, b->l); upd(b); return b; }
}

void split(node t, int x, node &a, node &b) {
	if (!ex(t)) { a = b = nullptr; return; }

	int q = sz(t->l);
	if (q < x) split(t->r, x - q - 1, t->r, b), a = t;
	else split(t->l, x, a, t->l), b = t;
	upd(t);
}

node root;
oset <int> pos;

node insert(node root, int x) {
	node f = new pnode(x);
	int id = pos.order_of_key(x);

	node a, b;
	split(root, id, a, b);
	return merge(merge(a, f), b);
}

node erase(node root, int pos) {
	node a, b, c, d;
	split(root, pos, a, b);
	split(b, 1, c, d);
	return merge(a, d);
}

int get(node root, int l, int r) {
	node a, b; split(root, l, a, b);
	node c, d; split(b, r - l + 1, c, d);

	int res = s(c);
	root = merge(merge(a, c), d); return res;
}

void print(node t) {
	if (ex(t->l)) print(t->l);
	if (ex(t)) cout << t->val << " ";
	else return;
	if (ex(t->r)) print(t->r);
}

void solve() {
	int n;
	cin >> n;
	node root = nullptr;
	for (int i = 0; i < n; ++i) {
		int type;
		cin >> type;
		if (type == 1) {
			int x;
			cin >> x;
			root = insert(root, x); pos.insert(x);
		}
		else if (type == 2) {
			int f;
			cin >> f;
			root = erase(root, f - 1);
			int x = *pos.find_by_order(f - 1);
			pos.erase(pos.lower_bound(x - 1));

		}
		else {
			int l, r;
			cin >> l >> r; --l, --r;
			cout << get(root, l, r) << '\n';
		}
	}
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
//	ifstream cin("input.txt");
//	ofstream cout("output.txt");
	int q = 1; // cin >> q;
	while (q--) solve();
}
