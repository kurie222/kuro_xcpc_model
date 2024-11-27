#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include "testlib.h"
#define rt return
#define pi pair<int, int>
#define pl pair<ll, ll>
#define pu pair<ull, ull>
#define ll long long
#define ull unsigned long long
#define endl '\n'
#define Endl endl
#define all(x) x.begin(), x.end()
#define lll __int128_t
#define ulll __uint128_t
using namespace std;
const int maxn = 1e5 + 50;
const int mod = 998244353;
const ll maxl = 2e18 + 5;
const int maxi = 1e9 + 7;
signed main(int argc, char *argv[])
{
    registerGen(argc, argv, 1);
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    ifstream in, ans, out;
    ans.open("2.txt");
    out.open("3.txt");
    in.open("1.txt");
    int ok = 1;
    int i = 1;
    int ___;
    in >> ___;
    for (int __ = 1; __ <= ___; __++)
    {
        int n, m;
        in >> n >> m;
        set<pi> st;
        for (int i = 0; i < m; i++)
        {
            int q, w;
            in >> q >> w;
            if (w < q)
                swap(q, w);
            st.insert({q, w});
        }
        int tag = -2;
        ans >> tag;
        int rtag = -2;
        out >> rtag;
        if ((tag == -1 && rtag != -1) || (tag != -1 && rtag == -1))
        {
            if (rtag == -1)
                cout << "WA in test case" << __ << " jury is -1" << endl;
            else
                cout << "WA in test case" << __ << " jury has answer" << endl;
            cout << n << ' ' << m << endl;
            for (auto [x, y] : st)
            {
                cout << x << ' ' << y << endl;
            }
            rt 0;
        }
        int ww;vector<int> an;
        for (int i = 0; i < n - 1; i++)
        {
            out >> ww;
            ans >> ww;
            
            an.push_back(ww);
            if (st.find({min(tag, ww), max(tag, ww)}) != st.end())
            {
                cout << "WA in test case" << __ << " constuct error" << endl;
                cout<<tag<<' '<<ww<<endl;
                cout << n << ' ' << m << endl;
                for (auto [x, y] : st)
                {
                    cout << x << ' ' << y << endl;
                }
                for(int i=0;i<an.size();i++)
                cout<<an[i]<<endl;
                rt 0;
            }
            tag = ww;
        }
    }
    if (ok)
    {
        cout << "Accepted!";
    }
    return 0;
}