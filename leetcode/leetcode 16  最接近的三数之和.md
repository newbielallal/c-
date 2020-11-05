---
title: leetcode 16 最接近的三数之和 
tags:
  - c++ 
categories: c++ 
---
三数之和变形来的
<!-- more -->

### 题目

给定一个包括 n 个整数的数组 nums 和 一个目标值 target。找出 nums 中的三个整数，使得它们的和与 target 最接近。返回这三个数的和。假定每组输入只存在唯一答案。

例如，给定数组 nums = [-1，2，1，-4], 和 target = 1.

与 target 最接近的三个数的和为 2. (-1 + 2 + 1 = 2).



### 思路

道理其实和三数之和那个题目一样的，只是加了两个int变量，每次记录下三数之和和目标值之间的差值，最后找到最小的那个三数之和返回即可。  

### code

     class Solution {
	public:
	    int threeSumClosest(vector<int>& nums, int target) {
	        if(nums.size()<3)
	            return {};
	        sort(nums.begin(),nums.end());
	        int jianzhi=INT_MAX;
	        int min_res=nums[0]+nums[1]+nums[2];
	        
	        for(int i=0;i<nums.size()-2;++i)
	        {
	            int l=i+1;
	            int r=nums.size()-1;
	            while(l<r)
	            {
	                
	                if(i==0||nums[i]!=nums[i-1])
	                {
	                    int res=target-(nums[i]+nums[l]+nums[r]);
	                    
	                    if(res==0)
	                        return target;
	                    else if(res>0)
	                    {
	                        
	                        if(abs(res)<jianzhi)
	                        {
	                            jianzhi=abs(res);
	                            min_res=nums[i]+nums[l]+nums[r];
	                        }
	                        l++;
	                    }
	                    else
	                    {
	                        
	                        if(abs(res)<jianzhi)
	                           {  jianzhi=abs(res);
	                            min_res=nums[i]+nums[l]+nums[r];}
	                        r--;
	                    }
	                    //cout<<res<<" "<<min_res<<endl;
	                }
	                else
	                    break;
	                
	                
	            }
	        }
	        return min_res;
	    } 
	};