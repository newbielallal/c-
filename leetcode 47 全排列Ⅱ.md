---
title: leetcode 47 全排列Ⅱ
tags:
  - c++ 
categories: c++ 
---

全排列，加了个去重。
<!-- more -->

### 题目

给定一个可包含重复数字的序列，返回所有不重复的全排列。

示例:

输入: [1,1,2]
输出:
[
  [1,1,2],
  [1,2,1],
  [2,1,1]
]





### 思路

就是全排列算法了，原理比较简单，增加了一个去重。

### code

	class Solution {
	public:
	void digui(vector<int> nums,int begin,int l,set<vector<int>> &res)
		    {
		        if(begin==l)
		            res.insert(nums);
		        else
		        {
		            for(int i=begin;i<=l;i++)
		            {
		                if(begin!=i&&nums[begin]==nums[i])
		                    continue;
		                swap(nums[begin],nums[i]);
		                digui(nums,begin+1,l,res);
		                swap(nums[begin],nums[i]);
		            }
		        }
		        return ;
		    }
	    vector<vector<int>> permuteUnique(vector<int>& nums) {
	            
		        if(nums.size()==0)
		            return {};
	            set<vector<int>> res;
	            vector<vector<int>>res_copy;
		        int l=nums.size()-1;
		        digui(nums,0,l,res);
	            res_copy.assign(res.begin(), res.end());
		        return res_copy;    
	    }
	};