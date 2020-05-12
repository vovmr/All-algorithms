/// Codechef task 'Construct Array' (CARR)
/// here matrixrs are used for dp of the following type:
/// dp[i][2] = dp[i - 1][1]
/// dp[i][1] = (m - 1) * dp[i - 1][1] + (m - 1) * dp[i - 1][2]
/// We can see that both dp[i][1] and dp[i][2] are just a linear combination of dp[i - 1][1] ans dp[i - 1][2]
/// So we want to find such matrix A that ( dp[i - 1][1], dp[i - 1][2] ) * A = ( dp[i][1], dp[i][2] )
/// Like in Fibonacci numbers we create a table
///                dp[i][1]  dp[i][2]
/// dp[i - 1][1]     m - 1       1
/// dp[i - 1][2]     m - 1       0
/// So A = (m - 1; 1)
///        (m - 1; 0)
/// and out task is calculate (dp[1][1], dp[1][2]) * A^(n - 1) = (m; 0) * A^(n - 1) = (dp[n][1], dp[n][2]);
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

const ll mod = 1e9 + 7;

struct matrix {
        ll a[2][2];
        void cl() { memset(a, 0, sizeof(a)); }
        void make_one() { a[0][0] = a[1][1] = 1; }
};

matrix operator * (const matrix &a, const matrix &b) {
        matrix res; res.cl();
        for (int i = 0; i < 2; ++i) {
                for (int j = 0; j < 2; ++j) {
                        for (int k = 0; k < 2; ++k) {
                                ll cur = ((a.a[i][k] % mod) * (b.a[k][j] % mod)) % mod;

                                res.a[i][j] += cur;
                                if (res.a[i][j] >= mod) res.a[i][j] -= mod;
                        }
                }
        }
        return res;
}

matrix bp(matrix a, ll n) {
        matrix res; res.cl(); res.make_one();
        while (n) {
                if (n & 1) res = res * a;
                a = a * a;
                n >>= 1;
        }
        return res;
}

void solve() {
        ll n, m;
        cin >> n >> m;

        matrix mt; mt.cl();
        mt.a[0][0] = mt.a[1][0] = m - 1; mt.a[0][1] = 1;

        mt = bp(mt, n - 1);
        ll res = ((m % mod) * (mt.a[0][0] % mod)) % mod;
        res += (((m % mod) * (mt.a[0][1] % mod)) % mod);
        cout << (res % mod) << '\n';

}

int main() {
        ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
//      freopen("input.txt", "r", stdin);
//      freopen("output.txt", "w", stdout);
        int q = 1; cin >> q;
        while (q--) {
                solve();
        }
}
