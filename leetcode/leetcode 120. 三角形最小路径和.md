**###题目**

给定一个三角形，找出自顶向下的最小路径和。每一步只能移动到下一行中相邻的结点上。

例如，给定三角形：

[

[2],

[3,4],

[6,5,7],

[4,1,8,3]

]

自顶向下的最小路径和为11（即，2 + 3 + 5 + 1 = 11）。

**###思路**

从倒数第二行开始往上处理，假设倒数第二行的每个点代表一条路径，那么它下一步走肯定是找最后一行两个可能的位置中花费最小的位置走，这样得到的才是这条路径的最小值。然后倒数第三行同理，也是找倒数第二行的最小花费，这样一直到第一行就得到了最小路径和。利用同样的方法使用自顶向下不行，因为自顶向下就好像贪婪算法一样了，贪婪算法不是所有的情况都能够得到最优值。

**###code**

```cpp
class Solution {
public:
    int minimumTotal(vector<vector<int>>& triangle) {
        if(triangle.size()==0)return 0;
        for(int i=triangle.size()-2;i>=0;--i)
        {
            for(int j=0;j<triangle[i].size();++j)
            {
               triangle[i][j]+=min(triangle[i+1][j],triangle[i+1][j+1]);
            }
        }
        return triangle[0][0];
    }
};
```