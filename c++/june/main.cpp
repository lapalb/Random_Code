//Hedaer Files of mine
#include <bits/stdc++.h>
using namespace std;

#define rep(i,a,b) for(int i=a;i<b;i++)
#define repr(i,a,b) for(int i=a;i>b;i--)

int main()
{

	int t;
	cin>>t;
	while(t--)
	{
		int n,a1,b1;
		cin>>n>>a1>>b1;
		int a[n];
		rep(i,0,n)cin>>a[i];
int cnta=0,cntb=0;
		rep(i,0,n)
		{
			if(a[i]==a1)cnta++;
            if(a[i]==b1)cntb++;

		}
        long double ans=0.0;
		ans+=cnta/(double)n;
		ans*=(cntb/double(n));
		cout<<ans<<endl;

	}}
