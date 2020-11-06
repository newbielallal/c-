**###题目**

**给定一个整数\*n\*，求以 1 ... \*n\* 为节点组成的二叉搜索树有多少种？**

- **输入:** 3
- **输出:** 5

**###思路**

这个是 95不同的二叉搜索树Ⅱ难度减低版。

只用计算一共有多少种二叉搜索树，利用数学定理，节点 ![[公式]](https://www.zhihu.com/equation?tex=1%5Csim+n) 能够组成的二叉搜索树的个数为[卡塔兰数](https://link.zhihu.com/?target=https%3A//baike.baidu.com/item/catalan/7605685%3Ffr%3Daladdin) ,其公式为![[公式]](https://www.zhihu.com/equation?tex=C_%7Bn%2B1%7D%3D%5Cfrac%7B2%282n%2B1%29%7D%7Bn%2B2%7DC_%7Bn%7D++++) ,其中 ![[公式]](https://www.zhihu.com/equation?tex=C_%7B0%7D) 设为1，利用上述公式，通过循环就可以计算出 ![[公式]](https://www.zhihu.com/equation?tex=C_%7Bn%7D) 的值，最后输出该结果即可。

**###code**

```cpp
class Solution {
public:
    int numTrees(int n) {
        long long res=1;//循环中先进行乘法，为避免溢出，所以用longlong型
        for (int i = 0; i < n; ++i) 
       {
        res = res * 2 * (2 * i + 1) / (i + 2);
        }
        return (int) res;
    }
};
```

**###思路**

第二种方法就是动态规划，建立dp矩阵，dp[i]代表i个节点能组成多少种二叉搜索树，将dp[0]、dp[1]置为1。然后dp[n]的值为多少呢？

- 假设以节点值i为根节点(i<=n)，那么左子树的节点就为 ![[公式]](https://www.zhihu.com/equation?tex=1%5Csim+i-1) ,右子树的节点为 ![[公式]](https://www.zhihu.com/equation?tex=i%5Csim+n) 。
- 对于某一个根节点i，假设其左子树的组成方式为left种,右子树的组成方式为right种，那么他们一共可以组成 ![[公式]](https://www.zhihu.com/equation?tex=left%5Ctimes+right) 种二叉搜索树。
- 所以dp[n]就为将左边子树的节点数为分别设置为0个到n-1个时(要有一个根节点)，这些情况下左右子树的组成方式之积的和。

**###code**

```cpp
class Solution {
public:
    int numTrees(int n) {
        vector<int>dp(n+1,0);
        dp[0]=1;
        dp[1]=1;
        //计算dp矩阵的值。
        for(int i=2;i<=n;++i)
        {
            //左右子树一一对应，故是乘法。
            for(int l=0;l<=i-1;++l)//左边子树的节点数为0个到i-1个，因为第i个为根节点。
                dp[i]+=dp[l]*dp[i-l-1];
        }
        return dp[n];

    }
};
```