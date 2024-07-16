首先对得到的序列排序， 容易发现影响答案的仅有 $x_0$ ， 于是分类讨论：

1. 当$k> 0$ 时,我们直接排序输出即可 。
2. 否则想到一种构造使得前缀和总是大于0， 如果不行则无解， 这一步能用双指针维护

code：

```cpp
#include<bits/stdc++.h>
using namespace std;
long long x[200050];
long long y[200500];
int n;long long k;


bool Judge(){
    int l=1,r=n;
    long long sum=0;
    while(l<=r){
        if(sum+x[l+1]<=0)sum+=x[r--];
        else sum+=x[l++];
    }
    return sum>=k;
}

void print(){
    printf("Yes\n");
    int l=1,r=n;
    long long sum=0;
    while(l<=r){
        if(sum+x[l]<=0){printf("%lld ",x[r]);sum+=x[r--];}
        else {printf("%lld ",x[l]);sum+=x[l++];}
    }
}
int main(){
    scanf("%d%lld",&n,&k);
    for(int i=1;i<=n;++i){
        scanf("%lld",&x[i]);
    }
    sort(x+1,x+1+n);
    if(k>0){
        printf("Yes\n");
        for(int i=1;i<=n;++i){
            printf("%lld ",x[i]);
        }
        return 0;
    }
    if(Judge()==false)printf("No\n");
    else print();

    return 0;
}
```