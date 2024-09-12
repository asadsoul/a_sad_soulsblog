## E.Avoid K Partition

简述题意：将一个数列分成若干个连续段，使得每段的和都不等于 $K$，求方案数，注意对 $998244353$ 取模。

设 $f_i$ 为以第 $i$ 个数为结尾分成子段的合法方案数，容易得到方程：

$$\large f_i=[a_i \ne K]+\sum\limits_{j=1}^{i-1}{[sum_i-sum_{j-1}\ne K]\times f_j}$$

这里 $sum_i$ 为数列 $a$ 的前缀和。

对 $sum_i-sum_{j-1}\ne K$ 移项得到 $sum_{j-1}\ne sum_i-K$

那么可以开一个哈希表存 $sum_i$ 的方案数然后记录前缀方案数最后减掉不符合答案的方案即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
const long long MOD = 998244353;
unordered_map<long long ,long long >vis;
long long n,k,sum;
long long g[500005],f[500005];
int main(){
	cin>>n>>k;
	f[0]=1;vis[0]=1;sum=1;
	for(int i=1;i<=n;++i){
		scanf("%lld",&g[i]);
		g[i]=g[i-1]+g[i];
	}
	for(int i=1;i<=n;++i){
		f[i]=(sum-vis[g[i]-k]+MOD+f[i])%MOD;
		vis[g[i]]=(vis[g[i]]+f[i])%MOD;
		sum=(sum+f[i])%MOD;
	}
	cout<<f[n]<<endl;
	return 0;
}
```