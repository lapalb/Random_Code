/*
Competition Name: CodeChef's Lord Of the Code
Name of The Problem: Elections in Chefland
Original Constraints:
1≤ T ≤1000
0≤ A,B≤ 10^6
1≤ A+B
Sum of A×B over all test cases does not exceed 10^7

*/
#include<bits/stdc++.h>
using namespace std;

long long cnt=0;
int fact(int n)
{
    if(n==1)  return 1;
    else return n* fact(n-1);
}
void lead(vector<int> s,int l)
{
    int acnt=0,bcnt=0;
    for(int i=0;i<l;i++)
    {
        if(s[i]==0){bcnt++ ;}
        else
           {
             acnt++;
           }

        if(acnt>bcnt)
            cnt++;
    }
}
int main()
{

	int t;
	cin>>t;
	while(t--)
	{
		int  a,b;
		cin>>a>>b;
        int l=a+b;
		cnt=0;
		vector<int> v;
		for(int i=0;i<b;i++)
            v.push_back(0);
        for(int i=0;i<a;i++)
            v.push_back(1);
        lead(v, l);
        while(std::next_permutation(v.begin(),v.end()))
        {
            lead(v, l);
        }
        cout<<(cnt*fact(a)*fact(b))/fact(l);


	}
}
