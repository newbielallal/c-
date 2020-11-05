---
title: leetcode 40. 组合总和 II
tags:
  - c++ 
categories: c++ 
---
回溯法。

<!-- more -->

### 题目

给定一个数组 candidates 和一个目标数 target ，找出 candidates 中所有可以使数字和为 target 的组合。

candidates 中的每个数字在每个组合中只能使用一次。

说明：

所有数字（包括目标数）都是正整数。
解集不能包含重复的组合。 
示例 1:

输入: candidates = [10,1,2,7,6,1,5], target = 8,
所求解集为:
[
  [1, 7],
  [1, 2, 5],
  [2, 6],
  [1, 1, 6]
]
示例 2:

输入: candidates = [2,5,2,1,2], target = 5,
所求解集为:
[
  [1,2,2],
  [5]
]

### 思路

依然是回溯法，但是增加了一行代码用来避免出现重复的集合，这行代码的位置一定要在temp.push_back(candidates[index]);的后面，因为这样是先添加元素，在进行去重，可以避免数字没有使用过就被去重跳过了，也可以使用39题的解法，最后加上一个res的去重就可以了，整体思路没有变化，依然是不断添加新的元素进去，直到满足sum==target就输出结果，如果不满足，就temp.pop_back();代表这个元素被删除掉了，不用加入最后的组合当中。

### code

	   class Solution {
		public:
		    void back(vector<int>& candidates,int target,int index,int sum,vector<vector<int>> &res,vector<int>&temp)
		    {
		        if(sum==target)
		        {
		            res.push_back(temp);
		            return;
		        }
		        else
		        {
		            while(index<candidates.size()&&(sum+candidates[index]<=target))//不用if，因为后面要去重，所以用if有点不简洁。
		            {
		                temp.push_back(candidates[index]);
		                back(candidates,target,++index,sum+candidates[index],res,temp);
		                while(index<candidates.size() && candidates[index] == candidates[index-1]) ++index;//避免重复，放在这个位置避免了出现重复组合，因为是先添加数字元素的。
		                temp.pop_back();//回溯，进行下一位运算 
		
		            }
		        }
		    }
		    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
		        vector<vector<int>>res;
		        vector<int>temp;
		        sort(candidates.begin(),candidates.end());
		        back(candidates,target,0,0,res,temp);
		        return res;
		    }
		};