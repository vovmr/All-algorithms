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

const ll mod = 1e9 + 7;
mt19937_64 rng(chrono::system_clock::now().time_since_epoch().count());

struct Node {
	Node *l, *r;
	ll sum, p, size, val;
	Node(ll val, ll p) : p(p), size(1) { l = r = nullptr; this->val = val; sum = val; }
};

typedef Node* node;

void print(node t) {
	if (t->l != nullptr) print(t->l);
	if (t != nullptr) cout << t->val << " ";
	if (t->r != nullptr) print(t->r);
}

inline int sz(node t) {
	return ((t != nullptr) ? t->size : 0);
}

inline int sum(node t) {
	return ((t != nullptr) ? t->sum : 0);
}

inline void update(node t) {
	if (t != nullptr) {
		t->size = 1 + sz(t->l) + sz(t->r);
		t->sum = sum(t->l) + sum(t->r) + t->val;
	}
}

node Merge(node a, node b) {
	if (a == nullptr || b == nullptr) return ((a == nullptr) ? b : a);
	else if (a->p > b->p) {
		a->r = Merge(a->r, b);
		update(a); return a;
	}
	else {
		b->l = Merge(a, b->l);
		update(b); return b;
	}
}

void Split(node t, int x, node &a, node &b) {
	if (t == nullptr) {
		a = b = nullptr;
		return;
	}
	int Q = sz(t->l);
	if (Q < x) Split(t->r, x - Q - 1, t->r, b), a = t;
	else Split(t->l, x, a, t->l), b = t;
	update(t);
}

inline node make(ll sum) {
	ll prior = rng() % mod;
	return new Node(sum, prior);
}

inline node insert(node t, int pos, ll sum) {
	node a, b;
	node f = make(sum);
	Split(t, pos, a, b);
	return Merge(Merge(a, f), b);
}

ll get(node t, int l, int r) {
	node a, b, c, d;
	Split(t, l, a, b);
	Split(b, r - l + 1, c, d);

	ll res = sum(c);
	t = Merge(Merge(a, c), d);

	return res;
}

void solve() {
	int q;
	cin >> q;

	node t = new Node(0, 0);
	for (int i = 0; i < q; ++i) {
		int c;
		cin >> c;
		if (c == 1) {
			int l, r;
			cin >> l >> r;
			ll ans = get(t, l, r);
			cout << "Sum is " << ans << endl;
		}
		else {
			int pos, x;
			cin >> pos >> x;
			t = insert(t, pos, x);
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
