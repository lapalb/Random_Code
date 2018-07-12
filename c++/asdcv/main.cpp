#include<bits/stdc++.h>
using namespace std;

int main()
{
int n;
cin>>n;
while(n--)
{
	string s;
	cin>>s;
	int i,j;
	for( i=0;i<(s.size()-1);i++)
	{
	    for( j=i+1;j<s.size();j++)
	    {
	        string s2;
	        s2=s.substr(i,(j-i+1));
	        if(s2 == string(s2.rbegin(), s2.rend())){cout<<"YES\n";goto sos;}
	    }
	}
	cout<<"NO\n";
	sos:{}
}
}

