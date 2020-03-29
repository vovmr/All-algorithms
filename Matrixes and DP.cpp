#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#define ll long long
#define ld long double
#define all(x)              (x).begin(), (x).end()
#define inf                 1e18

using namespace std;
using namespace __gnu_pbds;

template <typename T>
using ordered_set = tree <T, null_type, less <T>, rb_tree_tag, tree_order_statistics_node_update>;

/**

To make this work I claim that

[ f[n - 2]; f[n - 1] ] * [ 0 1 ] = [ f[n - 1]; f[n] ];
			 [ 1 1 ]
This matrix is very cool, and let's describe how we can get it for
almost any 1D DP of the following type:

f[n] = a[0] * f[n - 1] + a[1] * f[n - 2] + ... + a[k] * f[n - k - 1]
For example we have two vectors (as matrixes):
( f[n - k - 1]; f[n - k]; ..; f[n - 1] ) -> (1) and we want to get a vector ( f[n - k + 1]; f[n - k + 2]; ..; f[n] ) -> (2)
Let's build the following table with k rows and k columns.

For better understanding let's come up with an example of such DP:
f[n] = 2 * f[n - 1] + 10 * f[n - 2] + f[n - 3] + 5 * f[n - 4]

So the table looks like:
         f[n - 3] f[n - 2] f[n - 1] f[n]
f[n - 4]     0        0        0     5
f[n - 3]     1        0        0     1
f[n - 2]     0        1        0     10
f[n - 1]     0        0        1     2 

We want to put numbers in that table in order to get a matrix A such that
( f[n - k - 1]; f[n - k]; ..; f[n - 1] ) * A = ( f[n - k + 1]; f[n - k + 2]; ..; f[n] )

So we just want the scalar multiplication of each column with the first collumn (which is our initial vector) to give us the first number in this column
which is just some f[j], we can easily do this.

This table understanding becomes more clear if we think how we actually multiplicate those matrixes:
Just scalar multiplication of out first column to some column of A, and we want to get the first row.


                [ 0 0 0 5  ]
In our case A = [ 1 0 0 1  ]
                [ 0 1 0 10 ]
                [ 0 0 1 2  ]

And we can see, that if we find the product of (1) and A, we will get exactly (2) for this DP formula
This works for ANY 1D DP formulas of such type.

So to find any Fibonacci Number or just f[n] for such DP
We only need to calculate v * A^(n - k) and get the correct number in this vector
v -- our initial values for f[1], f[2], .. , f[k]
And this can be done in O( k^3 * log2(n) ) using binary exponentiation.

Hope it's helped someone to understand DP matrix exponentiation better.
*/

const ll mod = 998244353;

vector < vector <ll> > mult(vector < vector <ll> > &a, vector < vector <ll> > &b) {
	if (a[0].size() != b.size()) {
		cout << "INCORRECT" << '\n';
		exit(0);
	}
	vector < vector <ll> > ans(a.size(), vector <ll> (b[0].size()));
	for (int i = 0; i < a.size(); ++i) {
		for (int j = 0; j < b[0].size(); ++j) {
			for (int k = 0; k < a[0].size(); ++k) {
				ans[i][j] += ((a[i][k] * b[k][j]) % mod);
				if (ans[i][j] >= mod) {
					ans[i][j] -= mod;
				}
			}
		}
	}
	return ans;
}

void solve() {

	vector < vector <ll> > fib{{1, 1}};
	vector < vector <ll> > v{{0, 1}, {1, 1}};

	ll n;
	cin >> n; --n;
	vector < vector <ll> > e{{1, 0}, {0, 1}};
	while (n) {
		if (n & 1) {
			e = mult(e, v);
		}
		v = mult(v, v);
		n >>= 1;
	}
	fib = mult(fib, e);
	cout << fib[0][1] << endl;

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
