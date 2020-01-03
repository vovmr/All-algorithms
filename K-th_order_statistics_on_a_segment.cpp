#include <bits/stdc++.h>
#define ll long long
#define ld long double
#define all(x)              (x).begin(), (x).end()
#define inf                 1e18

using namespace std;

struct tree {
    int sum, l, r;
    tree() : sum(0) {}
};

int all;
vector <tree> t;
vector <int> lst, root, ar;

void build(int v, int vl, int vr) {
    lst[v] = v;
    all = max(all, v + 1);
    if (vl == vr) {
        t[v].sum = ar[vl];
        return;
    }
    int m = (vl + vr) >> 1;
    build(2 * v + 1, vl, m);
    build(2 * v + 2, m + 1, vr);
    t[v].l = 2 * v + 1, t[v].r = 2 * v + 2;
    t[v].sum = t[t[v].l].sum + t[t[v].r].sum;
}

int get_ans(int v, int vl, int vr, int l, int r) {
    if (l > r)
        return 0;
    else if (vl == l && vr == r)
        return t[v].sum;
    int m = (vl + vr) >> 1;
    int a = get_ans(t[v].l, vl, m, l, min(r, m));
    int b = get_ans(t[v].r, m + 1, vr, max(l, m + 1), r);
    return (a + b);
}

void update(int v, int x, int vl, int vr, int pos, int val) {
    int cur = lst[x]; lst[x] = v;
    if (vl == vr) {
        t[v].sum = val;
        return;
    }
    t[v] = t[cur];
    int m = (vl + vr) >> 1;
    if (pos <= m) {
        t[v].l = ++all;
        update(t[v].l, 2 * x + 1, vl, m, pos, val);
    }
    else {
        t[v].r = ++all;
        update(t[v].r, 2 * x + 2, m + 1, vr, pos, val);
    }
    t[v].sum = t[t[v].l].sum + t[t[v].r].sum;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
//    ifstream cin("input.txt");
//    ofstream cout("output.txt");
    int n, q;
    cin >> n >> q;
    ar.resize(n);
    root.resize(n + 1);
    lst.resize(4 * n + 1);
    t.resize(10 * n + 1);
    int cur = 1;
    build(0, 0, n - 1);
    vector < pair <int, int> > v(n);
    for (int i = 0; i < n; ++i) {
        cin >> ar[i];
        v[i].first = ar[i];
        v[i].second = i;
    }
    sort(all(v));
    for (int i = 0; i < n; ++i) {
        root[i + 1] = ++all;
        update(root[i + 1], 0, 0, n - 1, v[i].second, 1);
    }
    while (q--) {
        int k, l, r;
        cin >> k >> l >> r; --l; --r;
        int _l = 0, _r = n + 1, mid, ans = -1;
        while (_l <= _r) {
            mid = (_l + _r) >> 1;
            if (get_ans(root[mid], 0, n - 1, l, r) >= k) {
                ans = mid, _r = mid - 1;
            }
            else {
                _l = mid + 1;
            }
        }
        cout << k << "-th order statistics on [" << l + 1 << ", " << r + 1 << "] is " << v[ans - 1].first << endl;
    }
}
