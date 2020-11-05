---
title: leetcode 1. 两数之和
tags:
  - c++ 
categories: c++ 
---
利用map结构。

<!-- more -->

### 题目

给定一个整数数组 nums 和一个目标值 target，请你在该数组中找出和为目标值的那 两个 整数，并返回他们的数组下标。

你可以假设每种输入只会对应一个答案。但是，你不能重复利用这个数组中同样的元素。

示例:

给定 nums = [2, 7, 11, 15], target = 9

因为 nums[0] + nums[1] = 2 + 7 = 9
所以返回 [0, 1]


### 思路

从头开始遍历，如果找到满足的两个数就将其输出，如果没找到，就把这个数以及这个数在数组中的下标保存下来，用map进行保存，因为map特殊的存储结构，遍历时间很短，接近常数复杂度，可以接受。

### code

	class Solution {
	public:
	    vector<int> twoSum(vector<int>& nums, int target) {
	        map<int,int>value_index;
	        for(int i=0;i<nums.size();++i)
	        {
	            if(value_index.find(target-nums[i])==value_index.end())
	                value_index[nums[i]]=i;
	            else
	            {
	                //cout<<value_index[target-nums[i]]<<i;
	                return {value_index[target-nums[i]],i};
	            }
	        }
	        return {};
	    }
	};
    

