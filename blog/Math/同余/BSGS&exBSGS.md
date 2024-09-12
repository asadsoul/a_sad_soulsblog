## BSGS

对于形如这样的方程：

$$a^x\equiv n(\mod m)$$

如何计算？

由欧拉定理可知，对于一个数的循环节长度一定有 $\varphi(m)$ 这么长。

那么我们可以尝试枚举从0到 $\varphi(m)$ 的数字一个一个判断答案。
但是这样复杂度太高了，我们尝试将这个暴力优化一下。而 BSGS(Baby-Step Gaint-Step) 可以在 $\sqrt m $ 的时间复杂度下计算(应该是当下的一个计算方式很快的算法了)。

##### Attention:此方法应用于 $\gcd(x,m)=1$ 的方程中

若令 $k=\sqrt p,x=ik-q$

式子变换为 :

$$\large a^{ik-q}\equiv n(\mod m)$$

即

$$\large a^{ik}\equiv na^{q}(\mod m)$$

容易发现 $i,q$ 仅需枚举到 $k$ 即可。可以发现开一个哈希表储存对于每个值的答案然后查询即可：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll p;
ll ksm(ll a,ll b){
	ll re=1;
	while(b){
		if(b&1)re=re*a%p;
		a=a*a%p;
		b>>=1;
	}
	return re;
}

unordered_map<ll,ll>vis;

ll b,n;
int main(){
	cin>>p>>b>>n;b%=p;n%=p;
	ll t=ceil(sqrt(p));
	for(ll i=0;i<=t;++i)
		vis[n*ksm(b,i)%p]=i;
	for(ll i=0;i<=t;++i){
		ll now=ksm(b,i*t);
		if(vis[now]){
			cout<<(i*t-vis[now]+p-1)%(p-1);
			return 0;
		}
	}
	puts("no solution");
	return 0;
}
```

## exBSGS

对于非互质情况，可以先将式子转化成等价的方程：

$$a^x+mq=n$$

该方程有解的充要条件是 $\gcd(a,p)|n$ 

那么则可以联系exGCD去求解即先全部除以 $\gcd(a,p)$

即

$$\large a^{x-1}\frac{a}{d}+\frac{m}{d}q=\frac{n}{d},d=\gcd(a,p)$$

统计一共进行了多少次，容易得到答案式子

$$\large a^{x-cnt}\frac{a^{cnt}}{d}\equiv \frac{n}{d}(\mod \frac{m}{d})$$


```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll ksm(ll a,ll b,ll p){
	ll re=1;
	while(b){
		if(b&1)re=re*a%p;
		a=a*a%p;
		b>>=1;
	}
	return re;
}
ll gcd(ll a,ll b){
	if(b==0)return a;
	return gcd(b,a%b);
}
ll BSGS(ll a,ll n,ll p,ll mult){
	unordered_map<ll,ll>vis;
	ll r=ceil(sqrt(p)),now=1;
	for(int i=0;i<=r;++i){
		vis[now*n%p]=i;now=now*a%p;
	}
	for(int i=0;i<=r;++i){
		now=ksm(a,i*r,p)*mult%p;
		if(vis[now]&&i*r-vis[now]>=0)return i*r-vis[now];
	}
	return -1;
}
ll exBSGS(ll a,ll n,ll p){
	a%=p,n%=p;
	if(n==1||p==1)return 0;
	ll d,cnt=0,mult=1;
	while((d=gcd(a,p))!=1){
		if(n%d)return -1;
		++cnt,n/=d,p/=d;
		mult=(mult*a/d)%p;
		if(mult==n)return cnt;
	}
	ll ans=BSGS(a,n,p,mult);
	if(ans==-1)return -1;
	return ans+cnt;
}
ll read(){
	ll x=0;char ch=getchar();
	while(ch<'0'||ch>'9')ch=getchar();
	while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
	return x;
}
int main(){
	int X=1;
	while(X){
		ll a=read(),p=read(),n=read();
		if(a==0&&n==0&&p==0)break;
		ll ans=exBSGS(a,n,p);
		if(ans==-1)puts("No Solution");
		else printf("%lld\n",ans);
	}
	return 0;
}
```
