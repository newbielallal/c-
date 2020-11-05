---
title: leetcode 46 全排列
tags:
  - c++ 
categories: c++ 
---

就是算法导论上的全排列算法做的。
<!-- more -->

### 题目

给定一个没有重复数字的序列，返回其所有可能的全排列。

示例:

输入: [1,2,3]
输出:
[
  [1,2,3],
  [1,3,2],
  [2,1,3],
  [2,3,1],
  [3,1,2],
  [3,2,1]
]



### 思路

就是全排列算法了，原理比较简单。

### code

	class Solution {
	public:
	    void digui(vector<int>& nums,int begin,int l,vector<vector<int>> &res)
	            {
	                if(begin==l)
	                    res.push_back(nums);
	                else
	                {
	                    for(int i=begin;i<=l;i++)
	                    {
	                        swap(nums[begin],nums[i]);
	                        digui(nums,begin+1,l,res);
	                        swap(nums[begin],nums[i]);
	                    }
	                }
	                return ;
	            }
	    vector<vector<int>> permute(vector<int>& nums) {
	            vector<vector<int>> res;
		        if(nums.size()==0)
		            return res;
		        int l=nums.size()-1;
		        digui(nums,0,l,res);
		        return res;  
	    }
	};