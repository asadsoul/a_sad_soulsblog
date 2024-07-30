#include<bits/stdc++.h>
using namespace std;

priority_queue<int,vector<int>,greater<int> >q;
int n,l;
int main(){
    scanf("%d%d",&n,&l);
    for(int i=1;i<=n;++i){
        int x;scanf("%d",&x);
        if(q.size()<l)q.push(x);
        else{
            if(q.top()<x)q.pop(),q.push(x);
           
        } 
        if(q.size()==l)printf("%d\n",q.top());
    }

    return 0;
}