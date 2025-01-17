## 取模的等价运算

$$x \mod y \ =  x - \lfloor \frac{x}{y} \rfloor y$$


## 子集的遍历

设 $S$ 为一个集合，若想遍历其子集，则有

```cpp
for(int i=(S-1)&S;i;i=(i-1)&S);
```

## 特殊求和
$$\large\sum\limits_{i=1}^{n}{i[gcd(i,n)=1]}=\frac{\varphi{(n)}n}{2}$$

这里 $\varphi(n)$ 为欧拉函数

$$\large\sum\limits_{i=1}^{n}{\sum\limits_{i=1}^{n}{[gcd(i,j)==1]}}$$
$$\large=\sum\limits_{i=1}^{n}{\varphi(i)}-1$$

这里1是总体减1