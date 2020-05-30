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

const ll mod = 1e9 + 9;

mt19937_64 rng(chrono::system_clock::now().time_since_epoch().count());

struct Node {
	Node *l, *r;
	ll k, p, size;
	Node(ll K, ll P) : k(K), p(P), l(nullptr), r(nullptr), size(1) {}
	Node(Node *l, Node *r, ll K, ll P) : l(l), r(r), k(K), p(P), size(1) {}
};

typedef Node* node;

inline int sz(node t) {
	return ((t != nullptr) ? t->size : 0);
}

inline void update(node t) {
	if (t != nullptr) t->size = 1 + sz(t->l) + sz(t->r);
}

void Split(node t, int x, node &l, node &r) {
	if (t == nullptr) l = r = nullptr;

	else if (t->k <= x) Split(t->r, x, t->r, r), l = t;
	else Split(t->l, x, l, t->l), r = t;
	update(t);
}

void Merge(node &t, node a, node b) {
	if (a == nullptr || b == nullptr) t = ((a == nullptr) ? b : a);
	else if (a->p > b->p) Merge(a->r, a->r, b), t = a;
	else Merge(b->l, a, b->l), t = b;
	update(t);
}

inline node make(ll v) {
	ll prior = rng() % mod;
	return new Node(v, prior);
}

void insert(node &t, node v) {

	if (t == nullptr) t = v;
	else if (t->p < v->p) Split(t, v->k, v->l, v->r), t = v;
	else insert( ( ( t->k <= v->k ) ? t->r : t->l ), v );
	update(t);
}

void erase(node &t, int v) {
	if (t == nullptr) return;

	else if (t->k == v) Merge(t, t->l, t->r);
	else erase( ( (t->k <= v) ? t->r : t->l ), v );
	update(t);
}

int get(node t, int k) {
	if (sz(t->l) == k) return t->k;
	else if (sz(t->l) > k) return get(t->l, k);
	else return get(t->r, k - sz(t->l) - 1);
}

int smaller(node t, int x) {
	if (t == nullptr) return 0;
	if (t->k >= x) return smaller(t->l, x);
	else return (1 + sz(t->l) + smaller(t->r, x));
}

void solve() {
	int q;
	cin >> q;

	node t = nullptr;
	map <int, bool> have;

	while (q--) {
		char c;
		cin >> c;
		if (c == 'C') {
			int x;
			cin >> x;
			cout << smaller(t, x) << '\n';
		}
		else if (c == 'K') {
			int k;
			cin >> k; --k;
			if (sz(t) <= k) {
				cout << "invalid" << '\n';
				continue;
			}

			cout << get(t, k) << '\n';
		}
		else if (c == 'I') {
			int x;
			cin >> x;
			node v = make(x);
			if (!have[x]) insert(t, v);

			have[x] = 1;
		}
		else if (c == 'D') {
			int x;
			cin >> x;
			if (have[x]) erase(t, x);
			have[x] = 0;
		}
	}
}

int main() {
        ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
//      freopen("input.txt", "r", stdin);
//      freopen("output.txt", "w", stdout);
        int q = 1; // cin >> q;
        while (q--) {
                solve();
        }
}
