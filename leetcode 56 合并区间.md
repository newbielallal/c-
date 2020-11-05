---
title: leetcode 56 合并区间
tags:
  - c++ 
categories: c++ 
---
先排序再合并
<!-- more -->

### 题目

给出一个区间的集合，请合并所有重叠的区间。

示例 1:

输入: [[1,3],[2,6],[8,10],[15,18]]
输出: [[1,6],[8,10],[15,18]]
解释: 区间 [1,3] 和 [2,6] 重叠, 将它们合并为 [1,6].
示例 2:

输入: [[1,4],[4,5]]
输出: [[1,5]]
解释: 区间 [1,4] 和 [4,5] 可被视为重叠区间。




### 思路

首先将每个内部的vector按照第一个元素排列好，然后就开始合并了，合并的规则如下，首先选取第一个vector的第一个元素作为合并区间的首部，然后将第一个vector的第二个元素作为合并区间目前的尾部，记做num，然后依次往后检查所有待合并vector，有三种情况：

1、如果待合并vector的后一个元素小于num，那么说明这个vector应该被合并进区间中，继续检查下一个待合并vector。

2、如果待合并vector的后一个元素大于num，那么说明它应该在当前区间之外，然后继续看它的前一个元素，如果它的前一个元素大于等于num，那说明它和当前区间是接触的，是可以合成一个区间的，那么将num更新为该vector的后一个元素就ok了；

3、待合并vector的前后元素都大于num，那说明肯定它和上一个区间是没有接触的，此时可以将上一个区间放入结果数组中，并且重新开一个区间，然后更新num为该vector的后一个元素，暂时作为新区间的尾部，该vector的第一个元素为新区间的首部，然后继续向下合并区间。

### code

	class Solution {
	public:
	    static bool f(vector<int>&a,vector<int>&b)
	    {
	        return a[0]<b[0];
	    }
	    vector<vector<int>> merge(vector<vector<int>>& intervals) {
	        if(intervals.size()<=1)
	            return intervals;
	
	        sort(intervals.begin(),intervals.end(),f);
	
	        vector<vector<int>> res;
	        vector<int>temp;
	        temp.push_back(intervals[0][0]);
	        int num=intervals[0][1];
	        int index=1;
	        while(index<intervals.size())
	        {
	            if(intervals[index][1]>num)
	           {
	                if(intervals[index][0]<=num)
	                    num=intervals[index][1];
	                else
	                {
	                    temp.push_back(num);
	                    res.push_back(temp);
	                    temp.clear();
	                    temp.push_back(intervals[index][0]);
	                    num=intervals[index][1]; 
	                }
	            }
	            index++;
	        }
	        temp.push_back(num);
	        res.push_back(temp);
	        return res;
	    }
	};