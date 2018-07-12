#include<stdio.h>
#define lint long long
#define MAX 2000002
const int m = 1000000007;

int f[MAX], fi[MAX], bin[MAX];
int a, b;
int t;

int power( int x, int y ) {
	int ans = 1;
	for( ; y; y>>=1 )
	{
		if( y&1 )
			ans = 1ll*ans*x %m;
		x = 1ll*x*x %m;
	}
	return ans;
}

int main() {
	f[0] = 1;
	for( int i=1; i<MAX; ++i )
		f[i] = 1ll*i*f[i-1] %m;
	fi[MAX-1] = power(f[MAX-1], m-2);
	for( int i=MAX-1; i>0; --i )
		fi[i-1] = 1ll*i*fi[i] %m;

	scanf("%d", &t);
	while( t-- )
	{
		scanf("%d%d", &a, &b);
		bin[0] = 0;
		for( int i=1; i<=a && i<=b+1; ++i )
			bin[i] = 1ll*f[a+b+1]*(1ll*fi[i-1]*fi[a+b+2-i] %m) %m;
		for( int i=b+2; i<=a; ++i )
			bin[i] = 0;
		int ans = 0;
		for( int i=1; i<=a; ++i )
		{
			bin[i] += bin[i-1];
			if( bin[i] >= m )
				bin[i] -= m;
			ans += bin[i];
			if( ans >= m )
				ans -= m;
		}
		int den = 1ll*fi[a+b]*(1ll*f[a]*f[b] %m) %m;
		ans = 1ll*ans*den %m;
		printf("%d\n", ans);
	}
}
