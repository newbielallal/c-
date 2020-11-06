**### 题目**

一个机器人位于一个 m x n 网格的左上角 （起始点在下图中标记为“Start” ）。

机器人每次只能向下或者向右移动一步。机器人试图达到网格的右下角（在下图中标记为“Finish”）。

现在考虑网格中有障碍物。那么从左上角到右下角将会有多少条不同的路径？

网格中的障碍物和空位置分别用 1 和 0 来表示。

说明：m 和 n 的值均不超过 100。

示例 1:

输入:
[
 [0,0,0],
 [0,1,0],
 [0,0,0]
]
输出: 2
解释:
3x3 网格的正中间有一个障碍物。
从左上角到右下角一共有 2 条不同的路径：
\1. 向右 -> 向右 -> 向下 -> 向下
\2. 向下 -> 向下 -> 向右 -> 向右


**### 思路**

​    思路比较简单，因为只有两个方向，所以可以这么考虑，如果要达到点(m,n),那么一共有的可能的到达方式有两种，第一个是从(m-1,n)往下走，第二个是从（m,n-1）往右走（m-1与n-1>=0），那么达到(m,n)的可能的情况就是这两个位置可能的情况相加，这样一直往回计算，直到到达点(0,0)，这个位置只有一种情况，因为直接放置在这里，所以将(0,0)置为1，其他的照常相加就好了，如果这个地方是障碍物，那么这个地方的值也设置为0就可以了，这样就可以得到最后的结果了。

**### code**



```cpp
class Solution {
public:
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
        int m=obstacleGrid.size();
        int n=obstacleGrid[0].size();//这里没考虑m为0的情况
        vector<vector<long long>>res(m,vector<long long>(n,0));
        res[0][0]=1;//初始位置为1.
        for(int i=0;i<m;++i)
        {
            for(int j=0;j<n;++j)
                {
                    if(obstacleGrid[i][j]==1)//障碍物直接置零。
                        res[i][j]=0;
                    else
                    {
                     if((i-1)>=0)//两个位置相加
                        res[i][j]+=res[i-1][j];
                     if((j-1)>=0)
                        res[i][j]+=res[i][j-1];
                    }
                }
        }
        return res.back().back();//输出最后位置
    }
};
```

![点击并拖拽以移动](data:image/gif;base64,R0lGODlhAQABAPABAP///wAAACH5BAEKAAAALAAAAAABAAEAAAICRAEAOw==)

**### 题目**

一个机器人位于一个 m x n 网格的左上角 （起始点在下图中标记为“Start” ）。

机器人每次只能向下或者向右移动一步。机器人试图达到网格的右下角（在下图中标记为“Finish”）。那么从左上角到右下角将会有多少条不同的路径？



说明：m 和 n 的值均不超过 100。

示例 1:

输入: m = 3, n = 2
输出: 3
解释:
从左上角开始，总共有 3 条路径可以到达右下角。
\1. 向右 -> 向右 -> 向下
\2. 向右 -> 向下 -> 向右
\3. 向下 -> 向右 -> 向右
示例 2:

输入: m = 7, n = 3
输出: 28


**### 思路**

​    思路和上一题完全一样，因为没有障碍物，所以可以简化很多部分。

**### code**

```cpp
class Solution {
public:
    int uniquePaths(int m, int n) {
        if (m == 0 || n == 0) return 0;
        if (m == 1 || n == 1) return 1;
        vector<vector<int>> route(m, vector<int>(n, 1));
        for (int i = 1; i < m; i++)
            for (int j = 1; j < n; j++) 
                route[i][j] = route[i - 1][j] + route[i][j - 1];
        return route[m - 1][n - 1];
    }
};
```

![点击并拖拽以移动](data:image/gif;base64,R0lGODlhAQABAPABAP///wAAACH5BAEKAAAALAAAAAABAAEAAAICRAEAOw==)