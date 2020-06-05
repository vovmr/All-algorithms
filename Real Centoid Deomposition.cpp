/// Solution to spoj.com QTREEE5 " Query on a tree V "
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
 
string s;
 
vector < vector <int> > g;
vector <int> sz, used, h, ac;
 
void length(int v, int p) {
        sz[v] = 1;
        for (auto to : g[v]) {
                if (to != p && !used[to]) {
                        length(to, v); sz[v] += sz[to];
                }
        }
}
 
int centroid(int v, int p, int n) {
        for (auto to : g[v]) {
                if (to != p && !used[to] && sz[to] > n / 2) {
                        return centroid(to, v, n);
                }
        }
        return v;
}
 
void decomposition(int v, int p, int n) {
        used[v] = 1; ac[v] = p; length(v, p); h[v] = h[p] + 1;
 
        for (auto to : g[v]) {
                if (to != p && !used[to]) {
                        int c = centroid(to, v, sz[to]);
                        decomposition(c, v, sz[to]);
                }
        }
}

int lg = 0, T = 0;
 
vector <int> dist, in, out;
vector < vector <int> > up;
 
void dfs(int v, int p) {
	in[v] = ++T;
	up[v][0] = p;
	for (int i = 1; i <= lg; ++i) {
		up[v][i] = up[up[v][i - 1]][i - 1];
	}
        for (auto to : g[v]) {
                if (to != p) {
                        dist[to] = dist[v] + 1;
                        dfs(to, v);
                }
        }
        out[v] = ++T;
}

bool upper(int a, int b) {
	return (in[a] <= in[b] && out[b] <= out[a]);
}
 
inline int lca(int a, int b) {
	if (upper(a, b)) return a;
	if (upper(b, a)) return b;
	for (int i = lg; i >= 0; --i) {
		if (!upper(up[a][i], b)) {
			a = up[a][i];
		}
	}
	return up[a][0];
}
 
inline int F(int a, int b) {
        int res = dist[a] + dist[b] - 2 * dist[lca(a, b)];
        return res;
} 
 
vector < multiset < pair <int, int> > > f;
 
int get(int v) {
        int ans = INT_MAX, u = v;
        while (1) {
                if (!f[v].empty()) {
                        auto cur = *f[v].begin();
                        ans = min(ans, cur.fi + F(v, u));
                }
 
                if (ac[v] == v) break;
                v = ac[v];
        }
        return ans;
}
 
void upd(int v, int type) {
        if (type == 1) {
                int cur = v;
                while (1) {
                        pair <int, int> now = { F(cur, v), cur }; f[v].insert(now);
                        if (ac[v] == v) break;
                        v = ac[v];
                }
        }
        else {
                int cur = v;
                while (1) {
                        pair <int, int> now = { F(cur, v), cur };
                        f[v].erase(f[v].find(now));
                        if (ac[v] == v) break;
                        v = ac[v];
                }
        }
}
 
void solve() {
        int n;
        cin >> n;
        g.resize(n); h.resize(n); used.resize(n); sz.resize(n);
        for (int i = 0; i < n - 1; ++i) {
                int v, u;
                cin >> v >> u; --v; --u;
                g[v].push_back(u); g[u].push_back(v);
        }

        in.resize(n); out.resize(n); up.resize(n);

        while ((1 << lg) <= n) ++lg;
        for (int i = 0; i < n; ++i) up[i].resize(lg + 1);

        dist.resize(n); ac.resize(n);
        int c = centroid(0, 0, n); decomposition(c, c, n); dfs(c, c);
 
        vector <int> col(n); f.resize(n);
        /// 0 -- black, 1 -- white
 
        int q;
        cin >> q;
        while (q--) {
                int t, v;
                cin >> t >> v; --v;
 
                if (!t) {
                        if (col[v] == 0) upd(v, 1);
                        if (col[v] == 1) upd(v, 2);
                        col[v] ^= 1;
                }
                else {
                        int res = get(v);
                        if (res == INT_MAX) cout << -1 << '\n';
                        else cout << res << '\n';
                }
        }
}
 
int main() {
	ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
//	ifstream cin("input.txt");
//	ofstream cout("output.txt");
	int q = 1; // cin >> q;
	while (q--) {
		solve();
	}
} 
