---
title: leetcode 704 二分查找
tags:
  - c++ 
categories: c++ 
---
二分法。
<!-- more -->

### 题目
给定一个 n 个元素有序的（升序）整型数组 nums 和一个目标值 target  ，写一个函数搜索 nums 中的 target，如果目标值存在返回下标，否则返回 -1。

### 思路
使用mid=left+((right-left)>>1)两个好处，一个是运算更快，另外一个是防止溢出。
### code
     int search(vector<int>& nums, int target) {
        int left=0;
        int right=nums.size()-1;
        int mid=0;
        while(left<=right)
        {
             mid=left+((right-left)>>1);
            if(nums[mid]==target)
                return mid;
            else if(nums[mid]>target)
            {
                right=mid-1;
            }
            else
                left=mid+1;
        }
        return -1;
    }

