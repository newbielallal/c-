---
title: leetcode 30 串联所有单词的子串
tags:
  - c++ 
categories: c++ 
---
暴力法
<!-- more -->

### 题目

给定一个字符串 s 和一些长度相同的单词 words。找出 s 中恰好可以由 words 中所有单词串联形成的子串的起始位置。

注意子串要与 words 中的单词完全匹配，中间不能有其他字符，但不需要考虑 words 中单词串联的顺序。

 

示例 1：

输入：
  s = "barfoothefoobarman",
  words = ["foo","bar"]
输出：[0,9]
解释：
从索引 0 和 9 开始的子串分别是 "barfoo" 和 "foobar" 。
输出的顺序不重要, [9,0] 也是有效答案。
示例 2：

输入：
  s = "wordgoodgoodgoodbestword",
  words = ["word","good","best","word"]
输出：[]


### 思路

是利用的暴力法，利用两个map，一个用来存储words中的所有单词，并且记录下一共有多少个单词，然后第二个map在字符串进行比对的时候使用，用来存储比对了多少个单词，当两个map一样的时候，说明比对结束。

举例说明：
s = "wordgoodgoodgoodbestword",
words = ["word","good","best","word"]
首先利用m1存储下words中的单词以及个数，m1最后得到结果如下：
m1=｛"word"=2,"good"=1,"best"=1｝
然后对于s从索引0开始进行遍历，但是不用遍历到j=s.size()，只用遍历到(int)s.size()-l1*l2，l1为单词个数，l2为单词长度。
因为单词的长度都是一样的，所以每次都从s中直接截取l2长度的字符作为一个待匹配的单词temp，匹配中只有三种情况会结束匹配：
1.匹配结束，l1个单词都在这个字符串中找到了
2.temp并不存在与words中，匹配失败，这里用m1.find(temp)==m1.end()表示未找到temp
3.匹配失败，temp确实存在与words中，但是words中没有这么多个temp，这里用m2[temp]>m1[temp]来表示。

这样对于s进行匹配，情况如下：
索引 匹配情况
0：  匹配到两个good的时候停止，words中没有两个good
1：  ordg不存在
2：  rdgo不存在
3：  dgoo不存在
4：  匹配到两个good，停止
5：  oodg不存在
6：  odgo不存在
7：  dgoo不存在
8：  匹配到两个good，停止

到8就结束了，输出结果[].

### code

    class Solution {
	public:
	    vector<int> findSubstring(string s, vector<string>& words) {
	       vector<int>res;
	        
	        if(s.size()==0||words.size()==0)
	            return res;
	        map<string ,int> m1;
	        int l1=words.size();
	        int l2=words[0].size();
	        for(int i=0;i<l1;++i)//存储单词以及单词个数
	        {
	            ++m1[words[i]];
	        }
	        for(int i=0;i<=(int)s.size()-l1*l2;++i)//最开始的用的s.size()-l1*l2，一直报错，说out of range，后来才知道
             //s.size()返回的是一个无符号数，所以要先转换成int型才能正确的进行加减。不然减出来的数很大，因为符号位的原因。
	        {
	            map<string,int>m2;
	            int j;
	            for(j=0;j<l1;++j)//进行比对。
	            {
	                string temp=s.substr(i+j*l2,l2);
	                if(m1.find(temp)==m1.end())break;//在words中没有找到temp，直接跳出。
	                else
	                    ++m2[temp];
	                if(m2[temp]>m1[temp])break;//words中没有那么多个temp，跳出
	            }
	            if(j==l1)//j刚好等于l1，说明每一个都比对完成了。
	                res.push_back(i);
	        }
	        return res;
	    }
	};



