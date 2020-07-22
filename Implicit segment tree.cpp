#include <bits/stdc++.h>
#define fi first
#define se second
#define ll long long
#define ld long double
#define all(x)              (x).begin(), (x).end()
#define inf                 1e18

using namespace std;

struct st {
	st *l = 0, *r = 0; ll s = 0, add = 0;
	void push(int vl, int vr) {
		if (vl != vr && !l) l = new st{nullptr, nullptr, 0, 0};
		if (vl != vr && !r) r = new st{nullptr, nullptr, 0, 0};
		if (vl == vr) return;
		
		int m = vl + vr >> 1;
		l->add += add; r->add += add;
		l->s += (m - vl + 1) * add; r->s += (vr - m) * add; add = 0;
	}
};

inline ll s(st *v) { return (!v ? 0LL : v->s); }

void upd(st *v, int vl, int vr, int l, int r, ll x) {
	if (l > r) return;
	else if (vl == l && vr == r) {
		v->add += x; v->s += (vr - vl + 1) * x;
		return;
	}
	v->push(vl, vr);
	int m = vl + vr >> 1;
	upd(v->l, vl, m, l, min(r, m), x);
	upd(v->r, m + 1, vr, max(l, m + 1), r, x);
	v->s = s(v->l) + s(v->r);
}

ll find(st *v, int vl, int vr, ll k) {
	if (vl == vr) return vl;

	v->push(vl, vr);
	int m = vl + vr >> 1;
	if (s(v->l) >= k) return find(v->l, vl, m, k);
	else return find(v->r, m + 1, vr, k - s(v->l));
}

void solve() {
	int n;
	cin >> n;
	const int sz = 1e9 + 1;
	st *root = new st{nullptr, nullptr, 0, 0};

	ll f = 0;
	while (n--) {
		int l, r;
		cin >> l >> r;

		f += (r - l + 1);
		upd(root, 0, sz, l, r, 1); cout << find(root, 0, sz, (f + 1) / 2) << '\n';
	}
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
//	ifstream cin("input.txt");
//	ofstream cout("output.txt");
	int q = 1; // cin >> q;
	while (q--) solve();
}
