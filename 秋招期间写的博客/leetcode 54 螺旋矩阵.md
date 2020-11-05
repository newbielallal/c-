---
title: leetcode 54 螺旋矩阵
tags:
  - c++ 
categories: c++ 
---

思路清晰即可，可以用一个辅助矩阵来降低难度。
<!-- more -->

### 题目

给定一个包含 m x n 个元素的矩阵（m 行, n 列），请按照顺时针螺旋顺序，返回矩阵中的所有元素。

示例 1:

输入:
[
 [ 1, 2, 3 ],
 [ 4, 5, 6 ],
 [ 7, 8, 9 ]
]
输出: [1,2,3,6,9,8,7,4,5]
示例 2:

输入:
[
  [1, 2, 3, 4],
  [5, 6, 7, 8],
  [9,10,11,12]
]
输出: [1,2,3,4,8,12,11,10,9,5,6,7]


### 思路

方法有点取巧了，首先建立一个m*n的辅助矩阵用来表示该位置是否遍历过了，然后设置四个方向矩阵，最开始向右，然后向下，然后向左，最后向上，这样四个一次循环，直到将所有的元素都遍历一遍就结束了，具体可以看代码注释。

### code

	class Solution {
	public:
	    vector<int> spiralOrder(vector<vector<int>>& matrix) {
	        int l1=matrix.size();
	        if(l1==0)
	            return {};
	        int l2=matrix[0].size();
	        int num=1;
	        vector<int>res;
	        vector<vector<bool>>flag(l1,vector<bool>(l2,true));//辅助矩阵
	        int turn=0;
	        int i=0,j=0;
	        vector<vector<int>>fangxiang;//四个方向矩阵
	        fangxiang.push_back({0,1});
	        fangxiang.push_back({1,0});
	        fangxiang.push_back({0,-1});
	        fangxiang.push_back({-1,0});
	        res.push_back(matrix[i][j]);//先将（0，0）放入res中
	        flag[0][0]=false;
	        while(num!=l1*l2)
	        {   turn=turn%4;//四个方向内循环
	            if(i+fangxiang[turn][0]>=0&&i+fangxiang[turn][0]<l1&&j+fangxiang[turn][1]>=0&&j+fangxiang[turn][1]<l2&&flag[i+fangxiang[turn][0]][j+fangxiang[turn][1]]==true)//是否越界以及是否遍历过了
	            {
	                i+=fangxiang[turn][0];
	                j+=fangxiang[turn][1];
	                 res.push_back(matrix[i][j]);
	                flag[i][j]=false;
	                num++;
	            }
	            else//转向
	            {
	                turn++;
	            }
	        }
	        return res;
	    }
	};