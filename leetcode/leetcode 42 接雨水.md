---
title: leetcode 42 接雨水
tags:
  - c++ 
categories: c++ 
---
难就难在如何满足它的空间和时间复杂度要求。

<!-- more -->

### 题目

给定 n 个非负整数表示每个宽度为 1 的柱子的高度图，计算按此排列的柱子，下雨之后能接多少雨水。

示例:

输入: [0,1,0,2,1,0,1,3,2,1,2,1]
输出: 6
下面的图形中，1代表柱子，2代表雨水。
       1
   12221121
 12112111111

### 思路

由上图可以明显看出，每个2都是被旁边的1两边持平或更高的，或者说旁边是2，但是旁边的2也一定是被1持平或者更高，所以也就是说要接的雨水一定首先这个位置是空的，也就是此处是没有柱子的，其次这个位置的两边或者两边延伸出去一定是被柱子左右包围的，并且接水量是以矮的那个柱子为准，毕竟木桶理论的嘛，肯定是以矮边为准。

### code

	class Solution {
	public:
	    int trap(vector<int>& height) {
	        if(height.empty())
	            return 0;
	        int n=height.size();
	        vector<int>left(n,0),right(n,0);
	        for(int i=1;i<n;++i)//找出每个位置左边最高的柱子
	        {
	            left[i]=max(left[i-1],height[i-1]);
	        }
	        for(int i=n-2;i>=0;--i)//找出每个位置右边最高的柱子
	        {
	            right[i]=max(right[i+1],height[i+1]);
	        }
	        int res=0;
	        for(int i=1;i<=n-2;++i)//找出每个位置左右最矮的柱子
             //就是接水量(此位置柱子高度低于最矮柱子的前提下)
	        {
	            res+=max((min(left[i],right[i])-height[i]),0);
	        }
	        return res;
	            
	    }
	};