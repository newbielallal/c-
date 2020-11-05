---
title: leetcode  6 Z 字形变换
tags:
  - c++ 
categories: c++ 
---
寻找到各个下标之间的规律就可以了，最主要的是利用这个规律编写代码。
<!-- more -->

### 题目

将一个给定字符串根据给定的行数，以从上往下、从左到右进行 Z 字形排列。

比如输入字符串为 "LEETCODEISHIRING" 行数为 3 时，排列如下：

L   C   I   R
E T O E S I I G
E   D   H   N
之后，你的输出需要从左往右逐行读取，产生出一个新的字符串，比如："LCIRETOESIIGEDHN"。

请你实现这个将字符串进行指定行数变换的函数：

string convert(string s, int numRows);
示例 1:

输入: s = "LEETCODEISHIRING", numRows = 3
输出: "LCIRETOESIIGEDHN"
示例 2:

输入: s = "LEETCODEISHIRING", numRows = 4
输出: "LDREOEIIECIHNTSG"
解释:

L     D     R
E   O E   I I
E C   I H   N
T     S     G


### 思路

首先观察这个排列出来的Z型的下标：
0 4 8   12
13579 1113
2 6 10  14
可以观察到，对于第一行来说，每个下标之间间隔是行数numRows*2-2，对于第二行来说，它的下标之间的间隔是numRows*2-4，对于最后一行来说，下标之间的间隔又是numRows*2-4。
对于行数为4的情况下：
0  6    12
1 57  1113
24 810  14
3  9    15
下标之间的关系为：
第一行和最后一行依然为numRows*2-2，
第二行为4 2 4 2，
第三行为2 4 2 4，
可以明显看出第二行的第一个间隔为numRows*2-2-2*1，第二个间隔为numRows*2-2-（numRows*2-2-2*1），如此周而复始的两个一组循环，所以可以将除去第一行和最后一行的规律具体为numRows*2-2-2*i ，numRows*2-2-（numRows*2-2-2*1），numRows*2-2-2*i ，numRows*2-2-（numRows*2-2-2*1）如此循环。

### code

     class Solution {
	public:
    string convert(string s, int numRows) {
        if (numRows == 1) return s;//只有一行，直接返回
        int l=s.size();
        if(l<=numRows)//如果长度小于行数，也是直接返回的
            return s;
		int step = numRows * 2 - 2; // 间距
		int index ;// 记录s的下标，表明下一个需要放入的元素。
		int juli = 0; // 这是每一步的步长。
		string res;
		for (int i = 0; i < numRows; i++) // i表示行号
		{
			index = i;
			juli = i * 2;
			while (index < l)//超出字符串长度计算下一层
			{
				res += s[index]; // 当前行的第一个字母
				juli = step - juli;// 第一次步长是step -2*i，第二次是2*i,相当于a=b-c,c=b-a,这样不断循环。 
				index += (i == 0 || i == numRows-1) ? step : juli; // 0行和最后一行使用step间距，其余使用add间距
			}
		}
		return res;
    }
	};

