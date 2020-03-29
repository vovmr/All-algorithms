/// There are N <= 1e5 people in a city and each one has two parametres:
/// a[i] - his speed
/// b[i] - time to wake him up
/// The time to go from city i to city j for k-th person if exactly (a[k] * (i - j) + b[k])
/// But every person can ask someone to go to the first city instead of him
/// So the resulting time if i-th person asks j-th person to go instead of him is
/// ans[i] = a[i] * (i - j) + b[i] + b[j] + ans[j]
/// To calculate this dp faster we use The Convex Hull Trick
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

struct line {
	ld x, x1;
	pair <ll, ll> k;
	line(ld x, ld x1, pair <ll, ll> k) : x(x), x1(x1), k(k) {}
};

ld intersection(line &a, line &b) {
	ld cur = ((double)(b.k.second - a.k.second) / (double)(a.k.first - b.k.first));
	return cur;
}

vector <line> lines;

void add_line(int j, vector <ll> &dp) {
	if (lines.size() == 0) {
		lines.push_back(line(-inf, inf, {0, 0}));
		if (j == 0) {
			return;
		}
	}
	line cur = line(0, 0, {-j, dp[j]});
	while (lines.size() >= 2) {
		ld cur1 = intersection(lines.back(), lines[lines.size() - 2]), cur2 = intersection(lines.back(), cur);
		if (cur1 >= cur2) {
			lines.pop_back();
		}
		else {
			break;
		}
	}
	ld cur1 = intersection(lines.back(), cur);
	lines.back().x1 = cur1;
	lines.push_back(line(cur1, inf, {-j, dp[j]}));
}

void calc_dp() {
	srand(time(NULL));
	int n;
	cin >> n;
	vector <ll> a(n), b(n), dp(n + 1);
	for (auto &i : a) {
		i = rand() % 10;
	}
	for (auto &i : b) {
		i = rand() % 10;
	}
	ld time = clock();
	add_line(0, dp);
	for (int i = 1; i <= n; ++i) {
		if (i == 1) {
			dp[i] = a[i - 1] * i + b[i - 1];
			add_line(i, dp);
			continue;
		}
		ll pre_ans = a[i - 1] * i + b[i - 1];
		int l = 0, r = lines.size() - 1, mid, ans = 0;
		while (l <= r) {
			mid = (l + r) >> 1;
			if (lines[mid].x1 >= a[i - 1]) {
				ans = mid, r = mid - 1;
			}
			else {
				l = mid + 1;
			}
		}
		pre_ans += ((a[i - 1] * lines[ans].k.first + lines[ans].k.second));
		dp[i] = pre_ans;
		add_line(i, dp);
	}
	cout << "Anses:" << endl;
	for (auto i : dp) {
		cout << i << " ";
	}
	cerr << endl << (double)(clock() - time) << endl;
//	cout << "Convex Hull Trick dp:" << endl;
//	for (auto i : dp) {
//		cout << i << " ";
//	}                             
//	cout << endl;
/// Brute dp solution working in O(n^2)
//	dp.assign(n + 1, 0);
//	for (int i = 1; i <= n; ++i) {
//		ll mn = inf;
//		for (int j = 0; j < i; ++j) {
//			mn = min(mn, a[i - 1] * (i - j) + b[i - 1] + dp[j]);
//		}
//		dp[i] = mn;
//	}
//	cout << "Brute dp:" << endl;
//	for (auto i : dp) {
//		cout << i << " ";
//	}
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
//	ifstream cin("input.txt");
//	ofstream cout("output.txt");
	calc_dp();
}
