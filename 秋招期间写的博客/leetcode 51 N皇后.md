---
title: leetcode 51 N皇后
tags:
  - c++ 
categories: c++ 
---

利用回溯法。
<!-- more -->

### 题目

n 皇后问题研究的是如何将 n 个皇后放置在 n×n 的棋盘上，并且使皇后彼此之间不能相互攻击。

给定一个整数 n，返回所有不同的 n 皇后问题的解决方案。

每一种解法包含一个明确的 n 皇后问题的棋子放置方案，该方案中 'Q' 和 '.' 分别代表了皇后和空位。

示例:

输入: 4
输出: [
 [".Q..",  // 解法 1
  "...Q",
  "Q...",
  "..Q."],

 ["..Q.",  // 解法 2
  "Q...",
  "...Q",
  ".Q.."]
]
解释: 4 皇后问题存在两个不同的解法。

### 思路

首先搞清楚N皇后的攻击手段（同一行、同一列，同一斜对角线，同一正对角线），要想互不攻击就是要不满足前面的四个攻击条件，所以明显可以使用回溯法，然后以前面的四个攻击条件作为约束，所以代码的具体脉络就是，不断像后遍历，满足遍历到长度为n（n为皇后个数）时，返回结果，遍历过程中，如果不满足四个约束条件，那么回溯倒上一步，选择一种新的方式，这里主要困难的就是四个约束条件如何满足：

1、同一行很简单，遍历的时候每一行放上一个皇后就可以了，这样放一个皇后就往下走一行，肯定满足要求。
2、同一列也比较简单，用一个n长度的vector用来保存当前列的情况（false代表该列没有过皇后，可以放置新皇后）。
3、同一正对角线（下面那个数列中的一串1就代表一个正对角线），每个n*n的矩阵都肯定有2*n-1条正对角线，每一条正对角线上的所有坐标可以明显看出横坐标和纵坐标之间的差值是不变的（同时增加或减小），中间那条正对角线是排在第n条对角线，但是它上面的坐标的差值为0，所以这里可以用 i-j+n-1判断每个坐标属于哪个正对角线。
3、同一斜对角线（下面那个数列中的一串4就代表一个正对角线），每个n*n的矩阵都肯定有2*n-1条斜对角线，每一条斜对角线上的所有坐标可以明显看出横坐标和纵坐标之间的和值是不变的（一个增加一个就减小），中间那条正对角线是排在第n条对角线，但是它上面的坐标的差值为n-1，所以这里可以用 i-j判断每个坐标属于哪个斜对角线。
1 2 2 4
2 1 4 2
2 4 1 2
4 2 2 1

具体的回溯就可以看下面的代码。

### code

	class Solution {
	public:
	    void digui(vector<vector<string>>&res,vector<bool>&cols,vector<bool> &zhengxie,vector<bool> &nixie,int n,int rows,vector<string> &temp) {
	        if(n==rows)//回溯结束
	            res.push_back(temp);
	        else{
	            for(int i=0;i<n;++i){
	                int l1=i+rows;//斜对角线，行和列的和按对角线不会变。
	                int l2=i-rows+n-1;//正对角线，行和列的差值按对角线不会变化。
	                if(zhengxie[l2]||nixie[l1]||cols[i])//已经有皇后了。
	                    continue;
	                else{
	                    temp[i][rows]='Q';//设置皇后以及相关标志信息。
	                    zhengxie[l2]=true;
	                    nixie[l1]=true;
	                    cols[i]=true;
	                    digui(res,cols,zhengxie,nixie,n,rows+1,temp);
	                    temp[i][rows]='.';//回溯。
	                    zhengxie[l2]=false;
	                    nixie[l1]=false;
	                    cols[i]=false;
	                }
	            }
	        }
	    }
	    vector<vector<string>> solveNQueens(int n) {
	        vector<vector<string>> res;//用来存储结果
	        vector<string>temp(n,string(n,'.'));//存储每个符合条件的结果
	        vector<bool>cols(n,false);//列
	        vector<bool>zhengxie(2*n-1,false);//两条对角线
	        vector<bool>nixie(2*n-1,false);
	        digui(res,cols,zhengxie,nixie,n,0,temp);//递归过程
	        return res;
	    }
	};