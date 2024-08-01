#include<bits/stdc++.h>
using namespace std;
const int MAXN = 100050;
struct node{
    int to;
    int next;
}e[MAXN<<1];
int tot,head[MAXN];
int n,q,W[MAXN];
void add(int u,int v){
    e[++tot].to=v;
    e[tot].next=head[u];
    head[u]=tot;
}
int cnt,id[MAXN],rev[MAXN],siz[MAXN],top[MAXN],son[MAXN],fa[MAXN],dep[MAXN];
void dfs1(int u,int f){
    siz[u]=1;
    dep[u]=dep[f]+1;
    fa[u]=f;
    for(int i=head[u],v;i;i=e[i].next){
        v=e[i].to;
        if(v==f)continue;
        dfs1(v,u);
        siz[u]+=siz[v];
        if(siz[son[u]]<siz[v])son[u]=v;
    }
}
void dfs2(int u){
    id[u]=++cnt;rev[cnt]=u;
    if(son[fa[u]]==u)top[u]=top[fa[u]];
    else top[u]=u;
    if(!son[u])return ;
    dfs2(son[u]);
    for(int i=head[u];i;i=e[i].next){
        int v=e[i].to;
        if(v==fa[u]||v==son[u])continue;
        dfs2(v);
    }
}
struct Tree_node{
    int ls,rs;
    int cnt;
}tree[MAXN<<10];
int T;
#define ls(x)(tree[x].ls)
#define rs(x)(tree[x].rs)
const int R=3e6+10;
int build(int l,int r){
    int p=++T;
    tree[p].cnt=0;
    if(l==r)return p;
    int mid=(l+r)>>1;
    ls(p)=build(l,mid),rs(p)=build(mid+1,r);
    return p;
}
int update(int p,int l,int r,int pos){
    int Np=++T;
    tree[Np]=tree[p];
    tree[Np].cnt++;
    if(l==r)return Np;
    int mid=(l+r)>>1;
    if(pos<=mid)ls(Np)=update(ls(Np),l,mid,pos);
    else rs(Np)=update(rs(Np),mid+1,r,pos);
    return Np;
}
int query(int p,int op,int l,int r,int pos){
    if(l==r)return tree[p].cnt-tree[op].cnt;
    int mid=(l+r)>>1;
    if(pos<=mid)return query(ls(p),ls(op),l,mid,pos);
    else return query(rs(p),rs(op),mid+1,r,pos);
}
int rt[MAXN+10];
int ask(int x,int y,int w){
    int re=0;
    while(top[x]!=top[y]){
        if(dep[top[x]]<dep[top[y]])swap(x,y);
        re+=query(rt[id[x]],rt[id[top[x]]-1],1,R,w);
        x=fa[top[x]];
    }
    if(dep[x]>dep[y])swap(x,y);
    re+=query(rt[id[y]],rt[id[x]-1],1,R,w);
    return re;
}
void Init(){
    dfs1(1,1);
    dfs2(1);
    rt[0]=build(1,R);
    for(int i=1;i<=n;++i){
        rt[i]=update(rt[i-1],1,R,W[rev[i]]);
    }
}
int main(){
    scanf("%d%d",&n,&q);
    for(int i=1;i<n;++i){
        int u,v;scanf("%d%d",&u,&v);
        add(u,v),add(v,u);
    }
    for(int i=1;i<=n;++i)scanf("%d",&W[i]);
    Init();
    while(q--){
        int u,v,w;scanf("%d%d%d",&u,&v,&w);
        printf("%d\n",ask(u,v,w));
    }
    return 0;
}