---
title: leetcode 49 字母异位词分组
tags:
  - c++ 
categories: c++ 
---

可以利用字典。
<!-- more -->

### 题目

给定一个字符串数组，将字母异位词组合在一起。字母异位词指字母相同，但排列不同的字符串。

示例:

输入: ["eat", "tea", "tan", "ate", "nat", "bat"],
输出:
[
  ["ate","eat","tea"],
  ["nat","tan"],
  ["bat"]
]
说明：

所有输入均为小写字母。
不考虑答案输出的顺序。

### 思路

因为题目说了，不考虑答案输出的顺序，所以可以利用字典，因为字典虽然方便但是无序，如果要求有序就不能用字典了，原理很简单，字母异位词有一个特点就是含有的字母是一样的，所以可以用一个字典，其中字典的key值是一个字母异位词的字母按照字典序进行排序的字符串，这样所有的它的字母异位词因为按字典序排序之后相等都会被归在一起，因为题目也说了是排列不同的字符串，所以也不用担心字典的无重复储存问题。

### code

	class Solution {
	public:
	    vector<vector<string>> groupAnagrams(vector<string>& strs) {
	        if(strs.size()<=0)
	        return {};
	        map<string ,vector<string>>map_res;
	        for(int i=0;i<strs.size();++i)//将所有字符串按字典序进行存储
	        {
	            string temp=strs[i];
	            sort(temp.begin(),temp.end());
	            map_res[temp].push_back(strs[i]);
	        }
	        vector<vector<string>>res;
	        for(auto m:map_res)//按照字典存储的结果按key值进行存储。
	            res.push_back(m.second);
	        return res;
	    }
	};