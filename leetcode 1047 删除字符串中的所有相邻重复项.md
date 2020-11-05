---
title: leetcode 1047 删除字符串中的所有相邻重复项
tags:
  - c++ 
categories: c++ 
---
直接利用每次新加入的元素和最尾部元素大小进行比较即可。
<!-- more -->

### 题目
给出由小写字母组成的字符串 S，重复项删除操作会选择两个相邻且相同的字母，并删除它们。

在 S 上反复执行重复项删除操作，直到无法继续删除。

在完成所有重复项删除操作后返回最终的字符串。答案保证唯一。
### 思路
首先定义一个答案字符串，然后遍历需要删除的字符串，然后若答案字符串不为空且最后一个字符等于当前遍历到的字符，直接删除掉答案字符串的最后一个字符，否则将此字符添加进答案字符串。
### code
     string removeDuplicates(string S) {
        string res;
        for(auto &c:S)
        {
            if(!res.empty()&&res.back()==c)
                res.pop_back();
            else
                res.push_back(c);
        }
        return res;
    }

