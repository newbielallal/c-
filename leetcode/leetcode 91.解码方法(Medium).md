**###题目**

一条包含字母 A-Z 的消息通过以下方式进行了编码：

![img](https://mmbiz.qpic.cn/mmbiz_svg/bj9JGugn6UeichWGHZwfNPkMgC2aw0IPsjvsO9G1IaUCKm87EYUSbnDQZoEgxkur0O0PDZJD3ceubCvcc1LyQA2qFJEDIzOCA/640?wx_fmt=svg&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1)

给定一个只包含数字的非空字符串，请计算解码方法的总数。

- 输入：“12”
- 输出：2
- 说明：可解码为 "AB"(1 2)或者 "L"(12)。

**###思路**

利用动态规划进行求解，假设有dp矩阵，其中dp[i]代表从0到i的子字符串的解码方法的总数。

首先设置dp[0]=1,dp[1]=1。dp[i]的大小肯定是由dp[i-1]和dp[i-2]所决定的，dp[i]的更新分以下三种情况：

- s[i]=0，s[i-1]!=1&&s[i-2]!=2，说明这个0不能组成10或者20，是个非法的，返回0，如果为1或者2，那么说明只能组成10或者20；
- s[i]!=0,此时我们判断s[i-1]的大小，如果s[i-1]与s[i]能够组成一个1-26之间的数字，那么说明此时的dp[i]=dp[i-1]+dp[i-2]。因为编码方式为两种情况之和，我们可以将s[i-1]与s[i]一起解码，此时解码的方式为dp[i-2]，将两者分开解码，此时解码的方式为dp[i-1]。
- s[i]!=0,s[i-1]与s[i]不能构成一个1-26数字，那么只有s[i-1]与s[i]分开解码，此时dp[i]=dp[i-1]。

但是通过上述更新规则可以发现dp[i]只与dp[i-1]与dp[i-2]有关，所以其实不用建立一个dp矩阵，直接用num1、num2代表当前数的dp[i-1]、dp[i-2]即可。答案表明，这样的速度和空间复杂度都是比较优秀的。

**###code**

```

class Solution {
public:
int numDecodings(string s) {
    if(s.size()<=0||s[0]=='0')return 0;
    int num1=1,num2=1;
    for(int i=1;i<s.size();++i)
    {
        int temp=num2;
        if(s[i]=='0')
        {
            if(s[i-1]!='1'&&s[i-1]!='2')return 0;
            num2=num1;
        }
        else
        {
            if(s[i-1]=='1'||(s[i-1]=='2'&&s[i]<'7'&&s[i]>'0'))
                num2+=num1;
        }
        num1=temp;
    }
    return num2;
}
};
```

