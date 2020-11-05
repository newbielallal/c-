---
title: leetcode 130  被围绕的区域
tags:
  - c++ 
categories: c++ 
---
bfs
<!-- more -->

### 题目

给定一个二维的矩阵，包含 'X' 和 'O'（字母 O）。

找到所有被 'X' 围绕的区域，并将这些区域里所有的 'O' 用 'X' 填充。

示例:

X X X X
X O O X
X X O X
X O X X

运行你的函数后，矩阵变为：

X X X X
X X X X
X X X X
X O X X

解释:

被围绕的区间不会存在于边界上，换句话说，任何边界上的 'O' 都不会被填充为 'X'。 任何不在边界上，或不与边界上的 'O' 相连的 'O' 最终都会被填充为 'X'。如果两个元素在水平或垂直方向相邻，则称它们是“相连”的。

### 思路

思路挺简单的，先找出所有靠在边上的O，然后对这些O进行遍历，找出通过这些O能够到达的矩阵内部的O，将这些O全部赋值为a，最后在对矩阵进行遍历，将所有的值为a的全部赋为O，其他的赋为X，就完成要求了。

### code

     void DFS(vector<vector<char>>& a,vector<vector<int>> &fx,int i,int j)
    {
        a[i][j]='a';
        for(int k=0;k<4;++k)
        {
            if((i+fx[k][0])>=a.size()||(i+fx[k][0])<0||(j+fx[k][1])>=a[0].size()||(j+fx[k][1])<0||(a[i+fx[k][0]][j+fx[k][1]]!='O'))
                continue;
            else
                DFS(a,fx,i+fx[k][0],j+fx[k][1]);
        }
        
    }
        
    void solve(vector<vector<char>>& board) {
        if(board.size()==0)
            return ;
        vector<vector<int>>fx;
        fx.push_back({1,0});
        fx.push_back({-1,0});
        fx.push_back({0,1});
        fx.push_back({0,-1});
        for(int i=0;i<board[0].size();++i)
        {
            if(board[0][i]=='O')
                DFS(board,fx,0,i);
        }
        for(int i=0;i<board[0].size();++i)
        {
            if(board[board.size()-1][i]=='O')
            DFS(board,fx,board.size()-1,i);
        }
        for(int i=0;i<board.size();++i)
        {
            if(board[i][0]=='O')
            DFS(board,fx,i,0);
        }
        for(int i=0;i<board.size();++i)
        {
            if(board[i][board[0].size()-1]=='O')
            DFS(board,fx,i,board[0].size()-1);
        }
        for(int i=0;i<board.size();++i)
            for(int j=0;j<board[i].size();++j)
            {
                if(board[i][j]=='a')
                    board[i][j]='O';
                else
                    board[i][j]='X';
                
            }
    }

