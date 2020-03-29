#include <bits/stdc++.h>
#define ll long long
#define ld long double
#define all(x)              (x).begin(), (x).end()
#define inf                 1e18
#define PI                  -2 * atan2(-1, 0)

using namespace std;

int lg;

vector <int> in, out;
vector < vector <int> > gr, up;

bool upper(int a, int b) {
    return (in[a] <= in[b] && out[b] <= out[a]);
}

void dfs(int v, int prev, int &t) {
    in[v] = ++t;
    up[v][0] = prev;
    for (int i = 1; i <= lg; ++i)
        up[v][i] = up[up[v][i - 1]][i - 1];
    for (auto to : gr[v]) {
        if (to != prev) {
            dfs(to, v, t);
        }
    }
    out[v] = ++t;
}

int lca(int a, int b) {
    if (upper(a, b))
        return a;
    else if (upper(b, a))
        return b;
    for (int i = lg; i >= 0; --i)
        if (!upper(up[a][i], b))
            a = up[a][i];
    return up[a][0];
}

int main() {
    ios_base::sync_with_stdio(false);
//    ifstream cin("input.txt");
//    ofstream cout("output.txt");
    int n;
    cin >> n;
    gr.resize(n); in.resize(n); out.resize(n); up.resize(n);
    for (int i = 0; i < n - 1; ++i) {
        int v, u;
        cin >> v >> u;
        --v; --u;
        gr[v].push_back(u);
        gr[u].push_back(v);
    }
    while ((1 << lg) <= n)
        ++lg;
    for (int i = 0; i < n; ++i)
        up[i].resize(lg + 1);
    int t = 0;
    dfs(0, 0, t);
    int q;
    cin >> q;
    while (q--) {
        int v, u;
        cin >> v >> u;
        --v; --u;
        cout << lca(v, u) + 1 << endl;
    }
}
