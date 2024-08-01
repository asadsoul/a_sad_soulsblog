#include<bits/stdc++.h>
using namespace std;
const long long MOD=998244353;
long long f[22][2005];//item time usd
int b[30],a[30];
long long C[5005][5005];
void Solve(){
    C[0][0]=1;
    for(int i=1;i<=4000;++i){
        C[i][0]=1;
        for(int j=1;j<=4000;++j)
            C[i][j]=(C[i-1][j]+C[i-1][j-1])%MOD;
    }
}
long long ans=0;
int main(){
    Solve();
    f[0][0]=1;
    int sum=0;
    for(int i=1;i<=20;++i){
        scanf("%lld%lld",&a[i],&b[i]);
        sum+=b[i];
    }
    long long ans=0;
    for(int i=1;i<=20;++i){
        for(int t=1;t<=sum;++t){
            for(int k=1;k<=min(t,b[i]);++k){
                for(int l=0;l<i;++l){
                    f[i][t]=(f[i][t]+f[l][t-k]*C[t][k]%MOD)%MOD;
                }
            }
            ans=(ans+f[i][t])%MOD;
        }
    }
    printf("%lld\n",ans);
    return 0;
}
/*
1 2
2 2
3 0
4 0
5 0
6 0
7 0
8 0
9 0
10 0
11 0
12 0
13 0
14 0
15 0
16 0
17 0
18 0
19 0
20 0

*/