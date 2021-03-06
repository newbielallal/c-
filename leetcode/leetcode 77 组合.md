\### 题目

给你一个字符串 S、一个字符串 T，请在字符串 S 里面找出：包含 T 所有字母的最小子串。

示例：

输入: S = "ADOBECODEBANC", T = "ABC"
输出: "BANC"
说明：

如果 S 中不存这样的子串，则返回空字符串 ""。
如果 S 中存在这样的子串，我们保证它是唯一的答案。

\### 思路

​    思路是这样的，

\### code

```cpp
class Solution {
public:
    string minWindow(string s, string t) {
        int count[123] = {0};
        for (auto c : t) ++count[c];
        int len = 0, minLength = s.length();
        string res;
        for (int l = 0, r = 0; r < s.length(); ++r) 
        {
            if (--count[s[r]] >= 0) ++len;
            while (len == t.length())
            {
                if (r - l + 1 <= minLength) 
                {
                    minLength = r - l + 1;
                    res = s.substr(l, r - l + 1);
                }
                if (++count[s[l++]] > 0) --len;
            }
        }
        return res;
    }
};
```

![点击并拖拽以移动](data:image/gif;base64,R0lGODlhAQABAPABAP///wAAACH5BAEKAAAALAAAAAABAAEAAAICRAEAOw==)

 