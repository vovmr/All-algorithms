#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#define fi first
#define se second
#define ll long long
#define ld long double
#define all(x)              (x).begin(), (x).end()
#define inf                 1e18

using namespace std;

ll count(string &s) {
	ll ans = 0;
	int n = s.size();
	vector <int> d(n), d1(n);
	for (int i = 0, l = 0, r = -1; i < n; ++i) {
		int k = ((i > r) ? 1 : min(r - i + 1, d1[l + r - i]));
		while (i - k >= 0 && i + k < n && s[i - k] == s[i + k]) ++k;

		d1[i] = k--;
		if (i + k > r) l = i - k, r = i + k;
	}
	for (int i = 0, l = 0, r = -1; i < n; ++i) {
		int k = ((i > r) ? 0 : min(r - i + 1, d[l + r - i + 1]));
		while (i - k - 1 >= 0 && i + k < n && s[i - k - 1] == s[i + k]) ++k;

		d[i] = k--;
		if (i + k > r) l = i - k - 1, r = i + k;
	}
	for (auto i : d) ans += i;
	for (auto i : d1) ans += i;
	
	return ans;
}

mt19937_64 rng(chrono::system_clock::now().time_since_epoch().count());

struct otz {
	ll en = 0;
	int k = 0; string s = "";
	void upd() { en = count(s); }

	otz make_new() {
		map <char, int> mp;
		for (auto i : s) ++mp[i];

		vector < pair <int, char> > q;
		for (auto i : mp) q.push_back({i.se, i.fi});

		vector <char> most;
		sort(all(q)); reverse(all(q));
		for (int i = 0; i <= min((int)q.size() - 1, 1); ++i) most.push_back(q[i].se);

		int n = s.size();
		vector <int> pos(n); iota(all(pos), 0);

		shuffle(all(most), rng);
		sort(all(pos), [&](const int &a, const int &b) { return (abs((n / 2) - a) < abs((n / 2) - b)); });

		int j = 0;
		otz t{0, k + 1, s};
		for (int i = 0; i < n; ++i) {
			if (j == most.size()) break;
			if (t.s[pos[i]] != most[j]) {
				t.s[pos[i]] = most[j];
				break;
			}
			if (i == n - 1) i = 0, ++j;
		}
		t.upd();
		return t;
	}
};

constexpr ld e = 2.718281828459045;
void chMax(otz& a, const otz& b) { a = b; }

bool probability(ld delta, ld temp) {
	ld f = pow(e, 0.85 * delta / temp);
	return (f >= 0.5);
};

string solve(string &s, int &mxCh) {
	otz init{0, 0, s}; init.upd(); otz mx = init;
	
	vector <otz> can(mxCh + 1); can[0] = init;
	ld temp = 100000000000000.0, eps = 1, iter = 1;
	while (temp >= eps) {
		for (int i = 0; i < mxCh; ++i) {
			otz F = can[i].make_new();

			if (mx.en < F.en) mx = F;
			if (probability(F.en - can[i + 1].en, temp)) can[i + 1] = F;
		}
		temp = 0.99 * temp / iter; ++iter;
	}
	return mx.s;
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);

	for (int T : {10}) {
		ifstream in("input" + to_string(T) + ".txt");
		ifstream init("output" + to_string(T) + ".txt");

		string s;
		int n, t, k;
		in >> t >> n >> k >> s;

		string h; init >> h;
		string e = solve(s, k);
		for (int i = 0; i < -1; ++i) {
			string y = solve(s, k);
			if (count(y) > count(e)) e = y;
		}

		init.clear();
		if (count(e) <= count(h)) { continue; }
		ofstream cout("output" + to_string(T) + ".txt"); cout << e; in.clear();
	}
}
