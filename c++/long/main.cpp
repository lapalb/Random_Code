#include <bits/stdc++.h>

using namespace std;
void sub(int arr[], int n,int m)
{
    int cnt=0;
   /*  int o = pow(2, n);
     for (int counter = 1; counter < o; counter++)
    {
        vector<int>v;
        for (int j = 0; j < n; j++)
        {
            if (counter & (1<<j))
                v.push_back(arr[j]);
        }
        int ac=0;
        for(auto x: v)ac+=x;
        if((ac%m==0) && (v.size()!=n))cnt++;
    }*/
    for(int i=0;i<(n);i++)
    {

        for(int j=i;j<n;j++)

        {
             int s=0;
            for(int k=i;k<=j;k++)s+=arr[k];
            if(s==m)cnt++;

        }
    }
    cout<<cnt<<endl;
}
int main()
{
    int t;
    cin>>t;
    while(t--){
   int n,m;
   cin>>n>>m;
   int a[n];
   for(int i=0;i<n;i++)cin>>a[i];
   sub(a,n,m);}
}
