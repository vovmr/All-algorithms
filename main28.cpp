#include <bits/stdc++.h>
#define ll long long
#define ld long double
#define all(x)              (x).begin(), (x).end()
#define inf                 1e18
#define PI                  -2 * atan2(-1, 0)

using namespace std;

struct tree
{
    ll sum = 0;
    tree *l, *r;
    tree(ll val) { l = r = nullptr; sum = val; }
    tree(tree *l, tree *r) { this->l = l; this->r = r; this->sum = l->sum + r->sum; }
};

vector <ll> ar, cur_mask;

tree * build(int vl, int vr)
{
    if (vl == vr)
        return new tree(cur_mask[vl]);
    int m = (vl + vr) >> 1;
    return new tree(
                    build(vl, m),
                    build(m + 1, vr)
    );
}

ll sum(tree *v, int vl, int vr, int l, int r)
{
    if (l > r)
        return 0;
    else if (vl == l && vr == r)
        return v->sum;
    int m = (vl + vr) >> 1;
    return sum(v->l, vl, m, l, min(r, m)) + sum(v->r, m + 1, vr, max(l, m + 1), r);
}

tree * upd(tree *v, int vl, int vr, int pos, ll x)
{
    if (vl == vr)
        return new tree(x);
    int m = (vl + vr) >> 1;
    if (pos <= m)
        return new tree(upd(v->l, vl, m, pos, x), v->r);
    else
        return new tree(v->l, upd(v->r, m + 1, vr, pos, x));
}

int main()
{
    int n;
    cin >> n;
    map <ll, int> lst;
    vector < tree * > pdo(n);
    ar.resize(n); cur_mask.resize(n);
    for (int i = 0; i < n; ++i)
        cin >> ar[i];
    cur_mask[0] = 1;
    pdo[0] = build(0, n - 1); lst[ar[0]] = 1;
    for (int i = 1; i < n; ++i)
    {
        pdo[i] = new tree(0);
        cur_mask[i] = 1;
        pdo[i] = upd(pdo[i - 1], 0, n - 1, i, cur_mask[i]);
        if (lst[ar[i]])
        {
            cur_mask[lst[ar[i]] - 1] = 0;
            tree *cur = upd(pdo[i], 0, n - 1, lst[ar[i]] - 1, 0);
            pdo[i] = cur;
        }
//        pdo[i] = build(0, n - 1);
        lst[ar[i]] = i + 1;
    }
    int q;
    cin >> q;
    while (q--)
    {
        int l, r;
        cin >> l >> r;
        --l; --r;
        cout << sum(pdo[r], 0, n - 1, l, r) << endl;
    }
    return 0;
}
