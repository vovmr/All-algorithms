#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("avx,avx2,fma")
#define fi first
#define se second
#define ll long long
#define ld long double
#define all(x)              (x).begin(), (x).end()
#define inf                 1e18
 
using namespace std;
 
const int block = 251;
const int N = (int)3e6;
 
struct st {
	int sum = 0;
	int l = 0, r = 0;
};
 
st t[N];
int w = 0;
int lst[(int)5e5 + 6], root[(int)1e5 + 5];
 
void build(int v, int vl, int vr) {
	t[v] = st{0, 0, 0};
	lst[v] = v; w = max(w, v + 1);
	if (vl == vr) return;
 
	int m = vl + vr >> 1;
	t[v].l = 2 * v + 1, t[v].r = 2 * v + 2;
	build(2 * v + 1, vl, m); build(2 * v + 2, m + 1, vr);
	t[v].sum = t[t[v].l].sum + t[t[v].r].sum;
}
 
ll get(int v, int vl, int vr, int l, int r) {
	if (l > r) return 0;
	else if (vl == l && vr == r) return t[v].sum;
	int m = vl + vr >> 1;
	return (get(t[v].l, vl, m, l, min(r, m)) + get(t[v].r, m + 1, vr, max(l, m + 1), r));
}
 
void upd(int v, int x, int vl, int vr, int pos, ll val) {
	int cur = lst[x]; lst[x] = v; t[v] = t[cur];
	if (vl == vr) {
		t[v].sum = val;
		return;
	}
	int m = vl + vr >> 1;
	if (pos <= m) {
		t[v].l = ++w;
		upd(t[v].l, 2 * x + 1, vl, m, pos, val);
	}
	else {
		t[v].r = ++w;
		upd(t[v].r, 2 * x + 2, m + 1, vr, pos, val);
	}
	t[v].sum = t[t[v].l].sum + t[t[v].r].sum;
}
 
struct stonks {
 
	vector <ll> v;
	vector < pair <ll, int> > ar;
 
	stonks(vector <ll> &nv) {
		v.clear(); v = nv;
		int n = v.size(); ar.clear(); ar.resize(n);
		for (int i = 0; i < n; ++i) ar[i] = {v[i], i};
 
		root[0] = 0; w = 0;
 
		sort(all(ar));
		build(0, 0, n - 1);
		for (int i = 0; i < n; ++i) {
			root[i + 1] = ++w;
			upd(root[i + 1], 0, 0, n - 1, ar[i].se, 1); 
		}
	}
 
	ll que(int l1, int r1, ll x) {
		int l = 1, r = ar.size(), mid, ans = 0;
		while (l <= r) {
			mid = l + r >> 1;
			if (ar[mid - 1].fi <= x) ans = mid, l = mid + 1;
			else r = mid - 1;
		}
		return get(root[ans], 0, ar.size() - 1, l1, r1);
	}
};
 
void solve() {
	int n, m;
	cin >> n >> m;
	vector <ll> v(n);
	for (auto &i : v) cin >> i;
 
	vector < tuple <char, ll, ll, ll> > q(m);
	for (int i = 0; i < m; ++i) {
		char x;
		cin >> x;
		if (x == 'M') {
			ll a, pos;
			cin >> pos >> a; --pos;
			q[i] = make_tuple(x, pos, a, 0);
		}
		else {
			ll a, l, r;
			cin >> l >> r >> a; --l; --r;
			q[i] = make_tuple(x, l, r, a);
		}
	}
 
	stonks f(v);
	for (int l = 0; l < m; l += block) {
		int r = min(m - 1, l + block - 1);
 
		unordered_map <int, int> mp;
		for (int i = l; i <= r; ++i) {
			char o; ll a, l1, r1; tie(o, l1, r1, a) = q[i];
 
			if (o == 'C') {
				ll ans = f.que(l1, r1, a);
				for (auto &x : mp) {
					if (v[x.fi] <= a && x.fi >= l1 && x.fi <= r1) --ans;
					if (x.se <= a && x.fi >= l1 && x.fi <= r1) ++ans;
				}
				cout << ans << '\n';
			}
			else mp[l1] = r1;
		}
		for (auto &x : mp) v[x.fi] = x.se;
		f = stonks(v);
	}
}
 
int main() {
	ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
//	ifstream cin("input.txt");
//	ofstream cout("output.txt");
	int q = 1; // cin >> q;
	while (q--) solve();
}
