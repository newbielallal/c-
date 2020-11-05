---
title: leetcode 258 各位相加
tags:
  - c++ 
categories: c++ 
---
不停取余就行了。
<!-- more -->

### 题目
给定一个非负整数 num，反复将各个位上的数字相加，直到结果为一位数。
### 思路
不停取余相加，判断是否小于10，小于就停止并输出。
### code
     int addDigits(int num) {
        int res=0;
        while(num>=10)
        {
            while(num>0)
            {

               res+=num%10;
                num=num/10;
            }
            
                num=res;
                res=0;
        }
        return num;
    }

