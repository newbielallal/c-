---
title: leetcode 22 括号生成
tags:
  - c++ 
categories: c++ 
---
利用回溯法。
<!-- more -->

### 题目

给出 n 代表生成括号的对数，请你写出一个函数，使其能够生成所有可能的并且有效的括号组合。

例如，给出 n = 3，生成结果为：

[
  "((()))",
  "(()())",
  "(())()",
  "()(())",
  "()()()"
]


### 思路

这个题目是一个典型的回溯法问题，总的来说就是将可能的每种组合方式都列出来，挑选出其中满足条件的，如果不满足条件，就停止回溯，具体可看下面的示意：
          n=3
          （
       ((      ()
   (()   (((  ()(  ())<不满足条件>
 (()) (()(   ()() ()((
  约束条件为左括号数目大于右括号数目，左右括号数目小于n。


### code

     class Solution {
		public:
		    void add_a(vector<string>&res,string kuohao,int left,int right,int n)
		    {
		        if(kuohao.size()==2*n)
		        {
		            res.push_back(kuohao);
		            return ;
		        }
		        if(left<n)
		        {
		            add_a(res,kuohao+'(',left+1,right,n);//不能写成++left，注意，因为下一个right并没有加上左括号。
		        }
		        if(right<left)//右括号小于左括号才是有效的组合
		        {
		            add_a(res,kuohao+')',left,right+1,n);
		        }
		        return ;
		    }
		    vector<string> generateParenthesis(int n) {
		        vector<string> res;
		        add_a(res,"",0,0,n);
		        return res;
		    }
		};