/// allows you to reverse any segment of the array + insert/erase elements to/from any position
/// as the result -- we can also do cyclic shifts of the array
#include <bits/stdc++.h>
#define fi first
#define se second
#define ll long long
#define ld long double
#define all(x)              (x).begin(), (x).end()
#define inf                 1e18

using namespace std;

constexpr ll mod = 1e10 + 7;
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
inline ll G() { return (rng() % mod); }

struct Node {
	int sz = 1, rv = 0;
	Node *l = nullptr, *r = nullptr;
	ll prior, x = 0;
	Node(ll x) : x(x) { prior = G(); }
};

typedef Node* node;
int sz(node t) { return ((!t) ? 0 : t->sz); }
void upd(node t) { t->sz = sz(t->l) + sz(t->r) + 1; }

void push(node t) {
	if (!t || !t->rv) return;
	if (t->l) t->l->rv ^= 1;
	if (t->r) t->r->rv ^= 1;

	swap(t->l, t->r);
	t->rv = 0;
}

pair <node, node> split(node t, int key) {
	if (!t) return {nullptr, nullptr};
	push(t);

	if (key <= sz(t->l)) {
		node l;
		tie(l, t->l) = split(t->l, key); upd(t);

		return {l, t};
	}
	else {
		node r;
		tie(t->r, r) = split(t->r, key - sz(t->l) - 1); upd(t);

		return {t, r};
	}
}

node merge(node a, node b) {
	if (!b) { push(a); return a; }
	if (!a) { push(b); return b; }

	if (a->prior > b->prior) {
		push(a);
		a->r = merge(a->r, b); upd(a);

		return a;
	}
	else {
		push(b);
		b->l = merge(a, b->l); upd(b);

		return b;
	}
}

void sift(node t) {
	while (1) {
		node r = t;
		if (t->l && t->l->prior > r->prior) r = t->l;
		if (t->r && t->r->prior > r->prior) r = t->r;
		if (r == t) break;

		swap(r->prior, t->prior); t = r;
	}
}

int get(node t, int pos) {
	push(t);
	if (sz(t->l) == pos) return t->x;
	if (sz(t->l) > pos) return get(t->l, pos);
	else return get(t->r, pos - sz(t->l) - 1);
}

void insert(node &t, int pos, ll x) {
	node l, r, f = new Node(x);
	tie(l, r) = split(t, pos);
	t = merge(merge(l, f), r);
}

void erase(node &t) {
	node old = t;
	t = merge(t->l, t->r);
	delete old;
}

void erase(node &t, int pos) {
	push(t);
	if (pos == sz(t->l)) erase(t);
	else if (sz(t->l) > pos) { erase(t->l, pos); upd(t); }
	else { erase(t->r, pos - sz(t->l) - 1); upd(t); }
}

void reverse(node &t, int L, int R) {
	node l, r, m;
	tie(l, r) = split(t, R + 1);
	tie(l, m) = split(l, L);

	m->rv ^= 1;
	t = merge(merge(l, m), r);
}

vector <ll> ar;
node build(int vl, int vr) {
	if (vl > vr) return nullptr;

	int mid = (vl + vr) >> 1;

	node t = new Node(ar[mid]);
	t->l = build(vl, mid - 1); t->r = build(mid + 1, vr);
	sift(t); upd(t); return t;
}

void Free(node t) {
	if (!t) return;
	if (t->l) Free(t->l);
	if (t->r) Free(t->r);
	delete t;
}

node root;

void print() {
	for (int i = 0; i < sz(root); ++i) cout << get(root, i) << " ";
	cout << '\n';
}

void solve() {
	int n, m, q;
	cin >> n >> q >> m;

	ar.resize(n);
	for (auto &i : ar) cin >> i;

	root = build(0, n - 1);

	while (q--) {
		int t, l, r;
		cin >> t >> l >> r; --l; --r;

		if (t == 1) {
			ll x = get(root, r);
			erase(root, r);
			insert(root, l, x);
		}
		else reverse(root, l, r);

//		if (sz(root) != n) {
//			cout << "ERROR" << '\n'; print();
//			return;
//		}
//		cout << "OK" << '\n'; print(); cout << '\n';
	}
	while (m--) {
		int x;
		cin >> x; --x;
		cout << get(root, x) << '\n';
	}
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
//	ifstream cin("input.txt");
//	ofstream cout("output.txt");
	int q = 1; // cin >> q;
	while (q--) solve();
}
