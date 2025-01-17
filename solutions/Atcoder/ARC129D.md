我们发现，该操作对于数组总和是不变的，那么若 $\sum a_i\ne0$ 则无解。

我们设 $x_i$ 为选用该点操作的次数，那么显然若都为0，显然有 $a_i+2*x_i-x_{i-1}+x_{i+1}=0$

化简得 $a_i=(x_{i+1}-x_i)-(x_i-x_{i-1})$

发现有差分形式则令 $d_i=x_i-x_{i-1}$

于是又得 $a_i=d_{i+1}-d_{i}$

发现有 $d_i-d_1=\sum\limits_{j=2}^{i-1}(d_j-d_{j-1})=\sum\limits_{j=1}^{i-1}a_j$

那么有 $\sum\limits_{i=1}^{n}{d_i}=nd_1+\sum\limits_{i=1}^{n}(n-i)a_i$

考虑到有 $\sum\limits_{i=1}^{n}d_i=\sum\limits_{i=1}^{n}{x_i-x_{i-1}}$

又由于为环所以 $x_0=x_n$

于是该式子为0，那么就有

$$\large d_1=-\frac{\sum\limits_{i=1}^{n}(n-i)a_i}{n}$$

并且 $d_1$ 为整数，否则无解。

考虑递推 $d_{i+1}=d_{i}+a_{i}$

然后由于 $x_i\ge 0$ 又有  $x_i=x_1+\sum\limits_{j=2}^{i-1}d_j\ge 0$

求出最小的 $x_1$ 再求出来即可