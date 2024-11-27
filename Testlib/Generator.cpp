#include "testlib.h"
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#define rt return
#define pi pair<int, int>
#define pl pair<ll, ll>
#define pu pair<ull, ull>
#define int long long
#define ll long long
#define ull unsigned long long
#define endl '\n'
#define Endl endl
#define all(x) x.begin(), x.end()
#define all1(x) next(x.begin()), x.end()
#define debug(x) cerr << x << endl
#define lll __int128_t
#define ulll __uint128_t
using namespace std;
const int maxn = 1e5 + 50;
const int mod = 998244353;
const ll maxl = 2e18;
const int maxi = 1e9;
void solve()
{
    cout << 2<< endl;
    for (int j = 1; j <= 100; j++)
    {
        cout << (char)(rnd.next(0ll, 25ll) + 'a');
    }
    cout << endl;
    for (int j = 1; j <= 100; j++)
    {
        cout << (char)(rnd.next(0ll, 25ll) + 'a');
    }
    cout << endl;
    // vector<int> len(11);
    // int maxx = 200;
    // for (int i = 1; i <= 9; i++)
    // {
    //     if (maxx >= 1)
    //         len[i] = rnd.next(1ll, min(40ll,maxx));
    //     maxx -= len[i];
    // }
    // len[10] = maxx;
    // cout << 10 << endl;
    // for (int i = 1; i <= 10; i++)
    // {
    //     for (int j = 1; j <= len[i]; j++)
    //     {
    //         cout << (char)(rnd.next(0ll, 25ll) + 'a');
    //     }
    //     cout << endl;
    // }
    // for(int i=1;i<=1000;i++)
    // {
    //     // cout<<rnd.next(6ll,maxi)<<" \n";
    //     int ans;
    //     ans=rnd.next(6ll,maxi);
    //     while(ans%2!=0)
    //     {
    //         ans=rnd.next(6ll,maxi);
    //     }
    //     cout<<ans<<endl;
    // }
    // int t = 100000;
    // for(auto i:ans)
    // {
    //     cout<<i;
    //     for(int j=1;j<=i;j++)
    //     {
    //         cout<<' '<<rnd.next(6,100000);
    //     }
    //     cout<<endl;
    // }
    // cout << 100000;
    // for (int j = 1; j <= 100000; j++)
    // {
    //     cout << ' ' << j;
    // }
    // cout << endl;
    // for (int tt = 1; tt <= 10; tt++)
    // {
    //     cout <<"100000";
    //     for (int j = 1; j <= 100000; j++)
    //     {
    //         cout << ' ' << rnd.next(1, 100000);
    //     }
    //     cout << endl;
    // }
}
signed main(signed argc, char *argv[])
{
    registerGen(argc, argv, 1);
    rnd.setSeed(194293);
    for (int i = 10; i <= 11; i++)
    {
        string tp = ".in";
        tp = "test" + to_string(i) + tp;
        freopen(tp.c_str(), "w", stdout);
        int __ = 1;
        // cout << 1000 << endl;
        while (__--)
        {
            solve();
            // cerr<<"TIME"<<qq-__<<endl;
        }
    }
    return 0;
}