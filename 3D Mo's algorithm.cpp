#include <bits/stdc++.h>
#define fi first
#define se second
#define ll long long
#define ld long double
#define all(x)              (x).begin(), (x).end()
#define inf                 1e18

using namespace std;

const int block = 2201;

struct query {
	int t, l, r, id;
	query(int t, int l, int r, int id) : t(t), l(l), r(r), id(id) {}
	inline tuple <int, int, int> toTuple() const {
		int a = t / block;
		int b = (a & 1 ? -(l / block) : (l / block));
		int c = (((l / block) & 1) ? -r : r);
		return make_tuple(a, b, c);
	}
};

inline bool operator < (const query &a, const query &b) {
	return a.toTuple() < b.toTuple();
}

int l, r, t;
vector < pair <int, int> > updates;

const int N = 2e5 + 5;

int cnt[N], pref[N];
int mp[N], ar[N];

void add(int x) {
	--mp[cnt[x]];
	++cnt[x]; ++mp[cnt[x]];
}

void del(int x) {
	--mp[cnt[x]];
	--cnt[x]; ++mp[cnt[x]];
}

void upd(int num) { --num;
	int id = updates[num].se;
	int val = updates[num].fi;

	if (l <= id && id <= r) {
		del(ar[id]);
		add(val);
	}
	pref[num] = ar[id];
	ar[id] = val;
}

void deupd(int num) { --num;
	int id = updates[num].se;
	int val = pref[num];

	if (l <= id && id <= r) {
		del(ar[id]);
		add(val);
	}
	ar[id] = val;
}

void solve() {
	int n, m;
	cin >> n >> m;

	map <int, int> cp;
	for (int i = 0; i < n; ++i) {
		cin >> ar[i];
		++cp[ar[i]];
	}
	int cnt1 = 0;
	vector <query> q;
	for (int i = 0; i < m; ++i) {
		int type;
		cin >> type;
		if (type == 2) {
			++cnt1;
			int id, x;
			cin >> id >> x; ++cp[x];
			updates.push_back({x, --id});
		}
		else {
			int l, r;
			cin >> l >> r; --l, --r;
			q.push_back((query){cnt1, l, r, i});
		}
	}
	sort(all(q));
	l = q[0].l, r = q[0].l - 1; t = 0;

	int C = 0;
	for (auto &[a, b] : cp) b = C++;
	for (auto &[val, id] : updates) val = cp[val];
	for (int i = 0; i < n; ++i) ar[i] = cp[ar[i]];

	mp[0] = 1e9 + 5;
	vector <int> ans(m, -1);

	for (int i = 0; i < q.size(); ++i) {
		while (t > q[i].t) deupd(t--);
		while (t < q[i].t) upd(++t);
		while (r < q[i].r) add(ar[++r]);
		while (l > q[i].l) add(ar[--l]);
		while (r > q[i].r) del(ar[r--]);
		while (l < q[i].l) del(ar[l++]);

		int mex = 0;
		while (mp[mex]) ++mex;

		ans[q[i].id] = mex;
	}
	for (auto i : ans) {
		if (i != -1) cout << i << '\n';
	}
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
//	ifstream cin("input.txt");
//	ofstream cout("output.txt");
	int q = 1; // cin >> q;
	while (q--) solve();
}
