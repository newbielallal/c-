---
title: leetcode 1041 困于环中的机器人
tags:
  - c++ 
categories: c++ 
---
遍历这些数字，挨个判断。
<!-- more -->

### 题目
自除数 是指可以被它包含的每一位数除尽的数。

例如，128 是一个自除数，因为 128 % 1 == 0，128 % 2 == 0，128 % 8 == 0。

还有，自除数不允许包含 0 。

给定上边界和下边界数字，输出一个列表，列表的元素是边界（含边界）内所有的自除数。
### 思路
对范围内的数字进行判断，如果满足条件，添加进结果数组。
### code
     vector<int> selfDividingNumbers(int left, int right) {
        vector<int> res;
        int num=left;
        while(num<=right)
        {
            
            while(num>0)
            {
                
                if(num%10==0)
                    break;
                else
                {
                    int yushu=num%10;
                    if(left%yushu!=0)
                        break;
                }
                num=num/10;
                
            }
            
            if(num==0)
                res.push_back(left);
            num=++left;
            
        }
        return res;
    }

