#include <bits/stdc++.h>
#define ll long long
#define ld long double
#define all(x)              (x).begin(), (x).end()
#define inf                 1e18

using namespace std;

/// WARNING: PDO - Persistent Segment Tree

struct tree {
    /// As in normal PDO we store sum and also links to its sons, but not as pointers
    /// but as just indexes to the right array element
    /// Just as in casual segment tree
    /// In casual segment tree l = 2 * v + 1, r = 2 * v + 2, (0-indexed)
    int l, r, sum = 0;
    tree() : sum(0) {}
    tree(int x) : sum(x) {}
    tree(tree l, tree r) : sum(l.sum + r.sum) {}
};

int all;
/// All - the number of (already) created vertexes in PDO
/// We need it in order to create new vertexes in the update function
vector <tree> t;
vector <int> lst, root, ar;
/// lst - link to the previous version of this vertex, initially: lst[v] = v for all v
/// root - a list of our new roots
/// ar - initial array

void build(int v, int vl, int vr) { /// Build is almost the same as in usual persistent segment tree
    lst[v] = v;
    all = max(all, v + 1);
    if (vl == vr) {
        t[v].sum = ar[vl];
        return;
    }
    int m = (vl + vr) >> 1;
    build(2 * v + 1, vl, m);
    build(2 * v + 2, m + 1, vr);
    t[v] = tree(t[2 * v + 1], t[2 * v + 2]);
    t[v].l = 2 * v + 1, t[v].r = 2 * v + 2;
}

int get_ans(int v, int vl, int vr, int l, int r) { /// Sum is the same as in usual segment tree
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
    /// Here we create cur - the "previous version" vertex
    /// And update the last version
    if (vl == vr) { /// Checking if the current vertex is a leaf
        t[v].sum = val;
        return;
    }
    t[v] = t[cur]; /// Initially we store the previous information in our current vertex
    int m = (vl + vr) >> 1;
    if (pos <= m) {
        t[v].l = ++all;
        /// Here we don't set t[v].l to 2 * v + 1, because it'd be too much memory used (1)
        update(t[v].l, 2 * x + 1, vl, m, pos, val);
    }
    else {
        t[v].r = ++all; /// The same as (1)
        update(t[v].r, 2 * x + 2, m + 1, vr, pos, val);
    }
    t[v].sum = t[t[v].l].sum + t[t[v].r].sum; /// Updating the sum
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
//    ifstream cin("input.txt");
//    ofstream cout("output.txt");
    int n;
    cin >> n;
    ar.resize(n); lst.resize(4 * n + 1); t.resize(10 * n + 1);
    for (auto &i : ar) {
        cin >> i;
    }
    int q;
    cin >> q;
    root.resize(q + 1); root[0] = 0;
    build(0, 0, n - 1);
    int cnt = 1;
    while (q--) {
        int type;
        cin >> type;
        if (type == 1) {
            int k, l, r;
            cin >> k >> l >> r; --k; --l; --r;
            cout << get_ans(root[k], 0, n - 1, l, r) << endl;
        }
        else {
            int pos, x;
            cin >> pos >> x; --pos;
            root[cnt] = ++all;
            update(root[cnt], 0, 0, n - 1, pos, x); ++cnt;
        }
    }
}
