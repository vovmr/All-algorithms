#include <bits/stdc++.h>
#define fi first
#define se second
#define ll long long
#define ld long double
#define all(x)              (x).begin(), (x).end()
#define inf                 1e18
 
using namespace std;
 
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
 
inline ll sum(node t) {
	return ((t != nullptr) ? t->sum : -inf);
}
 
inline void update(node t) {
	if (t != nullptr) {
		t->size = 1 + sz(t->l) + sz(t->r);
		t->sum = max(sum(t->l), max(sum(t->r), t->val));
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
 
inline ll get(node t, int x, int y) {
	node l, r, a, b;
	Split(t, x, l, r);
	Split(r, y - x + 1, a, b);
 
	ll res = sum(a);
	t = Merge(l, Merge(a, b));
 
	return res;
}
 
void solve() {
	int q;
	cin >> q;
	node t = nullptr;
 
	while (q--) {
		char c;
		ll l, r;
		cin >> c >> l >> r;
		if (c == 'A') t = insert(t, r - 1, l);
		else cout << get(t, l - 1, r - 1) << '\n';
 
//		print(t);
//		cout << endl;
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
