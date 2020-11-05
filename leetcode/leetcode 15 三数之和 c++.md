---
title: leetcode 15 三数之和 c++
tags:
  - c++ 
categories: c++ 
---
两数之和变形来的
<!-- more -->

### 题目

给定一个包含 n 个整数的数组 nums，判断 nums 中是否存在三个元素 a，b，c ，使得 a + b + c = 0 ？找出所有满足条件且不重复的三元组。

注意：答案中不可以包含重复的三元组。

例如, 给定数组 nums = [-1, 0, 1, 2, -1, -4]，

满足要求的三元组集合为：
[
  [-1, 0, 1],
  [-1, -1, 2]
]

### 思路

首先将数组进行排序，因为需要的是三数和为0，所以先选择一个最小的数nums[0]，因为是不需要相同的三元组和，所以nums[i]!=nums[i-1],假如相等就直接跳过，但是有一个前提就是i不能等于0，因为如果在i等于0的时候也进行nums[i]!=nums[i-1]的判断，那么在[0,0,0,0]这种样本就不能通过，因为i等于0的时候因为是第一次进行三数之和等于0的判断，结果数组中目前没有任何有效的结果，肯定不能重复，所以不需要再做nums[i]!=nums[i-1]的判断，选定i之后，因为要等于0，首先选择i后面元素中的最大值和最小值，也就是nums[i+1] and nums[len-1],再将三者的和与0做比较，大于0则代表大的那个值取得过大，需要进行索引减1操作，小于0代表小的那个值过小，将其索引加一，在这个过程中必须保证l<r，最后得到等于0的结果旧作为结果保存起来，然后防止重复值，然后i再往前加，直到加到i等于len-2为止。

### code

     class Solution {
	public:
	    vector<vector<int>> threeSum(vector<int>& nums) {
	        if(nums.size()<3)
	            return {};
	        sort(nums.begin(),nums.end());
	        vector<vector<int>>res;
	        for(int i=0;i<nums.size()-2;++i)
	        {
	            
	            
	            int l=i+1;
	            int r=nums.size()-1;
	            while(l<r)
	            {
	                
	                if(i==0||nums[i]!=nums[i-1])
	                {
	                    int target=nums[i]+nums[l]+nums[r];
	                    if(target==0)
	                    {
	                        res.push_back({nums[i],nums[l],nums[r]});
	                        l++;
	                        r--;
	                        while(l<r&&nums[l]==nums[l-1])
	                            l++;
	                        while(l<r&&nums[r]==nums[r+1])
	                            r--;
	                    }
	                    else if(target<0)
	                    {
	                        l++;
	                    }
	                    else
	                    {
	                        r--;
	                    }
	                }
	                else
	                    break;
	                
	            }
	        }
	        return res;
	    }
	    
	};

