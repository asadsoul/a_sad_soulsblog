这题容易发现如下递推式

$$\large f_i=f_{i-1}*10^{len}+n$$

其中 $len$ 是 $n$ 的长度。

于是构造矩阵转移递推即可， 具体构造如下：

$$ \large \begin{bmatrix}
  n&n
\end{bmatrix}
\large \begin{bmatrix}
10^{len} & 0
\\ 1&1
\end{bmatrix}^{n-1}
$$

然后正常快速幂求解即可(代码很丑就不放了)