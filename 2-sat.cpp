#include <bits/stdc++.h>
#define fi first
#define se second
#define ll long long
#define ld long double
#define all(x)              (x).begin(), (x).end()
#define inf                 1e18

using namespace std;

vector <int> used, ord, who;
vector < vector <int> > gr, gt;

void dfs(int v) {
	used[v] = 1;
	for (auto to : gr[v]) {
		if (!used[to]) dfs(to);
	}
	ord.push_back(v);
}

void dfs1(int v, int c) {
	who[v] = c;
	for (auto to : gt[v]) {
		if (who[to] == -1) dfs1(to, c);
	}
}

void solve() {
	int n, m;
	cin >> n >> m;
	gr.resize(2 * m); gt.resize(2 * m); used.resize(2 * m); who.resize(2 * m, -1);

	auto inverse = [&](int v) {
		if (v < m) return v + m;
		return v - m;
	};

	for (int i = 0; i < n; ++i) {
		char a, b; int v, u;
		cin >> a >> v >> b >> u; --v; --u;

		if (a == '-') v = inverse(v);
		if (b == '-') u = inverse(u);
		gr[inverse(v)].push_back(u);
		gr[inverse(u)].push_back(v);

	}
	for (int i = 0; i < 2 * m; ++i) {
		for (auto to : gr[i]) gt[to].push_back(i);
	}

	for (int i = 0; i < 2 * m; ++i) {
		if (!used[i]) dfs(i);
	}

	int c = 1;
	for (int i = ord.size() - 1; ~i; --i) {
		if (who[ord[i]] == -1) {
			dfs1(ord[i], c);
			++c;
		}
	}
	for (int i = 0; i < m; ++i) {
		if (who[i] == who[inverse(i)]) {
			cout << "IMPOSSIBLE";
			return;
		}
	}
	for (int i = 0; i < m; ++i) {
		if (who[i] > who[inverse(i)]) cout << "+ ";
		else cout << "- ";
	}
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
//	ifstream cin("input.txt");
//	ofstream cout("output.txt");
	int q = 1; // cin >> q;
	while (q--) solve();
}

