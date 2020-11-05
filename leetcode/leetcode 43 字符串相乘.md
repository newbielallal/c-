---
title: leetcode 43 字符串相乘
tags:
  - c++ 
categories: c++ 
---
不知道算不算满足了题目要求。

<!-- more -->

### 题目

给定两个以字符串形式表示的非负整数 num1 和 num2，返回 num1 和 num2 的乘积，它们的乘积也表示为字符串形式。

示例 1:

输入: num1 = "2", num2 = "3"
输出: "6"
示例 2:

输入: num1 = "123", num2 = "456"
输出: "56088"
说明：

num1 和 num2 的长度小于110。
num1 和 num2 只包含数字 0-9。
num1 和 num2 均不以零开头，除非是数字 0 本身。
不能使用任何标准库的大数类型（比如 BigInteger）或直接将输入转换为整数来处理。


### 思路

首先，一个n位的数和一个m位的数相乘，结果最大是n+m位，知道这个之后，直接设置一个l1+l2长度的字符串用来存储结果。然后对第一个num中的每个数按位与整个num2中的数相乘，这里要注意的就是，在num1中是第i位，在num2中是第j位，那么在res中它们的乘积应该是从i+j+1开始的，因为num1和num2中一共有两个0索引，而res中只有一个，所以在res当中应当要加上1，最后就是取余求进位，这样依次循环得出结果，可以看下面的例子：

num1=234 num2=39
res=00000  add=0；
首先num1[2]*num2[1]=36，jinwei等于:res[i+j+1]=res[4]-'0'+add+36%10=6,
add=3+6/10=3
res[4]=6%10=6
同理按照循环可得res[3]=2 res[2]=1 res[1]=9 res[0]=0,最后得到结果9126.

### code

	class Solution {
	public:
	    string multiply(string num1, string num2) {
	        if(num1.empty()||num2.empty())
	            return "";
	        if(num1[0]=='0'||num2[0]=='0')//判断是否是特殊情况
	            return "0";
	        int l1=num1.size();
	        int l2=num2.size();
	        string res(l1+l2,'0');//设置一个最大长度的res
	        for(int i=l1-1;i>=0;--i)
	        {
	            int add=0;
	            for(int j=l2-1;j>=0;--j)//每一位相乘
	            {
	                int num=(num1[i]-'0')*(num2[j]-'0');
	                int jinwei=res[i+j+1]-'0'+add+num%10;//处理进位
	                res[i+j+1]='0'+jinwei%10;//直接相等，所以要加上'0'
	                add=jinwei/10+num/10;
	            }
	            res[i]+=add;//是加上，所以不用要+'0'
	        }
	        //cout<<res;
	        for(int i=0;i<res.size();++i)//去除头部的'0'
	        {
	            if(res[i]!='0')
	                return res.substr(i);
	        }
	        return "0";
	    }
	};