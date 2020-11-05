---
title: leetcode 3. 无重复字符的最长子串
tags:
  - c++ 
categories: c++ 
---
无重复字符这一点就是题目的解题突破口。
<!-- more -->

### 题目

给定一个字符串，请你找出其中不含有重复字符的 最长子串 的长度。

示例 1:

输入: "abcabcbb"
输出: 3 
解释: 因为无重复字符的最长子串是 "abc"，所以其长度为 3。
示例 2:

输入: "bbbbb"
输出: 1
解释: 因为无重复字符的最长子串是 "b"，所以其长度为 1。
示例 3:

输入: "pwwkew"
输出: 3
解释: 因为无重复字符的最长子串是 "wke"，所以其长度为 3。
     请注意，你的答案必须是 子串 的长度，"pwke" 是一个子序列，不是子串。


### 思路
其实有点类似于暴力法了，遍历一遍字符串，遍历之前设定一个vector<char>zichuan存储最长无重复子串，遍历过程中当子串内部无元素时，直接将目前遍历到的字符加进去，当子串有元素时，对子串进行查找，看是否有等于当前遍历到的字符的字符，如果有，删除掉子串的第一个字符，再继续查找，直到找不到当前遍历的字符或者子串的长度为0为止，然后添加当前遍历的字符进去。
### code

     //这是利用数据结构deque进行操作的，之前学习stl源码的时候记得书上说的，deque在首部进行操作效率很差，然后和vector
     //进行了一下对比，vector在首部进行操作也很麻烦，但是比deque快，deque耗时48ms。
     int lengthOfLongestSubstring(string s) {
        
        if(s.size()==0)
            return 0;
        int max_len=0;
        
        deque<char>zichuan;
        for(int i=0;i<s.size();i++)
        {
            if(zichuan.size()==0)
            {
                zichuan.push_back(s[i]);
                
            }
            else
            {
                while(zichuan.size()>0&&find(zichuan.begin(),zichuan.end(),s[i])!=zichuan.end())
                {
                    
                    
                    zichuan.pop_front();
                }
                zichuan.push_back(s[i]);
                
            }
            
            if(zichuan.size()>max_len)
                max_len=zichuan.size();
        }
        return max_len;
    }
	//vecotr耗时20ms
	int lengthOfLongestSubstring(string s) {
	        
	        if(s.size()==0)
	            return 0;
	        int max_len=0;
	        
	        vector<char>zichuan;
	        for(int i=0;i<s.size();i++)
	        {
	            if(zichuan.size()==0)
	            {
	                zichuan.push_back(s[i]);
	                
	            }
	            else
	            {
	                while(zichuan.size()>0&&find(zichuan.begin(),zichuan.end(),s[i])!=zichuan.end())
	                {
	                    
	                    
	                    vector< char >::iterator k = zichuan.begin();
	
	                    zichuan.erase(k); 
	                }
	                zichuan.push_back(s[i]);
	                
	            }
	            
	            if(zichuan.size()>max_len)
	                max_len=zichuan.size();
	        }
	        return max_len;
	    }

