**###题目**

给定一组非负整数，重新排列它们的顺序使之组成一个最大的整数。

- 示例 1:
- 输入: [10,2]
- 输出: 210
- 示例 2:
- 输入: [3,30,34,5,9]
- 输出: 9534330

说明: 输出结果可能非常大，所以你需要返回一个字符串而不是整数。

**###思路**

换了一种比较方法，如果ab>ba,那么就是a比b大，因为需要把能组合之后变得更大的数弄到最前面去。

**###code**

```cpp
class Solution {
public:
    static bool cmp(string &a, string &b)
    {
        return a + b > b + a;
    }
    string largestNumber(vector<int>& nums) {
        string res;
        int l = nums.size();
        vector<string>numToString(l, "");
        
        for(int i = 0; i < l; ++i)
        {
            numToString[i] = to_string(nums[i]);
        } 

        sort(numToString.begin(), numToString.end(), cmp);
        if("0" == numToString[0])
        {
            return "0";
        }
        for(auto i :numToString)
        {
            res += i;
        }
        return res;
    }
};
```