---
title: leetcode 81 搜索旋转排序数组 II
tags:
  - c++ 
categories: c++ 
---
这个题目要分情况来讨论，可以直接使用O（n）的时间复杂度暴力解法，也可以用二分查找法。

<!-- more -->

### 题目
假设按照升序排序的数组在预先未知的某个点上进行了旋转。

( 例如，数组 [0,0,1,2,2,5,6] 可能变为 [2,5,6,0,0,1,2] )。

编写一个函数来判断给定的目标值是否存在于数组中。若存在返回 true，否则返回 false。

### 思路
不是完完全全的log n，在特殊情况下会退化成O（n），例如数组全部数是一样的情况下。


### code
    bool search(vector<int>& nums, int target) {
        if(nums.size()<1)
            return false;
        int l=0;
        int r=nums.size()-1;
        while(l<=r)
        {
            int mid=l+((r-l)>>1);
            if(target==nums[mid])
                return true;
            if(nums[mid]>nums[l])//left is 升序，按照数组的构造定义得出
            {
                if(target>=nums[l]&&target<=nums[mid])//如果目标值大于左值并且小于等于中间值，若存在则肯定在左边，否则在右边。
                    r=mid-1;
                else
                    l=mid+1;
            }
            else if(nums[mid] < nums[l])//右边升序
            {
                if( (target >= nums[mid]) && (target <= nums[r]))
                    l = mid+1;
                else
                    r = mid - 1;
            }
            else //此情况下退化成O（n）；
                l=l+1;
        }
        return false;
    }