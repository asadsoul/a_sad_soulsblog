#include<bits/stdc++.h>
using namespace std;
bool Check(int x){
    bool vis[10];
    memset(vis,0,sizeof(vis));
    int cnt=0;
    while(x){
        int k=x%10;
        if(!vis[k])++cnt;
        vis[k]=true;
        x/=10;
    }
    return cnt==2;
}
int main(){
    int n;
    cin>>n;
    for(int i=n;i;--i){
        if(Check(i)){
            cout<<i<<endl;
            return 0;
        }
    }
    cout<<-1<<endl;
    return 0;
}