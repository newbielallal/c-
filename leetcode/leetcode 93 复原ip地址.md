---
title: leetcode 93 复原ip地址
tags:
  - c++ 
categories: c++ 
---
就是递归，找出所有可能。
<!-- more -->

### 题目

给定一个只包含数字的字符串，复原它并返回所有可能的 IP 地址格式。

示例:

输入: "25525511135"
输出: ["255.255.11.135", "255.255.111.35"]


### 思路

将字符串的字符挨个输入组合，看满足条件不，如果满足就继续向下遍历，最后如果刚好用完字符串，就输出一个合法结果，具体的可以看到后面的代码注释。

### code

     class Solution {
		public:
	    void ip_com(string s,int k,string tmp,vector<string>& res)
	    {
	        if(k==0)//k等于0，代表4个部分都已经处理了
	        {
	            if(s.size()==0)//字符串用完了，说明是合理的结果。
	                res.push_back(tmp);
	        }
	        else
	        {
	        for(int i=1;i<=3;++i)//每个字段长度最多为3。
	        {
	            if(s.size()>=i&&istrue(s.substr(0,i)))//s满足大于等i，并且切割出来的i个字符可以组成一个0到255的数。
	            {
	                if(k==1)//表示这是最后一部分，所以不需要加上.
	                {
	                    ip_com(s.substr(i), k-1,tmp+s.substr(0,i),res);//将s剩下的部分继续递归。
	                }
	                else
	                {
	                    ip_com(s.substr(i), k-1,tmp+s.substr(0,i)+'.',res);//前三部分后面要加上.。
	                }
	            }
	        }
	        }
	    }
	    bool istrue(string a)//判断是不是在0到255之间的合法的数字。
	    {
	        if(a.size()>1&&a[0]=='0')
	            return false;
	        int m=atoi(a.c_str());
	        return m<=255&&m>=0;
	    }
	    vector<string> restoreIpAddresses(string s) {      
	        vector<string>res;//用一个res存储可能的结果。
	        ip_com(s,4,"",res);//4代表ip有四个部分，""代表刚开始的时候没有一个字符在里面
	        return res;
	    }
	};

