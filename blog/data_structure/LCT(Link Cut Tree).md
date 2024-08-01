## Link Cut Tree 

### Problem

维护一棵树，支持如下操作：


* 修改两个点路径之间的权值

* 查询两点之间路径权值和

* 修改某点子树权值和

* 查询某点子树权值和

* 支持断边和连边操作

### 动态树问题

像上面的不是维护一个树而是一整个森林并且图的结构会有变动我们称之为动态树问题。

一般操作会有两点联通性，两点路径权值和，连接两点和切断某条边、修改信息等。

### 实链剖分

对于一个点连向它所有儿子的边，我们自己选择一条边进行剖分，我们称自己选择的边为实边，其它的则被称为虚边。对于实边，我们称它所链接的儿子为实儿子。对于一条由实边组成的链，我们同样称之为实链。

而 LCT 我们就可以简单的理解为用 Splay Tree 来维护动态的树链剖分，实现动态树上的区间操作。对于每一条实链，我们都可以开一个Spaly树来维护。而加边和删边就变成合并和分裂Spaly树的一个过程。


###  辅助树

辅助树由多个Splay树构成一个辅助树，每棵辅助树维护的是一棵树，一些辅助树构成一个LCT，其维护的是整个森林。

1.辅助树由多个Splay树所组成每棵Splay树维护原树中的一条路径，并且中序遍历会得到的序列对应前到猴，上到下的一条原树路径（即不破坏树的拓扑结构）。

2.辅助树各个Splay树之间并不是独立的。每棵Splay的根节点的父亲本应是空的，但在LCT中每棵Splay的根节点的父节点指向这条链的父节点。与一般的区别是子认父，父不认子，对应的是一条虚边。

3.由于拓扑性质相同，那么我们可以直接维护LCT而不是原树去解决答案。


### LCT的一些变量

* `ch[u][2]` 左右儿子

* `f[u]` 父亲

* `rev_tag[u]` 反转标记

* `siz[u]` 辅助树子树大小

* 维护树上信息的变量如边权，子树大小等（维护点权要化点为边维护）

## LCT的函数构成

* 维护信息的函数如 `pushup`、`pushdown` 等

* `Get_fa(u)` 获取是左儿子还是右儿子

* `Splay(u)` 讲改点作为其所在的Splay的根

* `Rotate(u)` 将点向上旋转一层

* `Access(u)` 打通x到根的链链，即将x到根的所有点放在一条实链上，并且在同一棵Splay树上

* `Is_Root(u)` 判断x是否是所在Splay树的根

* `Update(u)` 必须放在 `Access` 操作的后面，从上到下更新信息

* `MakeRoot(u)` 使此点称为其所在树的根

* `Link(x,y)`  在 $u$ 和 $v$ 之间连一条边

* `Cut(x,y)`  删除 $x$ 到 $y$ 之间的边

* `Find_Root(x)` 找到 $x$ 所在Splay树的根节点编号

* `Split(x,y)` 提取 $x,y$ 之间的路径，做区间操作的时候使用

这里定义 

`#define ls(x)(ch[x][0])` 和 `#define rs(x)(ch[x][1])`

### 函数的实现

```cpp
//Splay 和 Rotate 操作的实现，与Splay树稍微有些不同

void Rotate(int x){
    int y=f[x],z=f[y],k=Get_fa(x);
    if(!Is_Root(y))ch[z][ch[z][1]==y]=x;//必须这样先判断，否则会出错
    ch[y][k]=ch[x][!k];
    f[ch[x][!k]]=y;
    ch[x][!k]=y,f[y]=x,f[x]=z;
    //maintain operation
}

void Splay(int x){
    Update(x);//看下面一段
    while(Is_Root(x)){
        int y=f[x],z=f[y];
        if(Is_root(y))Rotate(((ls(y)==x)^(ls(z)==y))?x:y);//看看三个点是不是在同一个链上，是就转y否则转x
        Rotate(x);
    }
    //maintain操作
}

//Is_root(x)
//如果一个点既不是父亲左儿子，也不是父亲的右儿子，那么就是其Splay的根，因为LCT具有父亲不认虚儿子的性质（不是亲生的，确信）

bool Is_Root(int u){
    return (u!=ls(fa[u]))&&(u!=rs(fa[u]));
}


/*
LCT核心操作。做完之后某条路径恰好是这个Splay树
*/
void access(int x){
    for(int y=0;x;x=f[y=x]){
        Splay(x);rs(x)=y;//maintain operation
    }
}
//Update()

void Update(int x){
    if(!Is_Root(x))Update(f[x]);
    //maintain operation
}

void MakeRoot(int x){
    access(x);splay(x);pushrev(x);//pushrev是打翻转标记
}

void pushrev(int x){
    swap(ls(x),rs(x));lazy[x]^=1;
}
//Split()
//拿出一棵Splay，维护是x到y的路径
void Split(int x,int y){
    MakeRoot(x);Access(y);Splay(y);
}
//补充，操作完猴可以直接把需要路径拿出到y的子树上，进行其它操作

//Cut()

void Cut(int x,int y){
    MakeRoot(x);Access(p);Splay(y);ls(x)=f[x]=0;//不合法必须先判断再操作
}

// Link()
//比较简单，MakeRoot后把x父亲指向y

void Link(int x,int y){
    MakeRoot(x);Splay(x);f[x]=y;
}

void  FindRoot(int x){
    Access(x);Splay(x);
    //PushDown lazy Tag
    while(ls(x))x=ls(x)/*Pushdown*/;
    Splay(x);
    return x;
}

```

