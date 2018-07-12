#include <iostream>

using namespace std;
int expo(int a,int n)
{
    long long b=1;
    if(n==1) return a;
    if(n%2==0)
    return expo(a,n/2)* expo(a,n/2);
    else
       return expo(a,n/2)*expo(a,n/2)*a;

}
int main()
{
    int t;
    cin>>t;
    int a,n,b=1;
    while(t--)
    {
     cin>>a>>n;
    cout<<expo(a,n);
    }

}
