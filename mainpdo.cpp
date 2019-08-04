#include <bits/stdc++.h>
#define ll long long
#define ld long double
#define all(x)              (x).begin(), (x).end()
#define inf                 1e18
#define PI                  -2 * atan2(-1, 0)

using namespace std;

struct tree
{
    tree *l, *r;
    ll sum = 0, add = 0;
    tree(ll val) { l = r = nullptr; sum = val; add = 0; }
    tree(tree *l, tree *r) { this->l = l; this->r = r; this->sum = l->sum + r->sum; }
};

vector <ll> ar, cur_mask;

tree * build(int vl, int vr)
{
    if (vl == vr)
        return new tree(ar[vl]);
    int m = (vl + vr) >> 1;
    return new tree(
                    build(vl, m),
                    build(m + 1, vr)
    );
}

void push(tree *v, int vl, int vr)
{
    if (v->add)
    {
        if (vl != vr)
        {
            v->l->add += v->add;
            v->r->add += v->add;
        }
        v->sum += (vr - vl + 1) * v->add;
        v->add = 0;
    }
}

ll sum(tree *v, int vl, int vr, int l, int r)
{
    push(v, vl, vr);
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

tree * upd1(tree *v, int vl, int vr, int l, int r, ll x)
{
    push(v, vl, vr);
    if (l > r)
        return new tree(v->l, v->r);
    else if (vl == l && vr == r)
    {
        v->add += x;
        push(v, vl, vr);
        return new tree(v->l, v->r);
    }
    int m = (vl + vr) >> 1;
    return new tree(
                    upd1(v->l, vl, m, l, min(r, m), x),
                    upd1(v->r, m + 1, vr, max(l, m + 1), r, x)
    );
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
//    for (int i = 1; i < n; ++i)
//    {
//        pdo[i] = new tree(0);
//        cur_mask[i] = 1;
//        pdo[i] = upd(pdo[i - 1], 0, n - 1, i, cur_mask[i]);
//        if (lst[ar[i]])
//        {
//            cur_mask[lst[ar[i]] - 1] = 0;
//            tree *cur = upd(pdo[i], 0, n - 1, lst[ar[i]] - 1, 0);
//            pdo[i] = cur;
//        }
////        pdo[i] = build(0, n - 1);
//        lst[ar[i]] = i + 1;
//    }
    int cnt = 0;
    int q;
    cin >> q;
    while (q--)
    {
        ll x;
        int type, l, r, k;
        cin >> type;
        if (type == 1)
        {
            cin >> k >> l >> r;
            --l; --r;
            cout << sum(pdo[k - 1], 0, n - 1, l, r) << endl;
        }
        else if (type == 2)
        {
            cin >> l >> x; --l;
            pdo[cnt + 1] = upd(pdo[cnt], 0, n - 1, l, x);
            ++cnt;
        }
        else if (type == 3)
        {
            cin >> l >> r >> x;
            --l; --r;
            pdo[cnt + 1] = upd1(pdo[cnt], 0, n - 1, l, r, x);
        }
//        int l, r;
//        cin >> l >> r;
//        --l; --r;
//        cout << sum(pdo[r], 0, n - 1, l, r) << endl;
    }
    return 0;
}
