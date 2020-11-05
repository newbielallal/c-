---
title: leetcode 14. 最长公共前缀
tags:
  - c++ 
categories: c++ 
---
这个用的就是挨个对比每个字符串的相对位置的字符。
<!-- more -->

### 题目

编写一个函数来查找字符串数组中的最长公共前缀。

如果不存在公共前缀，返回空字符串 ""。

示例 1:

输入: ["flower","flow","flight"]
输出: "fl"
示例 2:

输入: ["dog","racecar","car"]
输出: ""
解释: 输入不存在公共前缀。
说明:

所有输入只包含小写字母 a-z 。



### 思路

没什么难得算法思想在里面，主要就是注意细节，思路一定要清晰，要找最长公共前缀，就将每个成员字符串的目前需要对比的字符都对比一遍，如果都相同，结果字符串上加上这个字符，继续对比下一个字符，如果没有都相等，那么就直接返回结果，

### code

     class Solution {
	public:
	    string longestCommonPrefix(vector<string>& strs) {
	        if(strs.size()<=0)//没有成员字符串，直接返回结果
	            return "";
	        
	        int index=0;//从第一个字符开始比对。
	        string str="";
	        while(1)
	        {
	            char a='a';
	            for(int i=0;i<strs.size();++i)
	            {
	                if(index>=strs[i].size())//如果超出了成员字符串的最大长度，无法对比，直接返回
	                {
	                    return str;
	                }
	                
	                if(i==0)//因为是第一个，没有可以对比的，所以保存下来。
	                    a=strs[i][index];
	                if(strs[i][index]!=a)
	                    return str;
	                if(i==strs.size()-1)//对比结束。
	                    str=str+strs[i][index];
	
	            }
	            ++index;
	            
	        }
	        return str;
	    }
	};

