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

ll bm(ll a, ll b, ll mod) {
        if (b <= 1) return (a * b) % mod;
        ll ans = ( 2 * bm(a, b / 2, mod) ) % mod;
        if (b & 1) ( ans += a ) %= mod;
        return ans;
}

ll mult(ll a, ll b, ll m) { /// super fast mult with modulos upto 2^62 * 1.4
        ll q = (ll)((ld)a * (ld)b / (ld)m); ll r = a * b - q * m;
        while (r < 0) r += m;
        return r % m; /// it works because both a * b and q * m overflow "the same"
}

ll m = (ll)2000000000000000001;
mt19937_64 rng(chrono::system_clock::now().time_since_epoch().count());

void solve() {
        int it = 0;
        while (it < INT_MAX) {
                ll mod = rng() % m;
                ll a =  rng() % mod; ll b = rng() % mod;

                if (bm(a, b, mod) != mult(a, b, mod)) {
                        cout << a << " " << b << " " << mod << endl;
                        cout << bm(a, b, mod) << " " << mult(a, b, mod) << endl;
                        return;
                }
                if (it % 10000 == 0) {
                        cout << "Completed for " << it << endl;
                }
                ++it;
        }
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
//	ifstream cin("input.txt");
//	ofstream cout("output.txt");
	int q = 1; cin >> q;
	while (q--) {
		solve();
	}
}
