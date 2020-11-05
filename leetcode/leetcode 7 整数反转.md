---
title: leetcode 7 整数反转
tags:
  - c++ 
categories: c++ 
---
这题目挺简单的。

<!-- more -->

### 题目
给出一个 32 位的有符号整数，你需要将这个整数中每位上的数字进行反转。

### 思路
就是取余相加除10，乘10再加余数再除10这几个操作，最后做一个判断。


### code

    int reverse(int x) {
        if (x < 10 && x > -10) {
            return x;
        }
        long result = 0;
        while (x != 0) {
            result = result * 10 + x % 10;
            x = x / 10;
        }
        if (result > 2147483647 || result < -2147483648) {
            return 0;
        }
        return (int) result;
           
    }