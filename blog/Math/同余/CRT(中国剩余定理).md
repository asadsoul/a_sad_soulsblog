### 引入

该定理最早见于 《孙子算经》中，这里用该书中的问题来引入：有物不知其数，三三数之剩二，五五数之剩三，七七数之剩二，问物几何？

### 定义

中国剩余定理 （Chinese Remainder Theorem ，CRT） 可求解如下一元线性同余方程组（其中 $n_1,n_2,\dots,n_k$ 两两互质）

$$
\large\left\{ \begin{matrix}
x &\equiv a_1 (\mod n_1)
\\ 
x &\equiv a_2 (\mod n_2)
\\
\dots
\\
x &\equiv a_k (\mod n_k) 
\end{matrix}\right.
$$

### 过程

公式为：

$$
\Large x= \sum\limits_{i=1}^{k}{a_i\cdot \frac{\prod\limits_{j=1,j\ne i}^{k}{n_i}}{(\prod\limits_{j=1,j\ne i}^{k}{n_i})_{(\mod n_i)}}}
$$

ps：这里$(\mod n_i)$ 指在模 $n_i$ 意义下的逆元。

具体的就是：

1.计算所有模数积 $n$

2.对于第 $i$ 个方程：

- 计算 $m_i=\frac{n}{n_i}$

- 计算 $m_i$ 在模 $n_i$ 意义下的逆元 $m_i^{-1}$

- 计算 $c=m_i\cdot m_i^{-1}$

3.则在模 $n$ 意义下唯一解为 $\large x=\sum\limits_{i=1}^{k}a_i\cdot c_i \ \ (\mod n)$



## EXCRT（拓展中国剩余定理）

当模数不互质时，普通的剩余定理已经不适用了。这时候就要清楚毫不相关的拓展中国剩余定理了。

我们设两个方程是$x\equiv a_1 (\mod m_1)$ 和 $x\equiv a_2(\mod m_2)$

将其转化为不定方程 :
$x=m_1\cdot p + a_1=m_2\cdot q + a_2$，其中 $p,q\in \Z$，则有$m_1\cdot p - m_2\cdot q = a_2-a_1$

由裴蜀定理可得，当 $\gcd(m_1,m_2) \nmid a_2-a_1$ 时无解。

其它情况下通过扩展欧几里得算法求出可行解$p,q$

则原来的方程解可以合并为 ：
$$x \equiv b (\mod M)$$

这里 $b=m_1\cdot p + a_1,M=lcm(m_1,m_2)$