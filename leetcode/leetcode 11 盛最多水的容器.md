---
title: leetcode  11. 盛最多水的容器
tags:
  - c++ 
categories: c++ 
---
可以用遍历的方法，计算每两个组成容器的边界的积水量，然后比较得出最大值就可以了，但是没有必要，因为太慢了，可以一次遍历得出最大值。

<!-- more -->

### 题目

给定 n 个非负整数 a1，a2，...，an，每个数代表坐标中的一个点 (i, ai) 。在坐标内画 n 条垂直线，垂直线 i 的两个端点分别为 (i, ai) 和 (i, 0)。找出其中的两条线，使得它们与 x 轴共同构成的容器可以容纳最多的水。

说明：你不能倾斜容器，且 n 的值至少为 2。



输入数组 [1,8,6,2,5,4,8,3,7]。在此情况下，容器能够容纳水的最大值为 49。

示例:

输入: [1,8,6,2,5,4,8,3,7]
输出: 49


### 思路

首先选择数组的第一个和最后一个数作为容器的边界，然后比较作为容器的两边的长度，放弃掉短的那边，将其往中心位置靠，


### code

    class Solution {
	public:
	    int maxArea(vector<int>& height) {
	        int max_res=0;
	        int l=0;
	        int r=height.size()-1;
	        while(l<r)
	        {
	            int res=min(height[l],height[r])*(r-l);
	            if(res>max_res)
	                max_res=res;
	            if(height[l]>height[r])
	                r--;
	            else
	                l++;
	        }
	        return max_res;
	    }
	};

