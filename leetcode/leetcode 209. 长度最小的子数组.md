**###题目**

给定一个含有 n 个正整数的数组和一个正整数 s ，找出该数组中满足其和 ≥ s 的长度最小的 连续 子数组，并返回其长度。如果不存在符合条件的子数组，返回 0。

- 输入：s = 7, nums = [2,3,1,2,4,3]
- 输出：2
- 解释：子数组 [4,3] 是该条件下的长度最小的子数组。

**###思路**

题目要求是连续子数组，所以其实还是比较简单的，我们维护一个连续子数组，这个连续子数组的长度为l，最后一个元素是nums[i]，然后只需要记录这个连续子数组的和是否大于s，

如**果大于s**，那么记录下此时的l，用于更新返回的最短子数组长度，同时删除掉连续子数组前面的元素，删除到子数组的和不大于s为止。

**如果不大于s，**那么连续子数组继续往后添加元素，即i++,l++。

**###code**

```cpp
class Solution {
public:
    int minSubArrayLen(int s, vector<int>& nums) {
        int sum = 0;
        int res = INT_MAX;
        int l = 0;

        for(int i = 0; i < nums.size(); ++i)
        {
            sum = sum + nums[i];
            l++;
            while(sum >= s)
            {
                if(l < res)
                    res = l;
                l = l - 1;
                sum -= nums[i - l];
            }
        }
        if(res == INT_MAX)
            return 0;
        return res;
    }
};
```