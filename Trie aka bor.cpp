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

struct bor {
	int end;
	bor *parent;
	bor *node[2];
	bor() { end = 0; node[0] = node[1] = nullptr; parent = nullptr; }
};

void add(bor *trie, ll x) {
	bor *cur = trie;
	bitset <40> bits(x);
	for (int i = 39; i >= 0; --i) {
		if (cur->node[bits[i]] == nullptr) {
			cur->node[bits[i]] = new bor();
			cur->node[bits[i]]->parent = cur;
		}
		cur = cur->node[bits[i]];
	}
	++cur->end;
}

ll get_ans(bor *trie, ll x) {
	ll ans = 0;
	bor *cur = trie;
	bitset <40> bits(x);
	for (int i = 39; i >= 0; --i) {
		if (cur->node[bits[i] ^ 1] != nullptr) {
			ans += (1LL << i);
			cur = cur->node[bits[i] ^ 1];
		}
		else {
			cur = cur->node[bits[i]];
		}
	}
	return ans;
}

void del(bor *trie, ll x) {
	bor *cur = trie;
	bitset <40> bits(x);
	for (int i = 39; i >= 0; --i) {
		assert(cur->node[bits[i]] != nullptr);
		cur = cur->node[bits[i]];
	}
	if (cur->end > 1) {
		--cur->end;
		return;
	}
	bor *parent = cur->parent;
	while (1) {
		if (cur->node[0] != nullptr || cur->node[1] != nullptr || cur->parent == nullptr) {
			break;
		}
		bool left = (parent->node[0] == cur);
		if (left) {
			delete cur;
			parent->node[0] = nullptr;
			cur = parent; parent = cur->parent;
		}
		else {
			delete cur;
			parent->node[1] = nullptr;
			cur = parent; parent = cur->parent;
		}
	}
}

void solve() {
	int q;
	cin >> q;
	bor *trie = new bor(); add(trie, 0);
	while (q--) {
		ll x;
		char t;
		cin >> t >> x;
		if (t == '+') add(trie, x);
		else if (t == '-') del(trie, x);
		else {
			cout << get_ans(trie, x) << '\n';
		}
	}
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
//	ifstream cin("input.txt");
//	ofstream cout("output.txt");
	int q = 1; // cin >> q;
	while (q--) {
		solve();
	}
}
