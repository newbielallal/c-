---
title: leetcode 36. 有效的数独
tags:
  - c++ 
categories: c++ 
---
暴力法，也没有用什么技巧。

<!-- more -->

### 题目

判断一个 9x9 的数独是否有效。只需要根据以下规则，验证已经填入的数字是否有效即可。

数字 1-9 在每一行只能出现一次。
数字 1-9 在每一列只能出现一次。
数字 1-9 在每一个以粗实线分隔的 3x3 宫内只能出现一次。
数独部分空格内已填入了数字，空白格用 '.' 表示。

示例 1:

输入:
[
  ["5","3",".",".","7",".",".",".","."],
  ["6",".",".","1","9","5",".",".","."],
  [".","9","8",".",".",".",".","6","."],
  ["8",".",".",".","6",".",".",".","3"],
  ["4",".",".","8",".","3",".",".","1"],
  ["7",".",".",".","2",".",".",".","6"],
  [".","6",".",".",".",".","2","8","."],
  [".",".",".","4","1","9",".",".","5"],
  [".",".",".",".","8",".",".","7","9"]
]
输出: true
示例 2:

输入:
[
  ["8","3",".",".","7",".",".",".","."],
  ["6",".",".","1","9","5",".",".","."],
  [".","9","8",".",".",".",".","6","."],
  ["8",".",".",".","6",".",".",".","3"],
  ["4",".",".","8",".","3",".",".","1"],
  ["7",".",".",".","2",".",".",".","6"],
  [".","6",".",".",".",".","2","8","."],
  [".",".",".","4","1","9",".",".","5"],
  [".",".",".",".","8",".",".","7","9"]
]
输出: false
解释: 除了第一行的第一个数字从 5 改为 8 以外，空格内其他数字均与 示例1 相同。但由于位于左上角的 3x3 宫内有两个 8 存在, 因此这个数独是无效的。
说明:

一个有效的数独（部分已被填充）不一定是可解的。
只需要根据以上规则，验证已经填入的数字是否有效即可。
给定数独序列只包含数字 1-9 和字符 '.' 。
给定数独永远是 9x9 形式的。

### 思路

首先判断每一行是否满足，在判断每一列是否满足，在判断每一列的三个3*3方块是否满足，就是这么暴力。

### code

    class Solution {
	public:
	    bool isValidSudoku(vector<vector<char>>& board) {
	        for(int i=0;i<9;++i)
	        {
	            vector<int>num(10,0);
	            for(int j=0;j<9;++j)
	            {
	                if(board[i][j]=='.')
	                    continue;
	                else
	                {
	                    int index=board[i][j]-'0';
	                    num[index]++;
	                    if(num[index]>1)
	                        return false;
	                }
	                
	            }
	        }
	        for(int j=0;j<9;++j)
	        {
	            vector<int>num(10,0);
	            for(int i=0;i<9;++i)
	            {
	                if(board[i][j]=='.')
	                    continue;
	                else
	                {
	                    int index=board[i][j]-'0';
	                    num[index]++;
	                    if(num[index]>1)
	                        return false;
	                }
	            }  
	        }
	        int i=0;
	        int j=0;
	        while(i<9)//判断第1列3*3方块
	        {
	            vector<int>num(10,0);
	            int l1=3;
	            while(l1--)
	            {
	                int l2=3;
	                while(l2--)
	                {
	                    if(board[i][j]!='.')
	                    {
	                        int index=board[i][j]-'0';
	                        num[index]++;
	                        if(num[index]>1)
	                            return false;
	                    }
	                    i=i+(j+1)/3;
	                    j=(j+1)%3;
	                }
	            }
	        }
	        i=0;j=3;
	        while(i<9)//判断第2列3*3方块
	        {
	            vector<int>num(10,0);
	            int l1=3;
	            while(l1--)
	            {
	                int l2=3;
	                while(l2--)
	                {
	                    if(board[i][j]!='.')
	                    {
	                        int index=board[i][j]-'0';
	                        num[index]++;
	                        if(num[index]>1)
	                            return false;
	                    }
	                    i=i+(j+1)/6;
	                    j=(j+1)%6;
	                    if(j<3)
	                        j=j+3;
	                }
	            }
	        }
	        i=0;j=6;
	        while(i<9)//判断第3列3*3方块
	        {
	            vector<int>num(10,0);
	            int l1=3;
	            while(l1--)
	            {
	                int l2=3;
	                while(l2--)
	                {
	                    if(board[i][j]!='.')
	                    {
	                        int index=board[i][j]-'0';
	                        num[index]++;
	                        if(num[index]>1)
	                            return false;
	                    }
	                    i=i+(j+1)/9;
	                    j=(j+1)%9;
	                    if(j<6)
	                        j=j+6;
	                }
	            }
	        }
	        return true;
	    }
	};

### 思路

把上面的代码简化一下。

### code

    class Solution {
	public:
	    bool isValidSudoku(vector<vector<char>>& board) {
	        vector<vector<int> > rows(10, vector<int>(10, 0));
	        vector<vector<int> > cols(10, vector<int>(10, 0));
	        vector<vector<int> > kuai(10, vector<int>(10, 0));
	        for (int i = 0; i < 9; ++i)
	        {
	            for (int j = 0; j < 9; ++j) 
	            {
	                if (board[i][j] == '.') continue;
	                int n = board[i][j] - '0';
	                int k = i / 3 * 3 + j / 3;
	                kuai[k][n] += 1;//记录在某行某列以及某块
	                rows[i][n] += 1;
	                cols[j][n] += 1;
	                if(cols[j][n]==2|| rows[i][n]==2||kuai[k][n]==2 )
	                    return false;
	            }
	        }
	
	        return true;
	    }
	};