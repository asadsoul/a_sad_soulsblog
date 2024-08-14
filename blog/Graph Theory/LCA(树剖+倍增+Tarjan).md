## 关于LCA

在一棵*有根树* $G(E,V)，RT = root$ 中，设 $x,y\in V$ ， 我们称 $x,y$ 到根 $RT$ 的路径上第一个相交的点称作 $x,y$ 在该有根树上的最近公共祖先(LCA,Lowest Common Ancestor)，记作 $LCA(x,y)$ 。

对于 $LCA(x,y)$ ，该点一定是 $x\rightarrow y$ 上的点。 $LCA$ 有这样的性质:
- 设 $dep(x)$为该点的深度，则 $dis(x,y)= dep(x)+dep(y)-2dep(LCA(x,y))$ 原因易证(树上路径唯一)。



- 对于以两个以 $x,y$ 为根的子树 $\large G_u,G_v,G_u\cap G_v = \varnothing,\forall a\in G_u,b\in G_v,LCA(a,b)=LCA(x,y)$

- 若 $LCA(x,y)\ne x,y $ ，则 $G_x\cap G_y = \varnothing$

- $x$ 为 $y$ 的祖先，当且仅当 $LCA(x,y)= x$ 

## LCA的求法

### 普通的暴力

我们设 $fa(x)$ 为 $x$ 的父亲。

那么我们可以将 $x,y$ 一直向上爬直到它们相遇位置。

```cpp
int LCA(int u,int v){
    if(dep[u]<dep[v])swap(u,v);
    while(dep[u]!=dep[v])u=fa[u];
    while(u!=v)u=fa[u],v=fa[v];
    return u;
}
```

该算法与树高息息相关，很多时候都会被卡到 $O(n)$ ，所以我们需要寻找更快的算法。

### 倍增法

顾名思义，就是成倍的查找，将使得查询更快，比如快速幂，ST表等算法都是类似的。而查询LCA也能使用倍增去优化暴力。

具体看代码，思路和上面差不多，预处理会多一个步骤。

```cpp
void dfs1(int u,int f){
    fa[u][0]=f;dep[u]=dep[f]+1;
    for(int j=1;j<=lg[dep[u]];++j)
        fa[u][j]=fa[fa[u][j-1]][j-1];
    for(int v:e[u])if(v!=f)dfs1(v,u);
}

int LCA(int x,int y){
    if(dep[x]<dep[y])swap(x,y);
    while(dep[x]>dep[y])x=fa[x][lg[dep[x]-dep[y]]-1]; 
    if(x==y)return x;
    for(int k=lg[dep[x]]-1;~k;--k)
        if(fa[x][k]!=fa[y][k])x=fa[x][k],y=fa[y][k];
    return fa[x][0];  
}
```

这里 `lg[x]` 是预处理后对应 $\lfloor \log_2(x)\rfloor$ 的值，直接调用 $log2(x)$ 由于精度问题所以就不宜使用。

#### 时间复杂度分析

预处理需要 $O(n\log{n})$  的时间，单次查询需要 $O(\log n)$ 的时间。

### Tarjan算法

没错，祖师爷 $Tarjan$ 也发明了求 LCA 的算法。

该算法是离线算法，即将所有询问存下来统一询问降低复杂度。

步骤如下：

1. 遍历整张图，并标记父亲节点和某个点是否被遍历过。

2. 在遍历儿子后将儿子的集合与父亲集合合并，过程用并查集维护。

3. 遍历完所有儿子后，遍历与该点有关的询问，若另一个点已经访问过，则答案为 `find(另一个点)` 。

4.  $\large x,y\in G_{LCA}(x,y)$

```cpp
void Tarjan(int u){
    for(int v:e[u]){
        if(vis[v])continue;
        Tarjan(v);
        merge(fa[u],fa[v]);//这里的fa不是其父亲而是其所属的集合
    }
    for(auto x:ask[u]){
        if(vis[x.v])ans[x.id]=find(x.v);
    }
}

```

#### 做法的正确性


由其过程可知， `find(y)` 是遍历 $y$ 后回溯到的最高点，且对于其儿子构成的子树， $y$ 所在的那棵已经被处理完毕。那么此时， $x$ 一定等于该点或者其它儿子作为根的子树上。由于树上路径唯一，所以此点一定为两个点的最近公共祖先。

#### 时间复杂度

由于仅需遍历一次树和处理两次询问，我们又设并查集时间复杂度为均摊 $O(1)$ 的情况下，时间复杂度易得为 $O(n+q)$ 。 但是请注意该算法常数比较大，在某些时候可能不如倍增。


### 树链剖分（该部分是进阶内容）

树链剖分是将树划分成不同大小的链，方便处理问题，即运用到化树为边的思想，简化了树。



对于一棵树，用什么样的方法能较优地划分呢？我们知道，树有个指标就是树的大小。我们设 `siz[u]` 是以 $u$ 为根的子树的大小。
那么我们不妨将所有儿子中以该儿子为根的子树大小最大的放在一条链上。

这样做法使得每个点往上跳到根节点所经过的链最多为 $\log n$ 条，具体为啥可以思考一下。

那么我们维护的元素有如下几个：

- `siz[u]` 以 $u$ 作为根的子树大小
- `son[u]` $u$ 的重儿子，即以该儿子作为根的子树大小在所有儿子中是最大的。
- `fa[u]` $u$ 的父亲
- `top[u]` $u$所在链的顶端节点。
- `dep[u]` $u$的深度，即根到该点的距离

预处理需要两次dfs，时间复杂度是 $O(n)$

```cpp
//第一次预处理需要维护siz,son,fa,dep
void dfs1(int u,int f){
    fa[u]=f,dep[u]=dep[f]+1,siz[u]=1;
    for(int v:e[u]){
        if(v==f)continue;
        dfs1(v,u);
        siz[u]+=siz[v];
        if(siz[son[u]]<siz[v])son[u]=v;//这里就是按定义来处理的
    }
}
//第二次处理top
void dfs2(int u){
    if(son[fa[u]]==u)top[u]=top[fa[u]];
    else top[u]=u;//如果该点是父亲的重儿子，则在同一个链上，否则为新链链头
    if(!son[u])return ;
    dfs2(son[u]);//优先遍历重儿子
    for(int v:e[u]){
        if(v==fa[u]||v==son[u])continue;
        dfs2(v);
    }
}
```

预处理完后，接下来就是如何求LCA了。

- 若 $x,y$ 在同一条链上，则LCA为深度较小的节点
- 否则将 $x,y$ 所在链深度较小的那个点往上爬知道满足上一个条件为止

```cpp
int LCA(int x,int y){
    while(top[x]!=top[y]){
        if(dep[top[x]]<dep[top[y]])swap(x,y);//较深的那个往上爬
        x=fa[top[x]];
    }
    if(dep[x]>dep[y])swap(x,y);
    return x;
}
```

由于最多经过 $O(\log n)$ 条链，单次查询时间复杂度是 $O(\log n)$ 。

这个算法在所有算法里面算是常数最小的一个了，而且还能拓展一堆额外功能，所以我一般都用这个。实际上查询LCA是伴随很多其它问题出现的，所以你会发现其它算法使用频率没有这个高（倍增的频率可能和树剖同一个数量级），因此我比较推荐使用这个算法。但是在某些问题上可能倍增码量会小很多，所以视情况选择算法。


讲个乐子：在找题的时候发现要LCA的基本全要树剖维护树上信息，所以emmm，你懂的，快点去学线段树吧！

![](https://cdn.luogu.com.cn/upload/image_hosting/1dre2ci9.png)