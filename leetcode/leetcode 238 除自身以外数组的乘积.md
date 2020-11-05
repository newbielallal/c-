---
title: leetcode 238 除自身以外数组的乘积
tags:
  - c++ 
categories: c++ 
---
两种方法，一个一次遍历，一个3次遍历。
<!-- more -->

### 题目

给定长度为 n 的整数数组 nums，其中 n > 1，返回输出数组 output ，其中 output[i] 等于 nums 中除 nums[i] 之外其余各元素的乘积。

示例:

输入: [1,2,3,4]
输出: [24,12,8,6]
说明: 请不要使用除法，且在 O(n) 时间复杂度内完成此题。

### 思路

两种方法，第一种就是设置两个数组，一个存储左值，一个保存右值，然后将对应的下标i的左值和右值相乘就可以了，时间复杂度为o(3n)，但是空间复杂度不满足进阶要求。

### code

     class Solution {
	public:
    vector<int> productExceptSelf(vector<int>& nums) {
        int n=nums.size();
        int left=1,right=1;     //left：从左边累乘，right：从右边累乘
        vector<int>l(n,1);
        vector<int>r(n,1);
        for(int i=1;i<n;++i)
        {
            left=left*nums[i-1];
            l[i]=left;
        }
        for(int i=n-2;i>=0;--i)
        {
            right=right*nums[i+1];
            r[i]=right;
        }
        for(int i=0;i<n;++i)
        {
            nums[i]=l[i]*r[i];
        }
        return nums;
    }
	};

### 思路

第二种方法，只需要一次遍历，并且是常数的空间复杂度，具体思路就是进行累乘，用一个left和一个right，但是区别就是需要首尾同时进行累乘，并且一个乘左值，一个乘右值，具体解析请看代码。

### code

     class Solution {
	public:
    vector<int> productExceptSelf(vector<int>& nums) {
        int n=nums.size();
        int left=1,right=1;     
        vector<int>res(n,1);
        for(int i=0;i<n;++i)
        {
            res[i]=res[i]*left;//最开始左边没有元素，所以直接乘以1，
            left=left*nums[i];//记录下从左边累乘下来的值。
            res[n-i-1]=res[n-i-1]*right;//同理，但是很明显，因为同时有了这两个累乘，所以是进行了两次乘法，分别乘以左边和右边。
            right=right*nums[n-i-1];
        }
        
        return res;
    }
	};

