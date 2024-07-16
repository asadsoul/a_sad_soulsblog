### A.Buy a Pen

有选择的取最小，当选定一个位置时求另外两个的最小值，分类讨论即可。
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
    int r,g,b;
    cin>>r>>g>>b;
    int ans=r+g+b;
    string s;
    cin>>s;
    if(s[0]=='R')cout<<min(g,b);
    if(s[0]=='G')cout<<min(r,b);
    if(s[0]=='B')cout<<min(r,g);
    return 0;
}

```

### B.Right Triangle

#### 题目大意

给定三角形的三个顶点，判断它们是否是直角三角形。

#### 题解

上过小学的朋友都知道勾股定理：

对于三角形的三条边 $A,B,C$ ，$A,B$ 是较小边，其是三角形的充要条件是$A^2+B^2=C^2$ 。

于是分别枚举 $C$ 即可。


### C.Sum=0

#### 题目大意:

给定 $n$ 段区间，在每段区间内取一个数，问存不存在一个数列，使得它们的加和等于0。如果可以，输出 `Yes` 并输出这个数列；否则输出 `No` 。

由于区间连续，所以最后答案值域一定是在 $\large\sum\limits_{i=1}^{n}{l_i}$ 和 $\large\sum\limits_{i=1}^{n}{r_i}$ 之间。 

可以发现，如果区间不包含0，那么答案不存在。

否则，我们可以先钦定序列全为区间左端点，再每个点尝试往右端点修改使得加和为0即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
struct node{
    long long l,r;
    bool operator<(const node X)const{
        return l<X.l;
    }
}a[5050550];
long long b[5050505];
int n;
long long suml,sumr;
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;++i){
        scanf("%lld%lld",&a[i].l,&a[i].r);
        suml+=a[i].l,sumr+=a[i].r;
    }
    if(0<suml||sumr<0)printf("No\n");
    else{
        printf("Yes\n");
        for(int i=1;i<=n;++i)b[i]=a[i].l;
        for(int i=1;i<=n&&suml!=0;++i){
            if(suml-a[i].l+a[i].r<=0){
                suml=suml-a[i].l+a[i].r;
                b[i]=a[i].r;
                continue;
            }
            else{
                b[i]=a[i].l-suml;
                break;
            }
        }       
        for(int i=1;i<=n;++i)printf("%lld ",b[i]);
    }
    return 0;
}
```


### D.Shortest Path 3

#### 题目大意

有一张 $n$ 个点和 $m$ 条边的无向图，每个点有一个点权 $a_i$ ， 每条边有个边权 $b_i$ 。

我们令一个点到另一个点的距离是某条通路上点权和边权之和的最小值。

现在对于每个点 $i=2,3,..,n$ , 求出其与 1 的最小值 。

#### 题解

很容易想到将一个点拆成两个， 在这两个点之间连上一条边权为 $a_i$ 的边跑最短路即可。连边有点细节具体详见代码。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define MAXN 2000050
long long dis[MAXN<<1];
struct node{
    int to;
    int nxt;
    long long dis;
}e[MAXN<<2];
int tot,head[MAXN<<1];
bool vis[MAXN<<1];
int s=1,n,m;
typedef pair<long long ,int >arr;
void add(int u,int v,long long d){
    e[++tot].to=v;  
    e[tot].dis=d;
    e[tot].nxt=head[u];head[u]=tot;
}
void Dijst(){
    priority_queue<arr,vector<arr>,greater<arr> >q;
    q.push(arr(0,1));
    memset(dis,63,sizeof(dis));
    dis[1]=0;
    while(!q.empty()){
        int u=q.top().second;
        q.pop();
        if(vis[u])continue;
        vis[u]=true;
        for(int i=head[u];i;i=e[i].nxt){
            int v=e[i].to;long long d=e[i].dis;
            if(d+dis[u]<dis[v]){
                dis[v]=d+dis[u];
                if(!vis[v])q.push(arr(dis[v],v));
            }
        }
    }
}
int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;++i){
        long long a;scanf("%lld",&a);
        add(i,i+n,a);
    }
    for(int i=1;i<=m;++i){
        int u,v;long long d;
        scanf("%d%d%lld",&u,&v,&d);
        add(u+n,v,d),add(v+n,u,d);//注意这里建边方式
    }
    Dijst();
    for(int i=n+2;i<=n*2;++i)printf("%lld ",dis[i]);
    return 0;
}
```

### Count Arithmetic Subsequences

#### 题目大意

给定一个长度为 $n$ 的数列， 求这个数列所能构成等差数列的子数列的个数。对`998244353`取模。

#### 题解

观察到 $n$ 很小，我们可以构造一个比较暴力的DP。

等差数列的一个关键要点是[公差](https://baike.baidu.com/item/%E5%85%AC%E5%B7%AE/844900)。对于每两个数可以确定其公差。于是枚举两个数，最多有 $n^2$ 个不同的公差，离散化后就可以构造DP了。

设 $f[i][j][k]$ 是以第 $i$ 个元素为结尾 长度为 $j$ 公差为 $k$ 的方案数。这里$k$枚举前面一个元素然后取其离散化后的值即可即可。于是对于一个元素 $a_j,j<i$ 有转移 $f[i][j][k]+=f[i][j-1][k]$ 

在每个 $i$ 结束后将答案统计进最终答案中即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
long long ans[100];
long long f[100][81*81][100];
unordered_map<long long ,int>p;
int cnt;
int n;
long long a[100];
long long const MOD=998244353;
int main(){
    cin>>n;
    for(int i=1;i<=n;++i){
        cin>>a[i];
    }
    for(int i=1;i<=n;++i)
        for(int j=i+1;j<=n;++j)
            if(p[a[j]-a[i]]==0)p[a[j]-a[i]]=++cnt;
    ans[1]=n;
    for(int i=1;i<=n;++i)
        for(int j=1;j<i;++j)
            {f[i][p[a[i]-a[j]]][2]++;}

    for(int i=1;i<=n;++i){
        for(int j=1;j<i;++j){
            int P=p[a[i]-a[j]];
            for(int k=3;k<=n;++k)f[i][P][k]=(f[i][P][k]+f[j][P][k-1])%MOD;
        }
        for(int j=0;j<=cnt;++j)
            for(int k=2;k<=n;++k)
                ans[k]=(ans[k]+f[i][j][k])%MOD;
    }
    for(int i=1;i<=n;++i)printf("%lld ",ans[i]);
    return 0;
}
```