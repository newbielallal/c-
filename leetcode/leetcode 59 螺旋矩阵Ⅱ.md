\###题目

给定一个正整数 n，生成一个包含 1 到 n2 所有元素，且元素按顺时针顺序螺旋排列的正方形矩阵。

输入: 3

输出:

[ [ 1, 2, 3 ],[ 8, 9, 4 ],[ 7, 6, 5 ]]

\###思路

按照从左到右，从上到下，从右到左，从下到上，这样四个方向循环填入数字，最后将1到 ![[公式]](https://www.zhihu.com/equation?tex=n%5E2) 都填入代表循序结束，是否调整方向由待处理的位置M[i][j]是否已经赋值为判断依据，所有赋值的数都是大于0的，所以不为0则代表M[i][j]已经赋值过了，调整方向。

\###code

```cpp
class Solution {
public:
    vector<vector<int>> generateMatrix(int n) {
        vector<vector<int>> res(n,vector<int>(n));
        int num=0,i=0,j=-1;
        while(num<n*n)
        {
            while(j+1<n&&!res[i][j+1]) res[i][++j]=++num;//从左到右
            while(i+1<n&&!res[i+1][j]) res[++i][j]=++num;//从上到下
            while(j-1>=0&&!res[i][j-1]) res[i][--j]=++num;//从右到左
            while(i-1>=0&&!res[i-1][j]) res[--i][j]=++num;//从下到上
        }
        return res;
    }
};
```