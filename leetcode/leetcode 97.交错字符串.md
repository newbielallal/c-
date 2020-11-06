**###题目**

给定三个字符串 *s1*,*s2*,*s3*, 验证 *s3* 是否是由 *s1* 和 *s2*交错组成的。

- 输入：s1 = "aabcc", s2 = "dbbca", *s3* = "aadbbcbcac"
- 输出：true

**###思路**

最开始想到的是最简单的回溯法，然后超时了，然后看讨论区，他们把这个归在暴力法里，扎心。

**###code**

```cpp
class Solution {
public:
    bool hs(string &s1, string &s2, string &s3,int l1,int l2,int l3)
    {
        if(l3==s3.size())return true;
        bool flag1=false,flag2=false;
        if(l1<s1.size()&&s1[l1]==s3[l3]) flag1=hs(s1,s2,s3,l1+1,l2,l3+1);
        if(l2<s2.size()&&s2[l2]==s3[l3]) flag2=hs(s1,s2,s3,l1,l2+1,l3+1);
        return flag1||flag2;
    } 
    bool isInterleave(string s1, string s2, string s3) {
        if(s3.size()!=s1.size()+s2.size())return false;
        return hs(s1,s2,s3,0,0,0);
    }
};
```

\###思路

基于第一种方法进行改进的，第一种方法之所以会超时的原因是因为存在冗余计算，比如我们回溯过程中，s1的子串和s2的子串组成s3的子串的方式有很多种，但是我们会计算每一种，并且如果不同的回溯方式也会计算下去，改进方法就是建立一个二维记忆数组memo，memo[i][j]有三种取值：

- 为-1，代表为处理过，继续处理
- 为0，代表不能够组成s3，直接返回false
- 为1，代表可以组成s3，返回true

其它的回溯就和第一种方法是一样得了。

\###code

```cpp
class Solution {
public:
      bool is_Interleave(string &s1,int i,string &s2,int j,string &s3,int k,vector<vector<int>>&memo) {
       if (i == s1.size()) {
           //s1用完了，直接看s2能不能匹配上
           return s2.substr(j,s2.size()-j)==s3.substr(k,s3.size()-k);
       }
       if (j == s2.size()) {
           return s1.substr(i,s1.size()-i)==s3.substr(k,s3.size()-k);
       }//看是否处理过
       if (memo[i][j] >= 0) {
           return memo[i][j] == 1 ? true : false;
       }
       bool ans = false;//进行回溯
       if (s3[k]==s1[i]&& is_Interleave(s1,i + 1,s2,j,s3,k + 1, memo)
               || s3[k]== s2[j]&& is_Interleave(s1, i, s2, j + 1, s3, k + 1, memo)) {
           ans = true;
       }
       memo[i][j]=ans;//记录回溯结果
       return ans;
   }
    bool isInterleave(string s1, string s2, string s3) {
        if(s1.size()+s2.size()!=s3.size())return false;
        vector<vector<int>>memo(s1.size(),vector<int>(s2.size(),-1));
        return is_Interleave(s1,0,s2,0,s3,0,memo);
    }
};
```

\###思路

这种问题一般都有动态规划的解法，使用二维动态规划，首先建立一个二维dp矩阵，其中dp[i][j]代表s1长度为i的子串以及s2长度为j的子串是否可以组成s3长度为i+j的子串(子串的起始位置为0)，那么最后只需要返回 ![[公式]](https://www.zhihu.com/equation?tex=dp%5Bs1.size%28%29%5D%5Bs2.size%28%29%5D) 就可以了。然后就是如何更新dp矩阵了。

- 首先dp[0][0]=1,三个空的子串可以互相组成
- 假设i不等于0，那么代表dp[i-1][j]存在，此时如果 ![[公式]](https://www.zhihu.com/equation?tex=s1%5Bi-1%5D%3D%3Ds3%5Bi%2Bj-1%5D) (因为下标从0开始，但是i和j是代表长度)，那么肯定有 ![[公式]](https://www.zhihu.com/equation?tex=dp%5Bi%5D%5Bj%5D%3Ddp%5Bi-1%5D%5Bj%5D%7C%7Cdp%5Bi%5D%5Bj%5D) ，因为新增的s1[i-1]不影响子串的匹配。
- 假设假设j不等于0，那么代表dp[i][j-1]存在，此时如果 ![[公式]](https://www.zhihu.com/equation?tex=s1%5Bj-1%5D%3D%3Ds3%5Bi%2Bj-1%5D) (因为下标从0开始，但是i和j是代表长度)，那么肯定有 ![[公式]](https://www.zhihu.com/equation?tex=dp%5Bi%5D%5Bj%5D%3Ddp%5Bi%5D%5Bj-1%5D%7C%7Cdp%5Bi%5D%5Bj%5D) ，因为新增的s1[i-1]不影响子串的匹配。

按照这个逻辑更新数组即可。

\###code

```cpp
class Solution {
public:
    bool isInterleave(string s1, string s2, string s3) {
        if(s3.size()!=s1.size()+s2.size())return false;
        int l1=s1.size();
        int l2=s2.size();
        vector<vector<int>>dp(l1+1,vector<int>(l2+1,0));
        dp[0][0]=1;      
        for(int i=0;i<=l1;++i)
        {
            for(int j=0;j<=l2;++j)
            {
                if(i==0&j==0)continue;
                if(i!=0)
                {
                    if(s1[i-1]==s3[i+j-1])
                        dp[i][j]=dp[i-1][j]||dp[i][j];
                }
                if(j!=0)
                {
                     if(s2[j-1]==s3[i+j-1])
                        dp[i][j]=dp[i][j-1]||dp[i][j];
                }
            }    
        }
        return dp.back().back();
    }
};
```

\###思路

第三种方法还可以优化，将二维的dp优化成一维的dp。dp的长度可以为 ![[公式]](https://www.zhihu.com/equation?tex=s1.size%28%29%E6%88%96s2.size%28%29) 。以dp的长度为s2.size()为例，在遍历s1和s2的过程中更新dp的过程如下：

- 以i代表s1的子串长度，以j代表s2的子串长度。
- 假如i为0，更新规则为 ![[公式]](https://www.zhihu.com/equation?tex=dp%5Bj%5D%3D%28dp%5Bj-1%5D+and+s2%5Bj-1%5D%3D%3Ds3%5Bi%2Bj-1%5D%29) ,此时为不选s1中的字符，用s2中的字符匹配。
- 假如j为0，更新规则为 ![[公式]](https://www.zhihu.com/equation?tex=dp%5Bj%5D%3D%28dp%5Bj%5D+and+s1%5Bi-1%5D%3D%3Ds3%5Bi%2Bj-1%5D%29) ,此时不选s2中的字符，用s1中的字符匹配。
- 两者都不为0，更新规则为 ![[公式]](https://www.zhihu.com/equation?tex=dp%5Bj%5D%3D%28%28dp%5Bj%5D+and+s1%5Bi-1%5D%3D%3Ds3%5Bi%2Bj-1%5D%29%7C%7C+%28dp%5Bj+-+1%5D+and+s2%5Bj-1%5D%3D%3D+s3%5Bi%2Bj-1%5D%29%29) ,此时相当于从s1或者s2中选一个来匹配s3，任一个可以匹配的就可以继续下去了。

整个过程其实更新了是s1.size()次dp数组，假设s2的长度为l2，第一次判断s2能否组成s3的前l2的子串，第二次看能否加上一个s1的字符组成s3的前l2+1的子串，第n次判断是否能加上n-1个s1的字符组成s3的前l2+n-1的子串，每次这个进来的字符都在找地方在原来的那个字符中插入，看插入之后的子串能否匹配上s3的子串。

\###code

```cpp
class Solution {
public:
    bool isInterleave(string s1, string s2, string s3) {
        if(s3.size()!=s1.size()+s2.size())return false;
        int l1=s1.size();
        int l2=s2.size();
        vector<int>dp(l2+1,0);
        dp[0]=1;
       for (int i = 0; i <= l1; i++) {
           for (int j = 0; j <= l2; j++) {
               if(i==0&&j==0)continue;
              if (i == 0) {
                   dp[j] = (dp[j - 1] &&s2[j-1]==s3[i+j-1]);
               } 
               else if (j == 0) {
                   dp[j] = (dp[j] && s1[i-1]== s3[i+j-1]);
               } 
               else {
                   dp[j]=((dp[j]&&s1[i-1]==s3[i+j-1])|| (dp[j - 1] && s2[j-1]== s3[i+j-1]));
               }
           }
       }
       return dp.back();
    }
};
```