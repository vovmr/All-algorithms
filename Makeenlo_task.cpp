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

vector <ll> ar;
vector < vector <ll> > t, pf, sq;

void build(int v, int vl, int vr) {
        if (vl == vr) {
                t[v] = vector <ll> (1, ar[vl]);
                return;
        }
        int m = (vl + vr) >> 1;
        build(2 * v + 1, vl, m);
        build(2 * v + 2, m + 1, vr);
        merge(all(t[2 * v + 1]), all(t[2 * v + 2]), back_inserter(t[v]));
}

int get(int v, int vl, int vr, int l, int r, ll x) {
        if (l > r) return 0;
        else if (vl == l && vr == r) {
                int cnt = t[v].size() - (upper_bound(all(t[v]), x) - t[v].begin());
                ll sum = -cnt * x;
                if (cnt != 0) sum += pf[v][t[v].size() - cnt];
                return max(0LL, sum);
        }
        int m = (vl + vr) >> 1;
        return (get(2 * v + 1, vl, m, l, min(r, m), x) + get(2 * v + 2, m + 1, vr, max(l, m + 1), r, x));
}

ll magic(int v, int vl, int vr, int l, int r, ll val) {
        if (l > r) return 0;
        else if (vl == l && vr == r) {
                ll cnt = t[v].size() - (upper_bound(all(t[v]), val) - t[v].begin());
                ll ans = cnt * val * val + sq[v][0] - ((cnt == 0) ? 0 : sq[v][t[v].size() - cnt]);
                return ans;
        }
        int m = (vl + vr) >> 1;
        return (magic(2 * v + 1, vl, m, l, min(r, m), val) + magic(2 * v + 2, m + 1, vr, max(l, m + 1), r, val));
}

void solve() {
        int n;
        cin >> n;
        ar.resize(n); t.resize(4 * n); pf.resize(4 * n); sq.resize(4 * n);
        for (auto &i : ar) cin >> i;
        build(0, 0, n - 1);

        for (int i = 0; i < 4 * n; ++i) {
                pf[i].resize(t[i].size()); sq[i].resize(t[i].size());
                for (int j = t[i].size() - 1; j >= 0; --j) {
                        pf[i][j] = t[i][j];
                        sq[i][j] = t[i][j] * t[i][j];
                        if (j != t[i].size() - 1) {
                                pf[i][j] += pf[i][j + 1];
                                sq[i][j] += sq[i][j + 1];
                        }
                }
        }

        int q;
        cin >> q;z
        while (q--) {
                int l, r, k;
                cin >> l >> r >> k; --l; --r;

                ll low = -1e4, high = 1e4, mid, ans;
                while (low <= high) {
                        mid = (low + high) >> 1;
                        if (get(0, 0, n - 1, l, r, mid) <= k) {
                                ans = mid, high = mid - 1;
                        }
                        else {
                                low = mid + 1;
                        }
                }
                ll ok = magic(0, 0, n - 1, l, r, ans);
                int num = k - get(0, 0, n - 1, l, r, ans);
                cout << ok - (num * (2 * ans - 1)) << '\n';
        }
}

int main() {
        ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
        freopen("input.txt", "r", stdin);
//      freopen("output.txt", "w", stdout);
        int q = 1; // cin >> q;
        while (q--) {
                solve();
        }
}
