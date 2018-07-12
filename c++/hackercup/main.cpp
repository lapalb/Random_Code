#include<bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i=a;i<b;i++)
int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int t1;
    cin>>t1;
    for(int  t=0;t<t1;t++ )
    {
        //Dealing with input
        int n,k; long long j;
        cin>>n>>k>>j;
        string s[n];
        rep(i,0,n)cin>>s[i];

        //Processing
        long long t1=k*(j-1);
        int ans=t1%n;
        vector<string> se;
        rep(i,0,k)
        {
            if((ans+i)<=(n-1))
            se.push_back(s[ans+i]);
            else
            se.push_back(s[ans+i-n]);
        }
        vector <string> sef;
        rep(l,0,n)
        {
            rep(m,0,k)
            {if(se[m]==s[l])
                sef.push_back(s[l]);}
        }
    cout<<"Case #"<<t+1<<": ";for(auto x: sef)cout<<x<<" ";
    cout<<endl;
    }
}
