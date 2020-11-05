---
title: 28. 实现strStr()
tags:
  - c++ 
categories: c++ 
---
利用双指针，最差条件下会退化到o（m*n）；

<!-- more -->

### 题目
给定一个 haystack 字符串和一个 needle 字符串，在 haystack 字符串中找出 needle 字符串出现的第一个位置 (从0开始)。如果不存在，则返回  -1。

### 思路
很简单的思路，首先算出寻找字符串和目标字符串的长度，先做一个简单的判断，若l2>l1，则证明寻找字符串没有目标字符串长，直接输出-1，若l2等于0，则不用判断，默认寻找到了。我们设定两个索引i，j，分别指向两个字符串，从寻找字符串的第一个字符开始，若匹配上，则i和j都加一，后面的字符若不相等了，则让i指向的位置变回最开始匹配上的索引的下一位，即i=i-j，然后下次循环会i++，就指向了下一位，在i和j加一的过程中，若j等于l2，则证明全部匹配上，输出i-j，就是第一个开始匹配字符的位置。结束之后再进行一次j==l2的判断，判断成功输出i=i-j，否则匹配失败，输出-1；

### code
    int strStr(string haystack, string needle) {
        int l1=haystack.size();
        int l2=needle.size();
        if(l2>l1)
            return -1;
        if(l2==0)
            return 0;
        int j=0;//needle指针
        int i=0;
        for (i = 0; i < l1; ++i) {
            if (j==l2){//判断完成
                return i - l2;
            }
            if (haystack[i] == needle[j]){
                j++;
            } 
            else{
                i -= j;
                j=0;
            }
        }
        if (j==l2){//判断完成
            return i - l2;
        }
        return -1;
    }


