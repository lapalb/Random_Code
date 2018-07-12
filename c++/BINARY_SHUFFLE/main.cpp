#include<bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i=a;i<b;i++)
int numB(long long a)
{
    return int((log2(a)+1));
}
int main()
{
    int t;
    cin>>t;
    while(t--)
    {
        long long a,b;
        cin>>a>>b;
        if(a==b)cout<<0<<endl;
        else{
            int as=__builtin_popcount(a);
            int bs=__builtin_popcount(b);
            if(as>bs)cout<<-1<<endl;
            else if(as==bs && a!=b)cout<<-1<<endl;
            else
            {
                cout<<as-bs;
            }
        }
    }
}
