---
title: leetcode 313 超级丑数
tags:
  - c++ 
categories: c++ 
---
最开始想的是对每个数num从1开始直到根号num做求取余运算，对每个结果为0的除数检测是否在primes中，若全部都在，则计数加一，直到最后计数为n就可以输出当时的num，不过超时了，这就比较尴尬啦，然后上网找的别人的代码。

<!-- more -->

### 题目
编写一段程序来查找第 n 个超级丑数。

超级丑数是指其所有质因数都是长度为 k 的质数列表 primes 中的正整数。

示例:

输入: n = 12, primes = [2,7,13,19]
输出: 32 
解释: 给定长度为 4 的质数列表 primes = [2,7,13,19]，前 12 个超级丑数序列为：[1,2,4,7,8,13,14,16,19,26,28,32] 。
说明:

1 是任何给定 primes 的超级丑数。
给定 primes 中的数字以升序排列。
0 < k ≤ 100, 0 < n ≤ 106, 0 < primes[i] < 1000 。
第 n 个超级丑数确保在 32 位有符整数范围内。

### 思路

下一个丑数建立在当前的丑数分别乘以素数表的素数所得到的最小值来构成，因此通过代码模拟这一过程即可。


### code
    class Solution {
    public:
    int nthSuperUglyNumber(int n, vector<int>& primes) {
         if (n == 1)
            return 1;
        int l = primes.size();
        vector<int> ugly(n,INT_MAX);//用于记录输出结果
        vector<int> tmp(l,1);//用于记录primes得出的结果
        vector<int> count(l,0);//输出丑数
        int next = 1;//第一个丑数为1
        for (int i = 0; i < n; i++) {
            ugly[i] = next;
            next = INT_MAX;
            for (int j = 0; j < l; j++) {
                if (tmp[j] == ugly[i])//因为是升序所以可以是== {
                    tmp[j] = ugly[count[j]]*primes[j];
                    count[j]++;
                }
                
            }
        next = min(next,*min_element(tmp.begin(),tmp.end()));
        }
        return ugly[n-1];
    }
    };
    next = min(next,*min_element(tmp.begin(),tmp.end()));
    max_element()前面不加*返回的是相应的位置，加上返回值，vector用的是tmp.begin(),tmp.end()形式，数组可以使用tmp，tmp+l形式，l为数组长度。