---
title: leetcode 650 只有两个键的键盘
tags:
  - c++ 
categories: c++ 
---
最开始想岔了，想去寻找它们的规律，后来才想明白。

<!-- more -->

### 题目
最初在一个记事本上只有一个字符 'A'。你每次可以对这个记事本进行两种操作：

1、Copy All (复制全部) : 你可以复制这个记事本中的所有字符(部分的复制是不允许的)。
2、Paste (粘贴) : 你可以粘贴你上一次复制的字符。
给定一个数字 n 。你需要使用最少的操作次数，在记事本中打印出恰好 n 个 'A'。输出能够打印出 n 个 'A' 的最少操作次数。

示例 1:

输入: 3
输出: 3
解释:
最初, 我们只有一个字符 'A'。
第 1 步, 我们使用 Copy All 操作。
第 2 步, 我们使用 Paste 操作来获得 'AA'。
第 3 步, 我们使用 Paste 操作来获得 'AAA'。

### 思路

要复制最少的次数，那只要确定出一个等式n=a*b，其中我们让b遍历，每个b通过a次得到n（粘贴a-1次+复制一次），然后再加上在记事本中得到b的次数，两者相加就是最终结果，然后求出最小值。所以min（n）=min（n/a）+a


### code
    class Solution {
    public:
    int minSteps(int n) {
        int i,num;
        if(n==1) return 0;
        vector<int> dp;
        dp.resize(n+1,0);
        for(num=1;num<=n;num++){
            dp[num]=num;
            i = sqrt(num);
 
            for(i=sqrt(num);i>=1;i--){
 
                if(num%i==0){
                    int tmp;
                    tmp=dp[num/i]+i;
 
                    if(tmp<dp[num]){
                        dp[num] = tmp;
                    }
                }
            }
 
        }
 
        return dp[n];
    }
    };

