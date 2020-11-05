---
title: leetcode 1091. 二进制矩阵中的最短路径
tags:
  - c++ 
categories: c++ 
---
BFS
<!-- more -->

### 题目

在一个 N × N 的方形网格中，每个单元格有两种状态：空（0）或者阻塞（1）。

一条从左上角到右下角、长度为 k 的畅通路径，由满足下述条件的单元格 C_1, C_2, ..., C_k 组成：

    相邻单元格 C_i 和 C_{i+1} 在八个方向之一上连通（此时，C_i 和 C_{i+1} 不同且共享边或角）
    C_1 位于 (0, 0)（即，值为 grid[0][0]）
    C_k 位于 (N-1, N-1)（即，值为 grid[N-1][N-1]）
    如果 C_i 位于 (r, c)，则 grid[r][c] 为空（即，grid[r][c] == 0）

返回这条从左上角到右下角的最短畅通路径的长度。如果不存在这样的路径，返回 -1 。



示例 1：

输入：[[0,1],[1,0]]

输出：2

示例 2：

输入：[[0,0,0],[1,1,0],[1,1,0]]

输出：4

提示：

    1 <= grid.length == grid[0].length <= 100
    grid[i][j] 为 0 或 1
### 思路

利用BFS实现最短路径。

### code

     int bfs(vector<vector<int>>& grid,int N,vector<vector<int>>& visit,vector<vector<int>>& path)
    {
        queue<pair<int,int>>re;
        re.push(make_pair(0,0));
        int dx[] = { -1, -1, -1, 0, 1, 1, 1, 0};
        int dy[] = { -1, 0, 1, 1, 1, 0, -1, -1};
        while(!re.empty())
        {
            pair<int,int> a=re.front();
            re.pop();
            if(a.first==N-1&&a.second==N-1)
                return path[a.first][a.second];
            for(int i=0;i<8;++i)
            {
                int x=a.first+dx[i];
                int y=a.second+dy[i];
                if(x>=0&&x<N&&y>=0&&y<N&&visit[x][y]==0&&grid[x][y]==0)
                {
                    visit[x][y]=1;
                    path[x][y]=path[a.first][a.second]+1;
                    re.push(make_pair(x,y));
                }
            }
        }
        return -1;
        
        
    }
    int shortestPathBinaryMatrix(vector<vector<int>>& grid) {
        int N=grid.size();
        if(N<=0)
            return -1;
        if(grid[0][0]==1||grid[N-1][N-1]==1)
            return -1;
        vector<vector<int>>visit(N,vector<int>(N));
        visit[0][0]=1;
        
        vector<vector<int>>path(N,vector<int>(N));
        path[0][0]=1;
        return bfs(grid,N,visit,path);
    }

