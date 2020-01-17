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

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

vector <string> v;
vector < pair <string, int> > ar;
vector < vector <ll> > mx_len, pre_hash;

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

ll calc_energy(vector <int> pos1) {
    ll ans = ar[pos1[0]].first.size();
    for (int i = 1; i < pos1.size(); ++i) {
        ans += ar[pos1[i]].first.size();
        ans -= mx_len[pos1[i - 1]][pos1[i]];
    }
    return ans;
}

struct otzhig {
    ll energy = 0;
    vector <int> pos;
    otzhig() : energy(0), pos(vector <int> (0)) {}
    otzhig(vector <int> pos1) : pos(pos1), energy(calc_energy(pos1)) {}
};

double probability(double delta, double temp, double e = 2.718281828459045) {
    return (pow(e, -1.0 * delta / temp));
}

otzhig generate_new(otzhig cur) {
    otzhig now = cur;
    if (cur.pos.size() == 1) {
        return now;
    }
    vector <int> ind(cur.pos.size()); iota(all(ind), 0); shuffle(all(ind), rng);
    int a = ind[0], b = ind[1];
    swap(now.pos[a], now.pos[b]); now.energy = calc_energy(now.pos);
    return now;
};

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
//    ifstream cin("input.txt");
//    ofstream cout("output.txt");
    for (int num_test = 1; num_test <= 10; ++num_test) {
        ifstream cin("INPUT" + to_string(num_test) + ".txt");
        ofstream cout("output" + to_string(num_test) + ".txt");
        ll mod = 1e9 + 7;
        vector <ll> pows(1e6 + 1); pows[0] = 1;
        for (int i = 1; i < pows.size(); ++i) {
            pows[i] = (pows[i - 1] * 101) % mod;
        }
        int n;
        cin >> n;
        v.resize(n);
        vector <bool> del(n, 0);
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
        for (int i = 0; i < n; ++i) {
            if (!del[i]) {
                ar.push_back(make_pair(v[i], 0));
            }
        }
        n = ar.size();
        for (int i = 0; i < n; ++i) {
            ar[i].second = i;
        }
        pre_hash.resize(n); mx_len.resize(n, vector <ll> (n));
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
        vector <int> positions(n);
        for (int i = 0; i < n; ++i) {
            positions[i] = i;
        }
        int cnt = 1;
        otzhig cur(positions), mn(positions);
        double temp = 10000.0;
        while (temp > 0.001) {
            otzhig now = generate_new(cur);
            if (mn.energy > now.energy) {
                mn = now;
            }
            if (now.energy < cur.energy) {
                cur = now;
            }
            else {
                if (probability((double)now.energy - (double)cur.energy, temp) >= 0.5) {
                    cur = now;
                }
            }
            temp = (0.99 * temp); ++cnt;
        }
        string ans = ar[mn.pos[0]].first;
        for (int i = 1; i < n; ++i) {
            for (int j = mx_len[mn.pos[i - 1]][mn.pos[i]]; j < ar[mn.pos[i]].first.size(); ++j) {
                ans += ar[mn.pos[i]].first[j];
            }
        }
        cout << ans << endl;
        v.clear(); ar.clear(); pre_hash.clear(); mx_len.clear();
        cin.clear();
    }
}
