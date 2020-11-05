---
title: leetcode 39 组合总和
tags:
  - c++ 
categories: c++ 
---
回溯法。

<!-- more -->

### 题目

给定一个无重复元素的数组 candidates 和一个目标数 target ，找出 candidates 中所有可以使数字和为 target 的组合。

candidates 中的数字可以无限制重复被选取。

说明：

所有数字（包括 target）都是正整数。
解集不能包含重复的组合。 
示例 1:

输入: candidates = [2,3,6,7], target = 7,
所求解集为:
[
  [7],
  [2,2,3]
]
示例 2:

输入: candidates = [2,3,5], target = 8,
所求解集为:
[
  [2,2,2,2],
  [2,3,3],
  [3,5]
]

### 思路

依然是利用回溯法，设置一个数组temp用来存储数字组合，首先将candidates的第一个数字放进temp当中，然后再在candidates中寻找下一个放入temp当中的数字，然后再将target减去放入的数字 这里注意，因为可以重复，所以依然是可以将candidates的第一个数字放入，然后依次这样放入数字，直到target等于0，证明找到了一个合理的组合，添加入最后结果当中。

### code

    class Solution {
	public:
	    void add(int index,vector<int>& candidates,vector<int>& temp,int target,vector<vector<int>>& res)
	    {
	        if(target<=0)
	        {
	            if(target==0)
	            {
	                res.push_back(temp);
	                
	            }
	            return ;
	        }
	       // cout<<1;
	        for(int i=index;i<candidates.size();++i)
	        {
	            temp.push_back(candidates[i]);
	            add(i,candidates,temp,target-candidates[i],res);
	            temp.pop_back();
	        }
	        //cout<<2;
	        return ;
	    }
	    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
	        vector<vector<int>>res;
	        vector<int>temp;
	        add(0,candidates,temp,target,res);
	        return res;
	    }
	};