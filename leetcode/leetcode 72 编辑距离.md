---
title: 72.编辑距离
tags:
  - c++ 
categories: c++ 
---
动态规划

<!-- more -->

### 题目

给定两个单词 word1 和 word2，计算出将 word1 转换成 word2 所使用的最少操作数 。

你可以对一个单词进行如下三种操作：

插入一个字符
删除一个字符
替换一个字符
示例 1:

输入: word1 = "horse", word2 = "ros"
输出: 3
解释: 
horse -> rorse (将 'h' 替换为 'r')
rorse -> rose (删除 'r')
rose -> ros (删除 'e')
示例 2:

输入: word1 = "intention", word2 = "execution"
输出: 5
解释: 
intention -> inention (删除 't')
inention -> enention (将 'i' 替换为 'e')
enention -> exention (将 'n' 替换为 'x')
exention -> exection (将 'n' 替换为 'c')
exection -> execution (插入 'u')

### 思路

思路也不是很难，dp数组的长度是l1+1和l2+1，dp[i] [j]代表了长度为i（就是i，不是i+1长度，从第一个字符开始算）的word1的子串和word2长度为j（就是j，不是j+1长度，从第一个字符开始算）的子串变成相同的一个单词需要的最少操作，最后输出最后一行的最后一个元素，就代表了word1和word2变成相同单词所需要的最少操作。

所以对于整个dp数组的元素的更新来说，首先将第一行和第一列更新了，这两个的更新很简单，当i或者j其中一个为0的时候，你如果想要实现两个单词变换之后相同，那么只需要插入另外一个单词的所有字母就可以了，这也是最少的操作次数，因为一个长度为0，代表没有字母，变成另一个单词，只能插入另一个单词的所有字母速度最快。

然后对于i或者j同时不为0的情况，dp[i] [j]的值的更新有两种情况，第一种，word1[i-1]==word2[j-1] (字符串的索引要减1)，因为加上了一个相同的字母，那么说明不需要任何的操作，word1和word2此时的长度为i和j的子串需要的操作和word1和word2的长度为i-1和j-1子串次数是一致的，所以直接dp[i] [j]=dp[i-1] [j-1];。

如果说word1[i-1]！=word2[j-1],相对于dp[i] [j]此时的值来说有三种选择，第一是dp[i-1] [j-1]的值加1，为何呢，因为word1和word2此时选择的子串加上了一对不相等的字母，只要将他们修改成相等的就可以了。第二是dp[i-1] [j]的值加1，为什么呢，只要将word1新加入的那个字母删掉，那么它需要的操作就和dp[i-1] [j]一致了，所以还加上一次删除操作即可。第三种是dp[i] [j-1]的值加1，道理和第二种是相同的。所以最后结果就是dp[i] [j]=min(min(dp[i-1] [j-1],dp[i-1] [j]),dp[i] [j-1])+1;

### code

    int minDistance(string word1, string word2) {
      int l1=word1.size();
      int l2=word2.size();
      if(l1==0||l2==0)
        return max(l1,l2);
      vector<vector<int>>dp(l1+1,vector<int>(l2+1,0));
      for(int i=0;i<=l1;++i)
        dp[i][0]=i;
      for(int j=0;j<=l2;++j)
        dp[0][j]=j;
      for(int i=1;i<=l1;++i)
      {
        for(int j=1;j<=l2;++j)
        {
           if(word1[i-1]==word2[j-1])
            dp[i][j]=dp[i-1][j-1];
          else
            dp[i][j]=min(min(dp[i-1][j-1],dp[i-1][j]),dp[i][j-1])+1;
        }
      }
      return dp.back().back();
    }


