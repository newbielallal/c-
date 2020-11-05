---
title: leetcode 37 解数独
tags:
  - c++ 
categories: c++ 
---
回溯法。

<!-- more -->

### 题目

编写一个程序，通过已填充的空格来解决数独问题。

一个数独的解法需遵循如下规则：

数字 1-9 在每一行只能出现一次。
数字 1-9 在每一列只能出现一次。
数字 1-9 在每一个以粗实线分隔的 3x3 宫内只能出现一次。
空白格用 '.' 表示。

将所有的'.'改成数字返回。

Note:

给定的数独序列只包含数字 1-9 和字符 '.' 。
你可以假设给定的数独只有唯一解。
给定数独永远是 9x9 形式的。

### 思路

利用回溯法，首先记录下每行每列每块现有的1到9，然后开始填空了，开始遍历那个9*9的board，有两种情况：

一、遇到board中的元素是数字的时候，直接跳过，遍历下一个元素。

二、遇到的是'.'，这时候就需要填空了，从1到9依次寻找，找到一个在行列块中都没有出现过的数字进行填空，如果最后所有的81个空格填空完成，那么就直接输出结果，否则要返回，将这个填空的数字改成下一个可以填入的数字，并且需要修改行列块中的相应数据，例如上次填入的是3，所以将行列快中3对应的位置置为1了，但是如果最后填入失败，需要填入其它数字，那么就需要将行列快中3对应的位置重新修改成0，然后按照同样的步骤继续进行递归。

### code

    class Solution {
	public:
	    bool back(vector<vector<char>>& board,bool &flag,int i,int j,vector<vector<int>>& rows,vector<vector<int>>& cols,vector<vector<int>>& kuai)
	    {
	        if(flag)return flag;//填空完成，直接返回
	        if(i*9+j==81)//判断是否填空完，如果填完，将标志位置为true
	        {
	            flag=true;
	            return flag;
	        }
	        int r=(i*9+j+1)/9;//下一个需要处理的位置
	        int c=(i*9+j+1)%9;
	        int z=i/3*3+j/3;//块的位置
	        if(board[i][j]!='.')//不能填，直接找下一个
	        {
	            
	            back(board,flag,r,c,rows,cols,kuai);
	        }
	        else
	        {
	        for(int temp=1;temp<=9;temp++)
	        {
	            if(rows[i][temp]!=1&&cols[j][temp]!=1&&kuai[z][temp]!=1)//在board【i】【j】中填入temp。
	            {
	                rows[i][temp]=1;
	                cols[j][temp]=1;
	                kuai[z][temp]=1;
	                board[i][j]='0'+temp;
	                if(!back(board,flag,r,c,rows,cols,kuai))//如果填入这个数字失败，那么还原数据
	                    {rows[i][temp]=0;
	                    cols[j][temp]=0;
	                    kuai[z][temp]=0;
	                    board[i][j]='.';}
	            }
	                
	        }
	        }
	        return flag;
	    }
	    void solveSudoku(vector<vector<char>>& board) {
	        vector<vector<int>>rows(10,vector<int>(10,0));
	        vector<vector<int>>cols(10,vector<int>(10,0));
	        vector<vector<int>>kuai(10,vector<int>(10,0));
	        for(int i=0;i<9;++i)//记录下board中的数字安排。
	        {
	            for(int j=0;j<9;++j)
	            {
	                if(board[i][j]=='.')continue;
	                int n=board[i][j]-'0';
	                int temp=i/3*3+j/3;
	                kuai[temp][n]=1;
	                rows[i][n]=1;
	                cols[j][n]=1;
	            }
	        }
	        bool flag=false;
	        back(board,flag,0,0,rows,cols,kuai);
	        return;
	    }
	};