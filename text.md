设 $f_i$ 为取完前 $i$ 个点的最优方案， $S_i$ 为 $\sum\limits_{k=1}^{i}(C_k+1)$

于是 $x=S_i-S_j-1$

那么有转移 $f_i=\min\{f_j+(S_i-S_j-1-L)^2\}$

令 $L=L+1$

则有 $f_i=\min\{f_j+(S_i-S_j-L)^2\}$

将 min 除去之后，整理得到 

$$f_i-(S_i-2S_iL)+2S_iS_j=f_j+(S_j+L)^2$$

于是得到一个决策点的坐标为

$$(S_j,f_j+(S_j+L)^2)$$