看到这个数据范围，显然的，我们需要用到快速排序先让数组变得有序。然后约束条件我们每次取有序序列中最大的和最小的，得到的新数用二分查找插入重复此过程知道数组内元素仅剩最多一个即可。

这个过程可以直接使用STL大法， 避免写这么多代码。

```cpp
#include<bits/stdc++.h>
using namespace std;
bool Cmp(int a,int b){
    printf("? %d %d\n",a,b);fflush(stdout);
    int x=0;scanf("%d",&x);
    return x;
}
int ask(int a,int b){
    printf("+ %d %d\n",a,b);fflush(stdout);
    int pos;scanf("%d",&pos);
    return pos;
}
deque<int>q;
int n;

int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;++i)q.push_back(i);
    sort(q.begin(),q.end(),Cmp);
    while(q.size()>1){
        int x=q.front(),y=q.back();q.pop_front(),q.pop_back();
        int mid=ask(x,y);
        q.insert(lower_bound(q.begin(),q.end(),mid,Cmp),mid);
    }
    printf("!\n");
    fflush(stdout);
    return 0;
}

```