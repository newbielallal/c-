---
title: leetcode 9 回文数
tags:
  - c++ 
categories: c++ 
---
就是简单的判断回文数字。

<!-- more -->

### 题目
判断一个整数是否是回文数。回文数是指正序（从左向右）和倒序（从右向左）读都是一样的整数。

示例 1:

输入: 121
输出: true
示例 2:

输入: -121
输出: false
解释: 从左向右读, 为 -121 。 从右向左读, 为 121- 。因此它不是一个回文数。
示例 3:

输入: 10
输出: false
解释: 从右向左读, 为 01 。因此它不是一个回文数。



### 思路

就是简单的暴力法，将每个数字分别存储下来，然后从后往前对比，负数因为有符号，首先排除掉，典型的暴力法。

### code

    class Solution {
	public:
    bool isPalindrome(int x) {
        if(x<0)
            return false;//负数有符号，肯定不可能。
        vector<int>num;//存储每一位上的数字。
        while(x>0)
        {
            int temp=x%10;
            x=x/10;
            num.push_back(temp);
        }
        int l=0;
        int r=num.size()-1;
        while(l<r)//进行前后比较。
        {
            if(num[l]!=num[r])
                return false;
            l++;
            r--;
        }
        return true;
    }
	};

### 思路

同理，首先排除掉负数，其次，将x从个位开始取余数，然后将这个余数对我们的res做一个res=res*10+余数，这样x的值就被反转之后存储在了res当中，如果是个回文数，那么就肯定存在res=x，这样就省掉了数组的空间开支，而且比较速度会快很多，时间复杂度和空间复杂度都降低了。

### code
    
	class Solution {
	public:
	    bool isPalindrome(int x) {
	        if(x<0)
	            return false;
	        int x_copy=x;
	        long long res=0;//防止溢出。
	        while(x>0)
	        {
	            if(res>x_copy)return false;
	            int temp=x%10;
	            res=res*10+temp;
	            x=x/10;
	        }
	        //cout<<res;
	        if(x_copy==res)return true;
	        return false;
	    }
	};


