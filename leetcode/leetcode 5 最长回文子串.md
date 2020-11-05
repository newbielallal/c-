---
title: leetcode 5. 最长回文子串
tags:
  - c++ 
categories: c++ 
---
直接利用动态规划，主要是写好状态转移方程。
<!-- more -->

### 题目

给定一个字符串 s，找到 s 中最长的回文子串。你可以假设 s 的最大长度为 1000。

示例 1：

输入: "babad"
输出: "bab"
注意: "aba" 也是一个有效答案。
示例 2：

输入: "cbbd"
输出: "bb"




### 思路

主要是要找好动态转移方程，定义一个长宽等于字符串长度的二维数组，其中若二位数组dp [i] [j]的值为1，代表在s中从下标i开始到下标j这段长度的字符子串是回文字符串，首先，一个字符肯定是回文子串，所以将dp[i] [i]（i从0到字符串长度）都设置为1，然后开始遍历，遍历过程中主要就是转移方程了，假设有s[i]==s[j],那表明它满足了新增的两个字符相等的条件，接下来就是看这两个字符往内层的子串是否也是回文的，所以只要dp[i+1] [j-1]为1，代表从i+1到j-1都是满足回文的，那么s[i]如果等于s[j]，那么回文子串就可以加上两个新成员，还有一种就是它们两是相邻的，那么只要有j-1==1，也可以代表这是一个新增的长度为2的新回文子串，最后再找出长度最长的回文子串输出就可以了，但是这个的时间复杂度为n*2，因为有两重嵌套循环，空间复杂度也是n*2，状态转移方程为：
dp[l] [r] = (s[l]==s[r] && (r-l==1 || dp[l+1] [r-1])) ? true : false

### code

     class Solution {
	public:
    string longestPalindrome(string s) {
        //动态规划做
        int l=s.size();
        if(l==0)
            return "";
        int max_l=0,max_r=0;
        vector<vector<int>>dp(l,vector<int>(l,0));
        for(int i=0;i<l;++i)
            dp[i][i]=1;
        for(int right=1;right<l;++right)
        {
            for(int left=0;left<right;++left)
            {
                if(s[left]==s[right]&&(right-left==1||dp[left+1][right-1]))
                {
                    dp[left][right]=1;
                    if(right-left>max_r-max_l)
                    {
                        max_r=right;
                        max_l=left;
                    }
                }
            }
        }
        return s.substr(max_l,max_r-max_l+1);
            
    }
	};

### 思路

第二种思路就是中心扩展法，速度快了5倍左右吧，思想很简单，就是依次将每个字符串中的字符作为一个可能存在的回文子串的中心字符，那么中心有两种中心方式：
第一种，回文子串长度是奇数，那么就是往两边扩展的，假设中心字符下标为i，那么只要有下标为i-1和i+1的两个字符相等，那么回文子串的长度加2，并且继续一个往前，一个往后遍历，也就是说继续比较下标为i-2和i+2的两个字符，直到找到不相等的或者说到达字符串边界，那么代表以s [i]
为中心的最长回文子串找到了。
第二种，回文子串的长度是偶数，那么就先对比s[i]以及s[i+1]，如果两者相等，那么继续比较s[i-1]和s[i+2]，知道超出字符串的边界或者不相等，这样就能找到最长的回文子串，s[i]可能是中中心，也可能是右中心，但是这个不用分别计算，因为s[i]如果是这个子串的右中心，那么就一定是下一个字符的子串的左中心，所以不会漏掉。

### code

     class Solution {
	public:
    int f(string &s,int i,int len)
    {
        int l1=1;
        int l2=1;
        int l=i-1;
        int r=i+1;
        while(l>=0&&r<len)
        {
            if(s[l]==s[r])
                l1+=2;
            else
                break;
            l--;
            r++;
        }
        for (l = i, r = i+1; l >= 0 && r < s.size() && s[l] == s[r]; l--, r++);
        l2 = r - l - 1;
        return max(l1, l2);
    }
    string longestPalindrome(string s) {
        //中心扩展法
        int len=s.size();
        if(len<=1)
            return s;
        int max_len=0,start=0;
        for(int i=0;i<len;++i)
        {
            int temp=f(s,i,len);
            if(temp>max_len)
            {
                max_len=temp;
                start=i-(temp-1)/2;
            }
        }
        return s.substr(start,max_len);
            
    }
	};

