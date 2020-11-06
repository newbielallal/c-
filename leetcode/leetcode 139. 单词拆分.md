**###题目**

给定一个非空字符串 s 和一个包含非空单词列表的字典 wordDict，判定 s 是否可以被空格拆分为一个或多个在字典中出现的单词。

说明：

拆分时可以重复使用字典中的单词。

你可以假设字典中没有重复的单词。

- 输入: s = "leetcode", wordDict = ["leet", "code"]
- 输出: true
- 解释: 返回 true 因为 "leetcode" 可以被拆分成 "leet code"。

**###思路**

万物皆可动态规划，假设非空字符串s的长度为l，那么申请一个长度为l+1的数组dp，其中dp[i]代表的是长度为i的s的子字符串是否能够由wordDict中的单词拆分，所以最后只需要输出dp[l]即可，所以问题就是怎么更新dp[i]的值。

首先dp[0]的值肯定是true，然后开始更新dp[1]到dp[l]。

dp[i]的更新规则为：

设j的取值范围为： ![[公式]](https://www.zhihu.com/equation?tex=0%3C%3Dj%3Ci) ，如果有一个j满足dp[j]=true且s_temp能够在wordDict中找到，那么就让dp[i]=true,其中s_temp= ![[公式]](https://www.zhihu.com/equation?tex=s.substr%28j%2Ci-j%29) 。

更新结束后输出dp.back()的值即可。

**###code**

```cpp
class Solution {
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        int l=s.size();
        vector<bool>dp(l+1,false);
        dp[0]=true;
        for(int i=1;i<=l;++i)
        {
            for(int j=i-1;j>=0;--j)
            {
                if(dp[j]&&find(wordDict.begin(),wordDict.end(),s.substr(j,i-j))!=wordDict.end())
                {
                    dp[i]=true;
                    break;
                }
            }
        }
        return dp.back();
    }
};
```