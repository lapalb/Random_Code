#include<bits/stdc++.h>
using namespace std;
#define eps 1e-12
#define pi 3.14159265358979323846
#define pb push_back
#define mp make_pair
#define st first
#define nd second
#define bgn begin
#define ll long long
#define ld long double
#define ull unsigned long long
#define ii pair<ll,ll>
struct gcdExtnd
{
	ll x,y,g;
	ll gcd(ll a,ll b)
	{
		if(b==0)
		{
			x=1;
			y=0;
			return a;
		}
		g=gcd(b,a%b);
		ll t=y;
		y=x-(a/b)*y;
		x=t;
		return g;
	}
};


ll invrsMod(ll a, ll m)
{
	gcdExtnd o;
	ll g=o.gcd(a,m);
	ll x=(o.x)%m;
	if(x<0)x+=m;
	return x;
}


const int N=1000,M=1e9+7;
ll q,n,t,res,fct[N+10];
void solve()
{
	fct[0]=1;
	for(int i=1;i<=N;i++)
	{
		fct[i]=(fct[i-1]*i)%M;
	}
	cin>>q;
	while(q--)
	{
		cin>>n>>t;
		res=invrsMod(t+1,M);
		for(ll i=1,j=n+t+1,k;i<=t+1;i++,j--)
		{
			res=(res*(j%M))%M;
		}
		res=(res-fct[t]+M)%M;
		cout<<res<<"\n";
	}
}

int main()
{
	std::ios::sync_with_stdio(0);
	cin.tie(0);
#ifdef localProject
	freopen("in.txt","r",stdin);
#endif
	solve();
	return 0;
}
