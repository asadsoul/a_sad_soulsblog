## 状压DP

看到这么长感觉无从下手但是注意到字符数仅有 20，那么可以考虑状压。

那么设状态 $S$ 表示子序列中含有哪几种元素的合法方案。我们发现，对于终止序列发现肯定右端点越靠做越好因为可以做更多的决策可能，这启发我们设 $f_S$ 为使得序列中含有 $S$ 这个状态的最小的最有端点。每次考虑加进一个元素时就找最靠左的能取的点即可。答案在做状压时取 $\max$ 即可。


```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2e5+10;
int nxt[25][MAXN];
int n;
int c[25];
typedef long long ll;
ll f[(1<<20)+10];
int a[MAXN],ans;
int lowbit(int i){return i&(-i);}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;++i)scanf("%d",&a[i]),--a[i];
	memset(f,127,sizeof(f));f[0]=0;
	for(int i=1;i<=n;++i)nxt[a[i]][++c[a[i]]]=i;
	for(int S=0;S<(1<<20);++S){
		if(f[S]>1e9)continue;
		int Q=S;int sum=0;while(Q)++sum,Q-=lowbit(Q);
		ans=max(ans,2*sum);
		for(int i=0;i<20;++i){
			if(S&(1<<i))continue;
			int p=lower_bound(nxt[i]+1,nxt[i]+1+c[i],f[S])-nxt[i];
			if(p+1<=c[i])f[S|(1<<i)]=min(f[S|(1<<i)],nxt[i][p+1]*1ll);
		}		
	}
	cout<<ans<<endl;
	return 0;
}
```