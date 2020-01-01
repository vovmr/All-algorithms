#include <bits/stdc++.h>

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

#define ll long long
#define ld long double
#define all(x)              (x).begin(), (x).end()
#define inf                 1e18

using namespace std;
using namespace __gnu_pbds;

typedef tree <ll, null_type, less <ll>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
//    ifstream cin("input.txt");
//    ofstream cout("output.txt");
    int n;
    cin >> n;
    ordered_set st;
    for (int i = 0; i < n; ++i) {
        int x;
        cin >> x;
        st.insert(x);
    }
    int q;
    cin >> q;
    while (q--) {
        int type;
        cin >> type;
        if (type == 1) {
            int x;
            cin >> x; /// inserts x
            st.insert(x);
        }
        else if (type == 2) {
            int x;
            cin >> x; /// deletes the element which is equal to x
            st.erase(x);
        }
        else if (type == 3) {
            int k;
            cin >> k; --k; /// prints the k-th order statistics on out set (0-indexed)
            cout << *st.find_by_order(k) << endl;
        }
        else {
            int x;
            cin >> x; /// prints the quantity of elements less than x
            cout << st.order_of_key(x) << endl;
        }
    }
}
