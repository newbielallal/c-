**###题目**

给你一个由 '1'（陆地）和 '0'（水）组成的的二维网格，请你计算网格中岛屿的数量。

岛屿总是被水包围，并且每座岛屿只能由水平方向或竖直方向上相邻的陆地连接形成。

此外，你可以假设该网格的四条边均被水包围。

![img](https://pic2.zhimg.com/80/v2-70563efec75509916a5f13e2680ce87d_720w.png)



**###思路**

思路很简单，一说就懂，遍历这个二维网格：

1. 如果遇到0，继续处理下一个元素。
2. 如果遇到1，那么岛屿的数量加一，同时将这个1接着的所有的1全部置为0，怎么处理呢，就是找到1的上下左右的1，找到1的上下左右的1的上下左右的1，一直这样下去，直到到达网格的边界或者上下左右找不到1了，将这些1全部置为0.

最后输出岛屿的数量就可以了。

**###code**

```cpp
class Solution {
public:
    void dfs(vector<vector<char>>& grid,int i,int j)
    {
        vector<int>f1={1,-1,0,0};
        vector<int>f2={0,0,1,-1};
        grid[i][j]='0';//将其置为0
        for(int k=0;k<4;++k)
        {
            
            if((i+f1[k])<grid.size()&&(i+f1[k])>=0&&(j+f2[k])<grid[i].size()&&(j+f2[k])>=0&&grid[i+f1[k]][j+f2[k]]=='1')
            {
                dfs(grid,i+f1[k],j+f2[k]);
            }
        }
        
    }
    int numIslands(vector<vector<char>>& grid) {
        int h=grid.size();
        if(h<=0)
            return 0;
        int s=grid[0].size();
        int res=0;
        for(int i=0;i<h;++i)//遍历二位网格
        {
            for(int j=0;j<s;++j)
            {
                if(grid[i][j]=='1')
                {
                    res++;
                    dfs(grid,i,j);//找到前后左右的1.
                }
            }
        }
        return res;
    }
};
```