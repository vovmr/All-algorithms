// Mo's algorithm sollution to 86D on Codeforces

#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#define ll long long
#define ld long double
#define all(x)              (x).begin(), (x).end()
#define inf                 1e18

using namespace std;
using namespace __gnu_pbds;

template <typename T>
using ordered_set = tree <T, null_type, less <T>, rb_tree_tag, tree_order_statistics_node_update>;

const int sz = 500, N = 1e6 + 1;

ll mp[N];

struct query {
	int l, r, id;
	query(int l, int r, int id) : l(l), r(r), id(id) {}
	bool operator < (const query &a) {
		if (l / sz != a.l / sz) {
			return (l / sz < a.l / sz);
		}
		return (((l / sz) & 1) ? (r < a.r) : (r > a.r));
	}
};

ll ans = 0;

void add(int id, vector <ll> &ar) {
	ans -= (ar[id] * mp[ar[id]] * mp[ar[id]]); ++mp[ar[id]];
	ans += (ar[id] * mp[ar[id]] * mp[ar[id]]);
}

void del(int id, vector <ll> &ar) {
	ans -= (ar[id] * mp[ar[id]] * mp[ar[id]]); --mp[ar[id]];
	ans += (ar[id] * mp[ar[id]] * mp[ar[id]]);
}

vector <ll> MO(vector <query> &q, vector <ll> &ar) {
	int n = q.size();
	vector <ll> anses(n);
	sort(all(q));
	int l = 0, r = -1;
	for (auto x : q) {
		while (l > x.l) {
			--l;
			add(l, ar);
		}
		while (r < x.r) {
			++r;
			add(r, ar);
		}
		while (l < x.l) {
			del(l, ar);
			++l;
		}
		while (r > x.r) {
			del(r, ar);
			--r;
		}
		anses[x.id] = ans;
	}
	return anses;
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
//	ifstream cin("input.txt");
//	ofstream cout("output.txt");
	int n, m;
	cin >> n >> m;
	vector <ll> v(n);
	vector <query> q(m, query(0, 0, 0));
	for (auto &i : v) {
		cin >> i;
	}
	for (int i = 0; i < m; ++i) {
		int l, r;
		cin >> l >> r;
		q[i] = query(--l, --r, i);
	}
	vector <ll> ar = MO(q, v);
	for (auto i : ar) {
		cout << i << '\n';
	}
}
