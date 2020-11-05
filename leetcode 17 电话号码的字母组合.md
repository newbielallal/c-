---
title: leetcode 17 电话号码的字母组合 
tags:
  - c++ 
categories: c++ 
---
递归的方法，其实就是深度遍历啦。
<!-- more -->

### 题目

给定一个仅包含数字 2-9 的字符串，返回所有它能表示的字母组合。

给出数字到字母的映射与电话按键相同。注意 1 不对应任何字母。



### 思路

如果用递归来写，这个问题就是比较简单的，举个例子，对于23，如何判断它能够对应的字母组合，首先2对应的字母是abc，3对应的字母是def，那么首先先将2可能对应的三种情况列出来：
a3
b3
c3  
然后再对3这个数字的进行数字到字母的映射：
ad  ae  af
bd  be  bf
cd  ce  cf
所以整个过程就是对输入字符串的数字进行挨个遍历，每遍历一个就将它对应的每个字母加上已经映射结束的字符串作为一个分支继续下去，这样直到所有数字映射完，所以分支数就是，一个数字为3，两个数字为9，三个数字为27。

### code

     class Solution {
	public:
	    void f(vector<string>&res,string &digits,int i,string res_ab)
	    {
	        if(i==digits.size())
	        {
	            res.push_back(res_ab);
	            return ;
	        }
	        switch(digits[i]-48)
	        {
	            case 2:
	                f(res,digits,i+1,res_ab+'a');
	                f(res,digits,i+1,res_ab+'b');
	                f(res,digits,i+1,res_ab+'c');
	                break;
	                case 3:
	                f(res,digits,i+1,res_ab+'d');
	                f(res,digits,i+1,res_ab+'e');
	                f(res,digits,i+1,res_ab+'f');
	                break;
	                case 4:
	                f(res,digits,i+1,res_ab+'g');
	                f(res,digits,i+1,res_ab+'h');
	                f(res,digits,i+1,res_ab+'i');
	                break;
	                case 5:
	                f(res,digits,i+1,res_ab+'j');
	                f(res,digits,i+1,res_ab+'k');
	                f(res,digits,i+1,res_ab+'l');
	                break;
	                case 6:
	                f(res,digits,i+1,res_ab+'m');
	                f(res,digits,i+1,res_ab+'n');
	                f(res,digits,i+1,res_ab+'o');
	                break;
	                case 7:
	                f(res,digits,i+1,res_ab+'p');
	                f(res,digits,i+1,res_ab+'q');
	                f(res,digits,i+1,res_ab+'r');
	                f(res,digits,i+1,res_ab+'s');
	                break;
	                case 8:
	                f(res,digits,i+1,res_ab+'t');
	                f(res,digits,i+1,res_ab+'u');
	                f(res,digits,i+1,res_ab+'v');
	                break;
	                case 9:
	                f(res,digits,i+1,res_ab+'w');
	                f(res,digits,i+1,res_ab+'x');
	                f(res,digits,i+1,res_ab+'y');
	                f(res,digits,i+1,res_ab+'z');
	                break;
	        }
	    }
	    vector<string> letterCombinations(string digits) {
	        vector<string> res;
	        if(digits.size()<=0)
	            return {};
	        f(res,digits,0,"");
	        return res;
	    }
	};