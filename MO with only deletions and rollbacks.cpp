/*
MO algortithm
That only perfirms deletions od element
IZhO 2020 day2 task 3
Also requires ability to do rollbacks in non-amorthized time
*/
#include <bits/stdc++.h>
#define fi first
#define se second
#define ll long long
#define ld long double
#define all(x) 			(x).begin(), (x).end()
#define inf 			1e18

#define pb push_back
#define pll pair <ll, ll>
#define pii pair <int, int>
#define mpp make_pair
#define mtt make_tuple

using namespace std;

struct List {
	ll ans = 0;
	vector <int> l, r, ar;

	struct roll_back { int prev, prevL, prevR; };
	stack <roll_back> oper;

	List(vector <int> &ar) : ar(ar) {
		int n = ar.size();
		l.resize(n); r.resize(n);
		for (int i = 0; i < n; ++i) {
			l[i] = (i ? i - 1 : -1);
			r[i] = (i < n - 1 ? i + 1 : -1);
		}
		for (int i = 1; i < n; ++i) ans += abs(ar[i] - ar[i - 1]);
	}
	void del(int pos) {
		if (l[pos] != -1) ans -= abs(ar[pos] - ar[l[pos]]);
		if (r[pos] != -1) ans -= abs(ar[pos] - ar[r[pos]]);

		int left = l[pos], right = r[pos];
		oper.push((roll_back){pos, left, right});

		if (right != -1) l[right] = left;
		if (left != -1) r[left] = right;
		if (left != -1 && right != -1) {
			ans += abs(ar[left] - ar[right]);
		}
	}
	void roll() {
		auto [pos, le, re] = oper.top(); oper.pop();
		if (le != -1) ans += abs(ar[le] - ar[pos]), r[le] = pos;
		if (re != -1) ans += abs(ar[re] - ar[pos]), l[re] = pos;
		if (le != -1 && re != -1) ans -= abs(ar[re] - ar[le]);
	}
};

const int block = 463;

struct query {
	int l, r, id;
	inline pair <int, int> toPair() const {
		return mpp(l / block, -r);
	}
};

inline bool operator < (const query &a, const query &b) {
	return a.toPair() < b.toPair();
}

void solve() {
	int n, q;
	cin >> n >> q;
	vector <int> v(n);
	for (auto &i : v) cin >> i;

	List ar(v);
	vector <query> a(q);

	vector < pair <int, int> > lol(n);
	for (int i = 0; i < n; ++i) lol[i] = {v[i], i};

	sort(all(lol));
	for (int i = 0; i < q; ++i) {
		int L, R;
		cin >> L >> R;
		L = lower_bound(all(lol), mpp(L, -1)) - lol.begin();
		R = upper_bound(all(lol), mpp(R, INT_MAX)) - lol.begin() - 1;
		a[i] = {L, R, i};
	}

	sort(all(a));
	vector <ll> ans(q);
	int l = 0, r = n - 1;

	for (int i = 0; i < q; ++i) {
		if (a[i].l > a[i].r) {
			ans[a[i].id] = 0;
			continue;
		}

		if (l / block != a[i].l / block) {
			while (r != n - 1) ar.roll(), ++r;
			while (l / block != a[i].l / block) ar.del(lol[l].se), ++l;
		}
		while (r > a[i].r) ar.del(lol[r].se), --r;

		int prv = l;
		while (l < a[i].l) ar.del(lol[l].se), ++l;

		ans[a[i].id] = ar.ans;
		while (l > prv) ar.roll(), --l;
	}

	for (auto i : ans) cout << i << "\n";
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	int q = 1; // cin >> q;
	while (q--) solve();
}
