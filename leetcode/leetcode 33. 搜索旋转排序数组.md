---
title: leetcode 33 搜索旋转排序数组
tags:
  - c++ 
categories: c++ 
---
二分法
<!-- more -->

### 题目

假设按照升序排序的数组在预先未知的某个点上进行了旋转。

( 例如，数组 [0,1,2,4,5,6,7] 可能变为 [4,5,6,7,0,1,2] )。

搜索一个给定的目标值，如果数组中存在这个目标值，则返回它的索引，否则返回 -1 。

你可以假设数组中不存在重复的元素。

你的算法时间复杂度必须是 O(log n) 级别。

示例 1:

输入: nums = [4,5,6,7,0,1,2], target = 0
输出: 4
示例 2:

输入: nums = [4,5,6,7,0,1,2], target = 3
输出: -1


### 思路

题目要求longn，一看就是需要二分法，但是因为是一个旋转数组，所以说在进行边界变换的时候需要注意条件。
因为是旋转了的，所以应该可以在数组中找到两个有序部分，假定分别是左边部分和右边部分。
得到nums[mid]之后，首先判断它是在左边还是右边部分，这样方便后续继续操作，判断方法就是用nums[mid]与nums[right]进行比较，如果说前者小于后者，那么它们一定是在一个有序序列中的，如果前者不小于后者，那么它们一定不在同一个有序序列中，其中nums[right]肯定是在右边那个有序序列，mid小于right，所以它一定是在左边那个有序序列当中，下面两种情况下继续进行循环：

1、mid和right处于同一个有序序列。
 首先，如果两者处于同一个有序序列，那么比较target是否在nums[mid]与nums[right]之间，如果在，那么l=mid+1，否则往左边移动，r=mid-1.
2、不处于同一有序序列
 当mid和right不在同一个有序序列之后，那么mid和left肯定在同一个有序序列，那么比较target是否在nums[mid]与nums[left]之间，如果在，那么r=mid-1，否则往右边移动，l=mid+1.

### code

	class Solution {
	public:
	    int search(vector<int>& nums, int target) {
	        if(nums.size()==0)return -1;//没有元素直接返回
	        int l=0;
	        int r=nums.size()-1;
	        while(l<=r)
	        {
	            int mid=l+((r-l)>>1);
	            
	            if(nums[mid]==target)
	                return mid;
	            if(nums[mid]<=nums[r])//说明nums[mid]是在旋转后的右边
	            {
	                if(nums[mid]<target&&nums[r]>=target)//说明在右边序列的右边，所以l=mid+1
	                {
	                    l=mid+1;
	                }
	                else//不再右边序列的右边，直接往左边移动。
	                    r=mid-1;
	            }
	            else//说明nums[mid]是在旋转后的左边
	            {
	                if(nums[mid]>target&&nums[l]<=target)//在左边部分的左边，所以玩左边移动。
	                    r=mid-1;
	                else//不再左边部分的左边，直接往右边移动。
	                    l=mid+1;
	            }
	        }
	        return -1;
	    }
	};