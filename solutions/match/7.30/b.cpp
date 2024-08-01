#include<bits/stdc++.h>
using namespace std;
const long long MOD=114514;
long long ksm(long long base,long long pow){
    long long re=1;
    while(pow){
        if(pow&1)re=(re*base)%MOD;
        base=(base*base)%MOD;
        pow>>=1;
    }
    return re;
}
int main(){
    long long n;
    cin>>n;
    cout<<(ksm(2,n)+1)%MOD<<endl;
    return 0;
}