---
title: leetcode 34 在排序数组中查找元素的第一个和最后一个位置
tags:
  - c++ 
categories: c++ 
---
看到复杂度要求是O（log n），第一感觉就是试试二分法，并且题目也说了是有序数组。

<!-- more -->

### 题目
给定一个按照升序排列的整数数组 nums，和一个目标值 target。找出给定目标值在数组中的开始位置和结束位置。
你的算法时间复杂度必须是 O(log n) 级别。
如果数组中不存在目标值，返回 [-1, -1]。
示例 1:
输入: nums = [5,7,7,8,8,10], target = 8
输出: [3,4]
示例 2:
输入: nums = [5,7,7,8,8,10], target = 6
输出: [-1,-1]
### 思路

就是按照二分法的方法首先找到目标元素，然后在进行前后拓展，情况最差的时候会退化成n。

### code
    class Solution {
	public:
    vector<int> searchRange(vector<int>& nums, int target) {
        int left=0;
        int right=nums.size()-1;
        int index=-1;
        while(left<=right)
        {
            int mid=left+((right-left)>>1);
            if(nums[mid]==target)
            {
                index=mid;
                break;
            }
            else if(nums[mid]<target)
            {
                left=left+1;
            }
            else
                right-=1;
        }
        
        if(index==-1)
            return {-1,-1};
        vector<int>res;
        left=index;
        right=index;
        while(0<=left&&nums[left]==target)
        {
            left--;
        }
        res.push_back(left+1);
        while(right<nums.size()&&nums[right]==target)
        {
            right++;
        }
        res.push_back(right-1);
        return res;
    }
    };
### 思路

这个是复杂度为2logn的，所以满足要求，就是之前说的那种特殊的二分查找，或者说我们可以将目标数值减去0.5，然后找出大于它的最小的数值。

### code
         vector<int> searchRange(vector<int>& nums, int target) {
        //明显的二分查找,注意不能找到左边缘再循环遍历到右边缘，因为可能整个数组都是这个数，这样复杂度就是变成n+logn了
        //所以我这里可以分别找左右边缘
        if(nums.empty()) return {-1,-1};
        if(target<nums.front()||target>nums.back()) return {-1,-1};//左右边缘会异常，所以单独处理
        int i=0,j=nums.size()-1,mid;
        while(i<=j){//找到左边
            mid=(j-i)/2+i;
            if(nums[mid]>=target){
                j=mid-1;
            }else{
                i=mid+1;
            }
        }
        if(nums[i]!=target) return {-1,-1};
        int begin=i;
        j=nums.size()-1;
        while(i<=j){//从左边缘到最后开始继续二分找到右边缘
            mid=(j-i)/2+i;
            if(nums[mid]>target){
                j=mid-1;
            }else{
                i=mid+1;
            }
        }
        return {begin,j};
    }