**###题目**

给定一个字符串**S**和一个字符串**T**，计算在 **S** 的子序列中 **T** 出现的个数。

一个字符串的一个子序列是指，通过删除一些（也可以不删除）字符且不干扰剩余字符相对位置所组成的新字符串。（例如，"**ACE**" 是 "**ABCDE**" 的一个子序列，而 "**AEC**" 不是）

- 输入：S = "rabbbit", T = "rabbit"
- 输出：3

**###思路**

看到题目就感觉是一个很明显的动态规划问题，所以建立二维dp矩阵，其中行的长度为T的长度+1，列的长度为S的长度+1。+1为了方便计算。dp[i][j]代表的是T[0:i-1]能由S[0:j-1]以多少种方式组成，因为dp矩阵要比字符串的长度多1，所以有减一。

dp的更新为：

- ***if (T[i-1]==S[j-1]) dp[i][j]=dp[i][j-1]+dp[i-1][j-1]***

在这种情况下，那么在T(0:i-2)子串后面再跟上T[i-1]以及在S(0:j-2)子串后面再跟上S[j-1]，此时代表采用S[j-1]来组成T的子串有多少种情况，相当于在两个子串后面加上了一个完全相同字符，再加上dp[i][j-1]的原因是，不采用S[j-1]来组成T的子串情况下有多少种组成方法。这样计算了所有的可能情况，带上S[j-1]和不带它。

- ***if (T[i-1]!=S[j-1]) dp[i][j]=dp[i][j-1]***

此时因为两者不等，所以只有不带S[j-1]组成T的子串，所以等于dp[i][j-1]。

**###code**

```cpp
class Solution {
public:
    int numDistinct(string s, string t) {
        if(s.size()==0&&t.size()==0)return 1;
        vector<vector<long long>>dp(t.size()+1,vector<long long>(s.size()+1,0));
        for(int i=0;i<dp[0].size();++i)
        {
            dp[0][i]=1;
        }
        for(int i=1;i<dp.size();++i)
        {
            for(int j=1;j<dp[0].size();++j)
            {
                if(s[j-1]==t[i-1])
                {
                    dp[i][j]=dp[i-1][j-1]+dp[i][j-1];
                }
                else
                    dp[i][j]=dp[i][j-1];
            }
        }
        return dp.back().back();
    }
};
```

**###思路**

对第一种方法进行优化，可以将二维矩阵优化成一维矩阵。观察上面的二维矩阵，我们会发现每次更新矩阵的值其实只需要待更新位置的前一个位置的值以及左上方位置的值，因此可以只要一维数组，长度还是为s.size()+1，更新过程就是通过一个temp1以及temp2来保存更新前的值，这样下一次更新的时候就可以用temp1的值作为该位置的左上方的值，前一个位置的值依然是保存在dp当中的。

**###code**

```cpp
class Solution {
public:
    int numDistinct(string s, string t) {
        if(s.size()==0&&t.size()==0)return 1;
        vector<long long>dp(s.size()+1,1);
        dp[0]=0;
        for(int i=0;i<t.size();++i)
        {
            long long temp1=0;//最开始为1，其它时候为0.
            if(i==0)temp1=1;
            for(int j=0;j<s.size();++j)
            {
                long long temp2=dp[j+1];
                if(s[j]==t[i])dp[j+1]=temp1+dp[j];
                else dp[j+1]=dp[j];
                temp1=temp2;
            }
        }
        return dp.back();
    }
};
```

**###思路**

回溯法感觉也可以，不过最后超时了，63个用例只过了51个。

**###code**

```cpp
class Solution {
public:
    int res=0;
    void huishu(string &s, string &t,int l1,int l2)
    {
        if(l2==t.size())res++;
        if(l1==s.size())return;
        for(int i=l1;i<s.size();++i)
        {
            if(s[i]==t[l2])
                huishu(s,t,i+1,l2+1);
        }
        return;
    }
    int numDistinct(string s, string t) {
        huishu(s,t,0,0);
        return res;
    }
};
```