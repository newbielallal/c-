---
title: leetcode 908 最小差值
tags:
  - c++ 
categories: c++ 
---
因为加上的数是在k到-k范围内，所以难度小了很多。
<!-- more -->

### 题目
给定一个整数数组 A，对于每个整数 A[i]，我们可以选择任意 x 满足 -K <= x <= K，并将 x 加到 A[i] 中。

在此过程之后，我们得到一些数组 B。

返回 B 的最大值和 B 的最小值之间可能存在的最小差值。
### 思路
因为每个数可以加上的范围是在k到-k之间，所以我们判断最大的数和最小的数之间的差值是否大于2k，如果不大于，那么我们可以改变每个数组元素加上的值，让它变成一个所有值都相等的元素，所以结果为0，如果大于2k，那么就是他们之间的差值减去2k。
### code
     int smallestRangeI(vector<int>& A, int K) {
        if(A.size()==1)
            return 0;
        sort(A.begin(),A.end());
        int num=A.back();
        num=num-A[0]-2*K;
        if(num>0)
            return num;
        return 0;
    }

