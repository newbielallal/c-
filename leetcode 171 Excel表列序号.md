---
title: leetcode 171 excel表列序号
tags:
  - c++ 
categories: c++ 
---
其实就相当于换成了26进制而已。
<!-- more -->

### 题目
给定一个Excel表格中的列名称，返回其相应的列序号。

例如，

    A -> 1
    B -> 2
    C -> 3
    ...
    Z -> 26
    AA -> 27
    AB -> 28 
    ...
### 思路
其实就是一个26进制转10进制。下面有一个地方要注意，res=a-'A'+1+res*26，先把减法写在前面，否则最后一个测试用例会溢出。
### code

     int titleToNumber(string s) {
        int res=0;
        for(auto a:s)
        {
            res=a-'A'+1+res*26;
        }
        return res;
    }

