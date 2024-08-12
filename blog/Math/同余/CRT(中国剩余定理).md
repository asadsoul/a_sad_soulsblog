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

- 计算$m_i=\frac{n}{n_i}$

- 计算$m_i$ 在模 $n_i$ 意义下的逆元 $m_i^{-1}$

- 计算 $c=m_i\cdot m_i^{-1}$

3.则在模 $n$ 意义下唯一解为 $\large x=\sum\limits_{i=1}^{k}a_i\cdot c_i \ \ (\mod n)$
