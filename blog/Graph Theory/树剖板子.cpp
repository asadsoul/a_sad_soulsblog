#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2e6+10;
int siz[MAXN],dep[MAXN],top[MAXN],id[MAXN],rev[MAXN],fa[MAXN],son[MAXN];
long long a[MAXN];
int dfn,n,q,rt;
long long MOD;
vector<int>e[MAXN];
void dfs1(int u,int f){
	siz[u]=1;
	dep[u]=dep[f]+1;
	fa[u]=f;
	for(int v:e[u]){
		if(v==f)continue;
		dfs1(v,u);
		siz[u]+=siz[v];
		if(siz[son[u]]<siz[v])son[u]=v;
	}
}
void dfs2(int u){
	id[u]=++dfn;rev[dfn]=u;
	if(son[fa[u]]==u)top[u]=top[fa[u]];
	else top[u]=u;
	if(!son[u])return ;
	dfs2(son[u]);
	for(int v:e[u]){
		if(v==fa[u]||v==son[u])continue;
		dfs2(v);
	}
}
struct node{
	int l,r;
	long long lz,sum;
}tree[MAXN<<2];
#define ls(x)(x<<1)
#define rs(x)(x<<1|1)
#define wide(p)(tree[p].r-tree[p].l+1)
void pushdown(int p){
	if(!tree[p].lz)return ;
	tree[ls(p)].sum=(tree[ls(p)].sum+tree[p].lz*wide(ls(p))%MOD)%MOD;
	tree[rs(p)].sum=(tree[rs(p)].sum+tree[p].lz*wide(rs(p))%MOD)%MOD;
	tree[ls(p)].lz=(tree[ls(p)].lz+tree[p].lz)%MOD;
	tree[rs(p)].lz=(tree[rs(p)].lz+tree[p].lz)%MOD;
	tree[p].lz=0;
}
void build(int p,int l,int r){
	tree[p].l=l,tree[p].r=r;tree[p].lz=0;
	if(l==r){
		tree[p].sum=a[rev[l]]%MOD;
		return ;
	}	
	int mid=(l+r)>>1;
	build(ls(p),l,mid),build(rs(p),mid+1,r);
	tree[p].sum=(tree[ls(p)].sum+tree[rs(p)].sum)%MOD;
}
void Update(int p,int L,int R,long long sum){
	int l=tree[p].l,r=tree[p].r,mid=(l+r)>>1;
	if(L<=l&&r<=R){
		tree[p].sum=(tree[p].sum+sum*wide(p)%MOD)%MOD;
		tree[p].lz=(tree[p].lz+sum)%MOD;
		return ;
	}
	pushdown(p);
	if(L<=mid)Update(ls(p),L,R,sum);
	if(mid<R)Update(rs(p),L,R,sum);
	tree[p].sum=(tree[ls(p)].sum+tree[rs(p)].sum)%MOD;
}
long long Query(int p,int L,int R){
	int l=tree[p].l,r=tree[p].r,mid=(l+r)>>1;
	long long re=0;
	if(L<=l&&r<=R)return tree[p].sum;
	pushdown(p);
	if(L<=mid)re=Query(ls(p),L,R);
	if(mid<R)re=(re+Query(rs(p),L,R))%MOD;
	return re;
}
void Update_In_Tre(int a,int b,long long v){
	while(top[a]!=top[b]){
		if(dep[top[a]]<dep[top[b]])swap(a,b);
		Update(1,id[top[a]],id[a],v);
		a=fa[top[a]];
	}
	if(dep[a]>dep[b])swap(a,b);
	Update(1,id[a],id[b],v);
}
long long Query_In_Tre(int a,int b){
	long long re=0;
	while(top[a]!=top[b]){
		if(dep[top[a]]<dep[top[b]])swap(a,b);
		re=(re+Query(1,id[top[a]],id[a]))%MOD;
		a=fa[top[a]];
	}
	if(dep[a]>dep[b])swap(a,b);
	return (re+Query(1,id[a],id[b]))%MOD;
}
int main(){
	scanf("%d%d%d%lld",&n,&q,&rt,&MOD);
	for(int i=1;i<=n;++i){
		scanf("%lld",&a[i]);
	}
	for(int i=1;i<n;++i){
		int x,y;scanf("%d%d",&x,&y);
		e[x].push_back(y),e[y].push_back(x);
	}
	dfs1(rt,rt),dfs2(rt);
	build(1,1,n);
	while(q--){
		int opt,x,y;long long z;
		scanf("%d",&opt);
		if(opt==1){
			scanf("%d%d%lld",&x,&y,&z);Update_In_Tre(x,y,z%MOD);
			continue;
		}
		if(opt==2){
			scanf("%d%d",&x,&y);
			printf("%lld\n",Query_In_Tre(x,y));
		}
		if(opt==3){
			scanf("%d%lld",&x,&z);
			Update(1,id[x],id[x]+siz[x]-1,z%MOD);
			continue;
		}
		if(opt==4){
			scanf("%d",&x);
			printf("%lld\n",Query(1,id[x],id[x]+siz[x]-1));
		}
	}
	return 0;
}