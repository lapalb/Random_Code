#include<bits/stdc++.h>
using namespace std;
void stackC()
{
   stack<int> s;
    s.push(1);
    s.push(2);
    s.push(3);
    s.push(4);
    s.pop();
    cout<<"The Value at top "<<s.top();
}
int main()
{
    stackC();

}
