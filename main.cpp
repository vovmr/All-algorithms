#include <bits/stdc++.h>
#define ll long long
#define ld long double
#define all(x)              (x).begin(), (x).end()
#define inf                 1e18
#define PI                  -2 * atan2(-1, 0)

using namespace std;

vector <ll> ar, t, add;

void build(int v, int vl, int vr)
{
    if (vl == vr)
    {
        t[v] = ar[vl];
        return;
    }
    int m = (vl + vr) >> 1;
    build(2 * v + 1, vl, m);
    build(2 * v + 2, m + 1, vr);
    t[v] = t[2 * v + 1] + t[2 * v + 2];
}

void push(int v, int vl, int vr)
{
    if (add[v])
    {
        if (vl != vr)
        {
            add[2 * v + 1] += add[v];
            add[2 * v + 2] += add[v];
        }
        t[v] += (vr - vl + 1) * add[v];
        add[v] = 0;
    }
}

ll sum(int v, int vl, int vr, int l, int r)
{
    push(v, vl, vr);
    if (l > r)
        return 0;
    else if (vl == l && vr == r)
        return t[v];
    int m = (vl + vr) >> 1;
    ll a = sum(2 * v + 1, vl, m, l, min(r, m));
    ll b = sum(2 * v + 2, m + 1, vr, max(l, m + 1), r);
    return (a + b);
}

void upd(int v, int vl, int vr, int l, int r, ll x)
{
    push(v, vl, vr);
    if (l > r)
        return;
    else if (vl == l && vr == r)
    {
        add[v] += x;
        push(v, vl, vr);
        return;
    }
    int m = (vl + vr) >> 1;
    upd(2 * v + 1, vl, m, l, min(r, m), x);
    upd(2 * v + 2, m + 1, vr, max(l, m + 1), r, x);
    t[v] = t[2 * v + 1] + t[2 * v + 2];
}

vector <ll> fenw;

void upd_fenw(int j, ll x)
{
    for (int i = j; i < fenw.size(); i += (i & (-i)))
        fenw[i] += x;
}

ll sum_fenw(int j)
{
    ll ans = 0;
    for (int i = j; i > 0; i -= (i & (-i)))
        ans += fenw[i];
    return ans;
}

vector <int> p, rnk;

void make(int v)
{
    p[v] = -1;
    rnk[v] = 1;
}

int par(int v)
{
    if (p[v] == -1)
        return v;
    else
        return (p[v] = par(p[v]));
}

void un(int a, int b)
{
    a = par(a); b = par(b);
    if (a != b)
    {
        if (rnk[a] > rnk[b])
            swap(a, b);
        p[a] = b;
        rnk[b] += rnk[a];
    }
}

struct edge
{
    ll w;
    int u;
    edge(int u, ll w) : u(u), w(w) {}
};

vector <ll> dist;
vector <bool> used;
vector < vector <edge> > gr;

void dfs(int v)
{
    used[v] = 1;
    for (auto to : gr[v])
    {
        if (!used[to.u])
        {
            dfs(to.u);
        }
    }
}

void dijkstra(int s)
{
    for (auto &i : dist)
        i = inf;
    dist[--s] = 0;
    set < pair <ll, int> > st;
    st.insert(make_pair(0, s));
    while (!st.empty())
    {
        int v = (*st.begin()).second;
        st.erase(st.begin());
        for (auto to : gr[v])
        {
            ll w = to.w;
            int u = to.u;
            if (dist[u] > dist[v] + w)
            {
                dist[u] = dist[v] + w;
                st.insert(make_pair(dist[u], u));
            }
        }
    }
}

vector <int> prefix_function(string &s)
{
    int n = s.size();
    vector <int> pref(n);
    for (int i = 1; i < n; ++i)
    {
        int j = p[i - 1];
        while (s[i] != s[j] && j > 0)
            j = p[j - 1];
        if (s[i] == s[j])
            ++j;
        p[i] = j;
    }
    return p;
}

vector <int> z_function(string &s)
{
    int n = s.size();
    vector <int> z(n);
    int l = 0, r = 0;
    for (int i = 1; i < n; ++i)
    {
        if (i <= r)
            z[i] = min(z[i - l], r - i + 1);
        else
            while (i + z[i] < n && s[z[i]] == s[i + z[i]])
                ++z[i];
        if (i + z[i] - 1 > r)
            l = i, r = i + z[i] - 1;
    }
    return z;
}

vector <int> eratosphene(int n)
{
    vector <int> prime(2 * n); /// 0 - prime, 1 - not prime
    prime[0] = prime[1] = 1;
    for (ll i = 2; i * i <= 2 * n; ++i)
        if (!prime[i])
            if (i * i <= 2 * n)
                for (ll j = i * i; j <= 2 * n; j += i)
                    prime[j] = 1;
    return prime;
}

ll bin_pow(ll a, ll n)
{
    ll res = 1;
    while (n)
    {
        if (n & 1)
            res *= a;
        a *= a;
        n >>= 1;
    }
    return res;
}

ll hsh(string &s, ll mod = 1e9 + 7)
{
    ll t = 0;
    ll prime = 101;
    vector <ll> pows(s.size() + 1);
    pows[0] = 1; pows[1] = prime;
    for (int i = 2; i < s.size() + 1; ++i)
        pows[i] = (pows[i - 1] * prime) % mod;
    for (int i = 0; i < s.size(); ++i)
    {
        t += ((s[i] - 'a' + 1) * pows[i]) % mod;
        t %= mod;
    }
    return t % mod;
}

ll gcd(ll a, ll b)
{
    while (a && b)
    {
        if (a >= b)
            a %= b;
        else
            b %= a;
    }
    return (a + b);
}

int main()
{
    ios_base::sync_with_stdio(false);
//    ifstream cin("input.txt");
//    ofstream cout("output.txt");
    int n, m;
    cin >> n >> m;
    gr.resize(n); dist.resize(n);
    while (m--)
    {
        ll w;
        int v, u;
        cin >> v >> u >> w;
        --v; --u;
        gr[v].push_back(edge(u, w));
        gr[u].push_back(edge(v, w));
    }
    dijkstra(1);
    for (auto i : dist)
        cout << i << " ";
}
