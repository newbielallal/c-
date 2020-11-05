---
title: leetcode 32 最长有效括号
tags:
  - c++ 
categories: c++ 
---
动态规划
<!-- more -->

### 题目

给定一个只包含 '(' 和 ')' 的字符串，找出最长的包含有效括号的子串的长度。

示例 1:

输入: "(()"
输出: 2
解释: 最长有效括号子串为 "()"
示例 2:

输入: ")()())"
输出: 4
解释: 最长有效括号子串为 "()()"


### 思路

题目说了是子串，所以一定要连续的，比如()(()就的最长合理子串就是2，两对括号之间被（隔开了.所以说找到一对合理的括号，同时要与它们的前一位进行联系。很明显就需要使用动态规划，用dp矩阵记录每个位置的最长合理子串。

申请一个长度为字符串长度的一维数组dp，其中dp[i]代表的是在字符串中，从下标为0的字符到下标为i的字符形成（子串中一定要包含下标为i的字符）的子串中最长的子串。
再申请一个stack，用来存储左括号。
dp的转移方程为：
dp[i]=dp[pre]+i-st.top()+1 ,其中pre等于st.top()-1.pre小于0时，不用加上dp[pre].

以字符串()()(()()举例说明：
遍历   处理
(    压入stack中,dp[0]=0.
）   遇到右括号，更新dp[1]=0+1-0+1=2,因为pre=0-1=-1，所以直接加0；
(    直接压入stack中，dp[2]=0,包含s[2]的情况下，无法形成合理的子串。
)    遇到右括号，更新dp[3]=2+3-2+1=4,因为pre=2-1=1，dp[1]=2；
(    压入stack中,dp[4]=0.
(    压入stack中,dp[5]=0.
)    遇到右括号，更新dp[6]=0+6-5+1=2,因为pre=5，所以直接加0；
(    压入stack中,dp[7]=0.
)    遇到右括号，更新dp[8]=2+8-7+1=4,因为pre=6，所以直接加2；
所以最后得出结果为4.

### code

    class Solution {
	public:
	    int longestValidParentheses(string s) {
	        int l=s.size();
	        int res=0;
	        vector<int>dp(l,0);
	        stack<int>st;
	        for(int i=0;i<l;++i)
	        {
	            if(s[i]=='(')
	            {
	                st.push(i);
	            }
	            else
	            {
	                if(!st.empty())
	                {
	                    int pre=st.top()-1;
	                    int len=0;
	                    if(pre>=0)
	                    {
	                        len=dp[pre]+i-st.top()+1;
	                    }
	                    else
	                    {
	                        len=i-st.top()+1;
	                    }
	                    res=max(res,len);
	                    dp[i]=len;
	                    st.pop();
	                }
	            }
	        }
	        return res;
	    }
	};


