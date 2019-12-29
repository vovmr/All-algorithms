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
    ifstream cin("INPUT1.TXT");
    ofstream cout("output.txt");
    srand(time(NULL));
    ll mod = 1e9 + 7;
    vector <ll> pows(1e6 + 1); pows[0] = 1;
    for (int i = 1; i < pows.size(); ++i) {
        pows[i] = (pows[i - 1] * 273) % mod;
    }
    int n;
    cin >> n;
    vector <bool> del(n, 0);
    vector <string> v(n);
    for (auto &i : v) {
        cin >> i;
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (!del[j] && i != j) {
                if (kmp(v[j], v[i])) {
                    del[j] = 1;
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
        pre_hash[i].resize(ar[i].first.size());
        pre_hash[i][0] = ar[i].first[0] - 'a' + 1;
        for (int j = 1; j < ar[i].first.size(); ++j) {
            pre_hash[i][j] = (pre_hash[i][j - 1] + (((ar[i].first[j] - 'a' + 1) * pows[j]) % mod)) % mod;
        }
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i != j) {
                ll l = 1, r = min(ar[i].first.size(), ar[j].first.size()), mid, ans = 0;
                while (l <= r) {
                    mid = (l + r) >> 1;
                    int m = ar[i].first.size();
                    ll hsh = pre_hash[j][mid - 1];
                    ll hsh1 = (pre_hash[i][m - 1] - pre_hash[i][m - 1 - mid]);
                    if (((hsh * pows[m - mid]) % mod) == hsh1) {
                        ans = mid, l = mid + 1;
                    }
                    else {
                        r = mid - 1;
                    }
                }
                mx_len[i][j] = ans;
            }
        }
    }
    sort(all(ar));
    ll mn = inf;
    string real_ans = "";
    vector < pair <string, int> > premutation(n);
    do {
        ll ans = 0;
        string cur = ar[0].first;
        for (int i = 0; i < n; ++i) {
            ans += ar[i].first.size();
        }
        for (int i = 1; i < n; ++i) {
            ans -= mx_len[ar[i - 1].second][ar[i].second];
        }
        if (ans < mn) {
            mn = ans;
            for (int i = 0; i < n; ++i) {
                premutation[i].first = ar[i].first;
                premutation[i].second = ar[i].second;
            }
        }
    } while (next_permutation(all(ar)));
    real_ans = premutation[0].first;
    for (int i = 1; i < n; ++i) {
        for (int j = mx_len[premutation[i - 1].second][premutation[i].second]; j < premutation[i].first.size(); ++j) {
            real_ans += premutation[i].first[j];
        }
    }
    cout << real_ans << " " << real_ans.size();
 }
