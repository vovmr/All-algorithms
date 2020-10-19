#include <bits/stdc++.h>
#define fi first
#define se second
#define ll long long
#define ld long double
#define all(x)              (x).begin(), (x).end()
#define inf                 1e18

using namespace std;

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

const int block = 543;

vector <int> p, rnk;
void make(int v) { p[v] = v; rnk[v] = 1; }
int par(int v) { if (p[v] == v) { return v; } return (p[v] = par(p[v])); }

void dsu(int a, int b) {
	a = par(a), b = par(b);
	if (a != b) {
		if (rnk[a] > rnk[b]) swap(a, b);
		p[a] = b, rnk[b] += rnk[a];
	}
}

void solve() {
	int n, m;
	cin >> n >> m;
	p.resize(n); rnk.resize(n);
	for (int i = 0; i < n; ++i) make(i);

	map < pair <int, int>, int > lst;
	vector < tuple <int, int, int> > q(m);

	for (int i = 0; i < m; ++i) {
		string s; int v, u; cin >> s >> v >> u;
		--v; --u; if (v > u) swap(v, u);

		int t;
		if (s == "conn") t = 1;
		else t = (s == "add" ? 2 : 3);

		if (t == 2) lst[make_pair(v, u)] = i;
		if (t <= 2) q[i] = make_tuple(t, v, u);
		else q[i] = make_tuple(t, lst[make_pair(v, u)], u);
	}

	vector <int> used(n);
	vector < vector <int> > gr(n);

	vector <int> global(m);
	for (int l = 0; l < m; l += block) {
		int r = min(m - 1, l + block - 1);

		vector <int> del(m);
		for (int i = l; i <= r; ++i) {
			int t, v, u; tie(t, v, u) = q[i];
			if (t == 3) del[v] = 1;
		}

		for (int i = 0; i < m; ++i) {
			int t, v, u; tie(t, v, u) = q[i];
			if (t == 2 && !del[i] && global[i]) dsu(v, u);
		}

		for (int i = l; i <= r; ++i) {
			int t, v, u; tie(t, v, u) = q[i];

			if (t == 2) global[i] = 1;
			else if (t == 3) global[v] = 0;
			else if (t == 1) {
				if (par(v) == par(u)) {
					cout << "YES" << '\n';
					continue;
				}

				unordered_set <int> li; li.insert(par(v)); li.insert(par(u));
				for (int j = l; j <= r; ++j) {
					int t1, v1, u1; tie(t1, v1, u1) = q[j];
					if (t1 == 2 && global[j]) {
						gr[par(v1)].push_back(par(u1));
						gr[par(u1)].push_back(par(v1));
						li.insert(par(v1)); li.insert(par(u1));
					}
					else if (t1 == 3 && global[v1]) {
						int t2, v2, u2; tie(t2, v2, u2) = q[v1];
						gr[par(v2)].push_back(par(u2));
						gr[par(u2)].push_back(par(v2));
						li.insert(par(v2)); li.insert(par(u2));
					}
				}

				queue <int> bfs; bfs.push(par(v)); used[par(v)] = 1;
				while (!bfs.empty()) {
					int s = bfs.front(); bfs.pop(); used[s] = 1;
					for (auto to : gr[s]) if (!used[to]) {
						used[to] = 1; bfs.push(to);
					}
				}
				cout << ((used[par(u)]) ? "YES" : "NO") << '\n';
				for (auto x : li) used[x] = 0, gr[x].clear();
			}
		}
		for (int i = 0; i < n; ++i) make(i);
	}
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
//	ifstream cin("input.txt");
//	ofstream cout("output.txt");
	int q = 1; // cin >> q;
	while (q--) solve();
}
/*
5 6
conn 1 5
add 1 2
add 1 3
add 3 4
add 5 4
conn 1 5
*/
