**###题目**

给定一个字符串 s1，我们可以把它递归地分割成两个非空子字符串，从而将其表示为二叉树，下图是字符串 s1="great"的一种可能的表示形式。

![img](https://pic3.zhimg.com/80/v2-5350c6d3a7f31b893c526d15adc4a2aa_720w.jpg)

在扰乱这个字符串的过程中，我们可以挑选任何一个非叶节点，然后交换它的两个子节点。例如，如果我们挑选非叶节点 "gr" ，交换它的两个子节点，将会产生扰乱字符串 "rgeat" 。

![img](https://pic2.zhimg.com/80/v2-4eca9828257a10558b984978368b04f9_720w.jpg)

我们将 "rgeat” 称作 "great" 的一个扰乱字符串。同样地，如果我们继续交换节点 "eat" 和 "at" 的子节点，将会产生另一个新的扰乱字符串 "rgtae" 。

![img](https://pic2.zhimg.com/80/v2-74a06ab9cdae6153a439daa2a69c95b1_720w.jpg)

我们将 "rgtae” 称作 "great" 的一个扰乱字符串。给出两个长度相等的字符串 s1 和 s2，判断 s2 是否是 s1 的扰乱字符串。

- 输入: s1 = "great", s2 = "rgeat"
- 输出: true
- 输入: s1 = "abcde", s2 = "caebd"
- 输出: false

**###思路**

这样来进行理解，给定的两个字符串s1和s2，若如果s1和s2长度不一样，那么两者不为扰动字符串，如果长度一样，在进行判断，首先字符串s1能够划分为s1_*1、s1_*2 。同理那么，s2可以划分成s2_*1、s2_*2，现在出现了两种情况：

- 没发生扰动，那么s1_*1=*s2_*1、s1_*2=*s2_*2。
- 发生了扰动，那么s1_*1=*s2_2*、s1_*2=*s2_1.*

那么只要两个字符串分割而成的子字符串之间满足上面两种情况中的任意一种，那么就可以认为它们两是扰动字符串，4个互为扰动字符串的字符串合并而来的两个字符串肯定也是互为扰动字符串。

我们建立dp矩阵， ![[公式]](https://www.zhihu.com/equation?tex=dp%5Bi%5D%5Bj%5D%5Bl%5D)表示从s1的i开始的长度为l的字符串是否和s2的j开始的长度为l的字符串互为扰动字符串。

转移方程为 ![[公式]](https://www.zhihu.com/equation?tex=dp%5Bi%5D%5Bj%5D%5Bl%5D%3D%28dp%5Bi%5D%5Bj%5D%5Bw%5D++AND+dp%5Bi%2Bw%5D%5Bj%2Bw%5D%5Bk-w%5D%29or%28dp%5Bi%5D%5Bj%2Bk%E2%88%92w%5D%5Bw%5DAND+dp%5Bi%2Bw%5D%5Bj%5D%5Bk%E2%88%92w%5D%29)

前后两个分别代表了两种情况，满足其一就可以了。

初始情况为长度是1的子串，此时只有相等才能变过去，所以相等为true，不相等为false。

**###code**

```cpp
class Solution {
public:
    bool isScramble(string s1, string s2) {
        if(s1.size()!=s2.size())return false;
        int l=s1.size();
        vector<vector<vector<int>>>dp(l,vector<vector<int>>(l,vector<int>(l+1,0)));
        for(int i=0;i<l;++i)//长度为1的情况
        {
            for(int j=0;j<l;++j)
                dp[i][j][1]= s1[i]==s2[j] ?1:0;
        }

        for(int len=2;len<=l;++len)//遍历2-n的长度
        {
            for(int s1_start=0;s1_start<=l-len;++s1_start)
            {
                for(int s2_start=0;s2_start<=l-len;++s2_start)
                {
                    for(int p_len=1;p_len<len;++p_len)//要分为两个非空子字符串
                    {//第一种情况
                        if(dp[s1_start][s2_start][p_len]&&dp[s1_start+p_len][s2_start+p_len][len-p_len])
                        {
                            dp[s1_start][s2_start][len]=1;
                            break;
                        }//第二种情况
                        if(dp[s1_start][s2_start+len-p_len][p_len]&&dp[s1_start+p_len][s2_start][len-p_len])
                        {
                            dp[s1_start][s2_start][len]=1;
                            break;
                        }
                    }
                }
            }
        }
        return dp[0][0][l];
    }
};
```

\###思路

看到别人修改成了递归版本，看起来舒服多了，也容易理解。

\###代码

```cpp
class Solution {
public:
	bool isScramble(string s1, string s2) {
		if (s1.size() != s2.size())return false;
		if (s1 == s2) return true;
		string ss1(s1);
		string ss2(s2);
		sort(ss1.begin(), ss1.end());
		sort(ss2.begin(), ss2.end());
		if (ss1 != ss2)return false;
		for (int i = 1; i < s1.size(); i++) {
			//第一种情况
			if(isScramble(s1.substr(0, i), s2.substr(0, i)) 
				&& isScramble(s1.substr(i, s1.size()), s2.substr(i, s2.size()))) {
				return true;
			}
			//第二种情况
			if (isScramble(s1.substr(0, i), s2.substr(s2.size() - i, i))
				&& isScramble(s1.substr(i, s1.size()), s2.substr(0, s2.size() - i))) {
				return true;
			}
		}
		return false;
	}
};
```