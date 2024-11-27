#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;
const long long maxi=1e18,maxn=1e4;
signed main(int argc, char *argv[])
{
    registerGen(argc, argv, 1);
    string s1,s2;
    int n=inf.readInteger(1,100);
    inf.readEoln();
    int total=1e5;
    for(int i=1;i<=n;i++)
    {
        int m=inf.readInt(1,total);
        inf.readEoln();
        total-=m;
        for(int j=1;j<=m;j++)
        {
            inf.readLong(1ll,(long long)(1e18));
            if(j!=m) inf.readSpace();
            else inf.readEoln();
        }
    }
    inf.readEof();
    return 0;
}