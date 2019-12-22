/// solution to 484E on Codeforces by vovamr, 21.12.2019 20:32
/// an example of using persistent segment tree with binary search
 
#include <bits/stdc++.h>
#define ll long long
#define ld long double
#define all(x)              (x).begin(), (x).end()
#define inf                 1e18
#define PI                  -2 * atan2(-1, 0)
 
using namespace std;
 
vector <int> ar;
 
struct st {
    int suffix, prefix, ans, vl, vr;
    st() : suffix(0), prefix(0), ans(0), vl(-1), vr(-1) {}
    st(int x, int vl) : suffix(x), prefix(x), ans(x), vl(vl), vr(vl) {}
    st(st l, st r) {
        this->prefix = max(l.prefix, ((l.prefix == l.vr - l.vl + 1) ? l.prefix + r.prefix : 0));
        this->suffix = max(r.suffix, ((r.suffix == r.vr - r.vl + 1) ? r.suffix + l.suffix : 0));
        this->ans = max({l.ans, r.ans, l.suffix + r.prefix});
        this->vl = l.vl, this->vr = r.vr;
    }
};
 
struct tree {
    st node;
    tree *l, *r;
    tree() : l(nullptr), r(nullptr), node(st()) {}
    tree(int x, int vl) : l(nullptr), r(nullptr), node(st(x, vl)) {}
    tree(tree *l, tree *r) : l(l), r(r), node(st(l->node, r->node)) {}
};
 
tree * build(int vl, int vr) {
    if (vl == vr) {
        return new tree(ar[vl], vl);
    }
    int m = (vl + vr) >> 1;
    return new tree(build(vl, m),
                    build(m + 1, vr)
    );
}
 
tree * upd(tree *v, int vl, int vr, int pos, int x) {
    if (vl == vr) {
        return new tree(x, vl);
    }
    int m = (vl + vr) >> 1;
    if (pos <= m) {
        return new tree(upd(v->l, vl, m, pos, x),
                        v->r
        );
    }
    else {
        return new tree(v->l,
                        upd(v->r, m + 1, vr, pos, x)
        );
    }
}
 
st get_ans(tree *v, int vl, int vr, int l, int r) {
    if (l > r) {
        return st();
    }
    else if (vl == l && vr == r) {
        return v->node;
    }
    int m = (vl + vr) >> 1;
    st a = get_ans(v->l, vl, m, l, min(r, m));
    st b = get_ans(v->r, m + 1, vr, max(l, m + 1), r);
    return st(a, b);
}
 
int main() {
    ios_base::sync_with_stdio(false);
//    ifstream cin("input.txt");
//    ofstream cout("output.txt");
    int n;
    cin >> n;
    vector <int> v(n);
    map <int, int> num;
    map < int, vector <int> > mp;
    vector < tree * > pdo(n + 1, new tree()); ar.resize(n); pdo[0] = build(0, n - 1);
    for (int i = 0; i < n; ++i) {
        cin >> v[i];
        mp[v[i]].push_back(i);
    }
    int cur_pos = 1;
    for (auto it = mp.rbegin(); it != mp.rend(); ++it) {
        int fir = 1;
        vector <int> cur = it->second;
        while (!cur.empty()) {
            if (fir) {
                pdo[cur_pos] = upd(pdo[cur_pos - 1], 0, n - 1, cur.back(), 1);
                fir = 0;
            }
            else {
                pdo[cur_pos] = upd(pdo[cur_pos], 0, n - 1, cur.back(), 1);
            }
            cur.pop_back();
        }
        num[it->first] = cur_pos; ++cur_pos;
    }
    auto it = num.rbegin();
    vector <int> pos(num.size());
    for (int i = 0; i < num.size(); ++i) {
        pos[i] = it->first;
        ++it;
    }
    int q;
    cin >> q;
    while (q--) {
        int _l, _r, w;
        cin >> _l >> _r >> w; --_l; --_r;
        int l = 0, r = num.size() - 1, mid, ans = -1;
        while (l <= r) {
            mid = (l + r) >> 1;
            int cur_h = pos[mid];
            if (get_ans(pdo[num[cur_h]], 0, n - 1, _l, _r).ans >= w) {
                r = mid - 1, ans = pos[mid];
            }
            else {
                l = mid + 1;
            }
        }
        cout << ans << endl;
    }
}
