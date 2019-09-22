#include <bits/stdc++.h>
#define ll long long
#define ld long double
#define all(x)              (x).begin(), (x).end()
#define inf                 1e18
#define PI                  -2 * atan2(-1, 0)

using namespace std;

ll dp[35][32], dp1[35][32][2];

int main()
{
    ios_base::sync_with_stdio(false);
//    ifstream cin("input.txt");
//    ofstream cout("output.txt");
    int n, k1;
    cin >> n >> k1;
    ll now = n;
    deque <int> cur;
    while (now)
    {
        cur.push_front(now % 2);
        now >>= 1;
    }
    dp[0][0] = 1;
    for (int i = 1; i < cur.size(); ++i)
    {
        for (int k = 0; k < i; ++k)
        {
            if (k == i || k == 0)
            {
                dp[i][k] = 1;
            }
            else
            {
                if (!(i > 1 && k == i - 1))
                    dp[i][k] += dp[i - 1][k];
                if (k > 0)
                    dp[i][k] += dp[i - 1][k - 1];
            }
        }
    }
    dp1[0][0][0] = 1;
    for (int i = 1; i <= cur.size(); ++i)
    {
        for (int k = 0; k < i; ++k)
        {
            if (cur[i - 1] == 1)
            {
                dp1[i][k][1] += dp1[i - 1][k][1];
                dp1[i][k][0] += dp1[i - 1][k][0];
                if (k > 0)
                {
                    dp1[i][k][1] += dp1[i - 1][k - 1][1];
                    dp1[i][k][1] += dp1[i - 1][k - 1][0];
                }
            }
            else
            {
                if (k > 0)
                {
                    dp1[i][k][0] += dp1[i - 1][k - 1][0];
                    dp1[i][k][1] += dp1[i - 1][k - 1][1];
                }
                dp1[i][k][1] += dp1[i - 1][k][1];
            }
        }
    }
    ll ans = 0;
    for (int i = 1; i < cur.size(); ++i)
    {
        for (int j = 0; j <= i; ++j)
        {
            ans += (dp[i][j] * (((j != 0) ? 1 + ((j - 1) / k1) : 0)));
        }
    }
    for (int j = 1; j <= cur.size(); ++j)
    {
        ans += (dp1[cur.size()][j][0] * (1 + ((j - 1) / k1)));
        ans += (dp1[cur.size()][j][1] * (1 + ((j - 1) / k1)));
    }
//    for (auto i : dp)
//    {
//        for (int j = 0; j < 32; ++j)
//        {
//            if (i[j] == 0)
//                break;
//            cout << i[j] << " ";
//        }
//        cout << endl;
//    }
    cout << ans;
}
