#include <bits/stdc++.h>
#define ll long long
#define ld long double
#define all(x)              (x).begin(), (x).end()
#define inf                 1e18
#define PI                  -2 * atan2(-1, 0)

using namespace std;

bool kmp(string &a, string &b) {
    string res = a + "#" + b;
    int n = (int)res.size();
    vector <int> p(n);
    for (int i = 1; i < n; ++i) {
        int j = p[i - 1];
        while (res[i] != res[j] && j > 0) {
            j = p[j - 1];
        }
        if (res[i] == res[j]) {
            ++j;
        }
        p[i] = j;
        if (p[i] == a.size()) {
            return 1;
        }
    }
    return 0;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    ifstream cin("INPUT10.TXT");
    ofstream cout("output10.txt");
    ll mod = 1e9 + 7;
    vector <ll> pows(1e6 + 1); pows[0] = 1;
    for (int i = 1; i < pows.size(); ++i) {
        pows[i] = (pows[i - 1] * 101) % mod;
    }
    int n;
    cin >> n;
    vector <bool> del(n, 0);
    vector <string> v(n);
    for (auto &i : v) {
        cin >> i;
    }
    sort(all(v));
    auto it = unique(all(v));
    v.resize(distance(v.begin(), it));
    n = v.size();
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i != j && v[i] != v[j]) {
                if (kmp(v[i], v[j])) {
                    del[i] = 1;
                }
            }
        }
    }
    vector < pair <string, int> > ar;
    for (int i = 0; i < n; ++i) {
        if (!del[i]) {
            ar.push_back(make_pair(v[i], 0));
        }
    }
    n = ar.size();
    for (int i = 0; i < n; ++i) {
        ar[i].second = i;
    }
    vector < vector <ll> > pre_hash(n), mx_len(n, vector <ll> (n));
    for (int i = 0; i < n; ++i) {
        pre_hash[i].resize(ar[i].first.size() + 1);
        pre_hash[i][1] = ar[i].first[0] - 'a' + 1;
        for (int j = 2; j <= ar[i].first.size(); ++j) {
            pre_hash[i][j] = (pre_hash[i][j - 1] + (((ar[i].first[j - 1] - 'a' + 1) * pows[j - 1]) % mod)) % mod;
        }
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i != j) {
                ll mn = min(ar[i].first.size(), ar[j].first.size()), ans = 0;
                for (int z = 1; z <= mn; ++z) {
                    ll hsh = pre_hash[j][z];
                    int m = ar[i].first.size();
                    ll hsh1 = (pre_hash[i][m] - pre_hash[i][m - z] + 1000 * mod) % mod;
                    if (hsh1 == ((hsh * pows[m - z]) % mod)) {
                        ans = max(ans, 1LL * z);
                    }
                }
                mx_len[i][j] = ans;
            }
            else {
                mx_len[i][j] = 0;
            }
        }
    }
    vector < vector <int> > dp((1 << n), vector <int> (n, INT_MAX)), p((1 << n), vector <int> (n));
    for (int i = 0; i < n; ++i) {
        dp[0][i] = 0;
    }
    for (ll mask = 1; mask < (1 << n); ++mask) {
        int cnt = 0, pos = 0;
        for (int i = 0; i < n; ++i) {
            cnt += ((mask & (1 << i)) != 0);
            if (mask & (1 << i)) {
                pos = i;
            }
        }
        if (cnt == 1) {
            dp[mask][pos] = ar[pos].first.size();
        }
        for (int lst = 0; lst < n; ++lst) {
            if (mask & (1 << lst)) {
                for (int j = 0; j < n; ++j) {
                    if (!(mask & (1 << j))) {
                        if (dp[mask + (1 << j)][j] > dp[mask][lst] + ar[j].first.size() - mx_len[lst][j]) {
                            dp[mask + (1 << j)][j] = dp[mask][lst] + ar[j].first.size() - mx_len[lst][j];
                            p[mask + (1 << j)][j] = lst;
                        }
                    }
                }
            }
        }
    }
    ll mn = inf, need = 0, cur_mask = (1 << n) - 1;
    for (int i = 0; i < n; ++i) {
        if (dp[(1 << n) - 1][i] < mn) {
            mn = dp[(1 << n) - 1][i];
            need = i;
        }
    }
    int cur_pos = n - 1;
    vector <int> order(n); order[cur_pos] = need; --cur_pos;
    while (cur_pos >= 0) {
        order[cur_pos] = p[cur_mask][order[cur_pos + 1]];
        cur_mask -= (1 << (order[cur_pos + 1]));
        --cur_pos;
    }
    string real_ans = ar[order[0]].first;
    for (int i = 1; i < n; ++i) {
        int cur_len = mx_len[order[i - 1]][order[i]];
        for (int j = cur_len; j < ar[order[i]].first.size(); ++j) {
            real_ans += ar[order[i]].first[j];
        }
    }
    cout << real_ans;
}
