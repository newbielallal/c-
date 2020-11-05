---
title: leetcode 4. 寻找两个有序数组的中位数
tags:
  - c++ 
categories: c++ 
---
直接利用归并排序的归并函数可以实现，利用好排序数组这一条件。
<!-- more -->

### 题目

给定两个大小为 m 和 n 的有序数组 nums1 和 nums2。

请你找出这两个有序数组的中位数，并且要求算法的时间复杂度为 O(log(m + n))。

你可以假设 nums1 和 nums2 不会同时为空。

示例 1:

nums1 = [1, 3]
nums2 = [2]

则中位数是 2.0
示例 2:

nums1 = [1, 2]
nums2 = [3, 4]

则中位数是 (2 + 3)/2 = 2.5


### 思路

利用归并函数可以实现。

### code

     class Solution {
	public:
    void guibing(vector<int>&a,vector<int>&b,vector<int>&c,int l1,int l2)
    {
        
        int i=0,j=0,temp=0;
        while(i<l1&&j<l2&&temp<=(l1+l2)/2)//中位数后面的元素不用排序，因为不会用到
        {
            if(a[i]<b[j])
                c[temp]=a[i++];
            else
                c[temp]=b[j++];
            temp++;
        }
        if(i==l1&&temp<=(l1+l2)/2)
        {
            while(j<l2)
                c[temp++]=b[j++];
        }
        else if(j==l2&&temp<=(l1+l2)/2)
        {
            while(i<l1)
                c[temp++]=a[i++];
        }
        return ;
    }
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        //利用归并排序首先完成数组合并，然后选择中位数。
        int l1=nums1.size();
        int l2=nums2.size();        
        vector<int>temp(l1+l2,0);
        guibing(nums1,nums2,temp,l1,l2);
        if((l1+l2)%2==0)//判断元素的个数是奇数还是偶数，分别计算中位数。
        {
            //cout<<double(temp[(l1+l2)/2])<<" "<<double(temp[(l1+l2)/2-1]);
            return (double(temp[(l1+l2)/2])+double(temp[(l1+l2)/2-1]))/2;
        }
        else
            return double(temp[(l1+l2)/2]);
    }
	};

