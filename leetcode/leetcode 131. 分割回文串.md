**###题目**

给定一个字符串 *s*，将 *s* 分割成一些子串，使每个子串都是回文串。

返回 *s* 所有可能的分割方案。

- 输入："aaaab"
- 输出：[["a","a","a","a","b"],["a","a","aa","b"],["a","aa","a","b"],["a","aaa","b"]，["aa","a","a","b"],["aa","aa","b"],["aaa","a","b"],["aaaa","b"]]

**###思路**

利用回溯法，以字符串“aab”举例。

![img](https://pic3.zhimg.com/80/v2-c4afa696b546f10f7dca217c970c10da_720w.jpg)

- 对字符串截取从长度1到最大可以截取长度
- 对每段截取出来的字符串判断是否为回文字符串。
- 若不是回文，这条分路结束。
- 若是，继续往下截取。
- 若截取完整个字符串，且都为回文，那么得到一个分割方案。

**###code**

```cpp
class Solution {
public:
    bool panduan(string s)//判断是否回文
    {
        for(int i=0;i<=s.size()/2;++i)
        {   
            if(s[i]!=s[s.size()-1-i])return false;

        }
        return true;
    }
    void huishu(string s,int i,vector<vector<string>>& res,vector<string> temp)
    {
        if(i==s.size())res.push_back(temp);//分割结束，得到分割方案
        for(int j=i;j<s.size();++j)//按长度回溯
        {
            string temp1=s.substr(i,j-i+1);
            if(panduan(temp1))
            {
                temp.push_back(temp1);
                huishu(s,j+1,res,temp);
                temp.pop_back();
            }
        }
        return;
    }
    vector<vector<string>> partition(string s) {
        vector<vector<string>>res;
        vector<string> temp;
        huishu(s,0,res,temp);
        return res;
    }
};
```