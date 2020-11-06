**\### 题目**

给定一个包含非负整数的 m x n 网格，请找出一条从左上角到右下角的路径，使得路径上的数字总和为最小。

说明：每次只能向下或者向右移动一步。

示例:

输入:
[
 [1,3,1],
 [1,5,1],
 [4,2,1]
]
输出: 7
解释: 因为路径 1→3→1→1→1 的总和最小。


**\### 思路**

​    本来想用BFS或者说Dijkstra*算法，后来发现其实可以不用，急就用动态规划写，也算偷个懒吧，题目规定了只有两个方向可以走，那么达到当前位置的最小数字总和就是那两个位置中小的那个和加上当前位置的值。*



**\### code**

```cpp
class Solution {
public:
    int minPathSum(vector<vector<int>>& grid) {
        int m=grid.size();
        int n=grid[0].size();
        vector<vector<int>>dp(m,vector<int>(n,0));
        int num=0;
        for (int i=0;i<m;++i)
        {
            dp[i][0]=grid[i][0]+num;
            num=dp[i][0];
        }
        num=0;
        for (int i=0;i<n;++i)
        {
            dp[0][i]=grid[0][i]+num;
            num=dp[0][i];
        }
        for (int i=1;i<m;++i)
        {
            for(int j=1;j<n;++j)//必须一行一行的遍历
            {
                dp[i][j]=grid[i][j]+min(dp[i-1][j],dp[i][j-1]);//找更短的那个
            }
        }
        return dp[m-1][n-1];
    }
};
```

![点击并拖拽以移动](data:image/gif;base64,R0lGODlhAQABAPABAP///wAAACH5BAEKAAAALAAAAAABAAEAAAICRAEAOw==)