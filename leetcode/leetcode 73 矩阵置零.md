**###题目**

给定一个 *m*x*n*的矩阵，如果一个元素为 0，则将其所在行和列的所有元素都设为 0。请使用**原地**算法**。**

**###思路**

利用矩阵的第0行和第0列来记录下矩阵内部除了第0行和第0列中剩下行列中是否出现0，比如matrix[0]=[0,0,1,1,1,0,0],那么代表矩阵内部第1列、第2列、第5列、第6列都出现了0(第0列单独计算)，对于第一行来说也是同样的，所以算法流程如下：

- 首先用num_row、num_col来代表第0行和第0列中是否出现0。
- 遍历除第0行、第0列外的所有数组元素，如果matrix[i][j]==0，那么将matrix[i][0]、matrix[0][j]置为0，代表第i行、第j列出现0。
- 根据第0行、第0列中的0来更新整个矩阵。
- 根据num_row、num_col更新第0行、第0列。

**###code**

```

class Solution {
public:
void setZeroes(vector<vector<int>>& matrix) {
    if(matrix.size()==0)return;
    int num_row=1;
    int num_col=1;
    int l1=matrix.size();
    int l2=matrix[0].size();
    for(int i=0;i<l1;++i)if(matrix[i][0]==0)num_row=0;
    for(int i=0;i<l2;++i)if(matrix[0][i]==0)num_col=0;
    for(int i=1;i<l1;++i)
    {
        for(int j=1;j<l2;++j)
        {
            if(matrix[i][j]==0)
            {
                matrix[i][0]=0;
                matrix[0][j]=0;
            }
        }
    }
    for(int i=1;i<l1;++i)
    {
        if(matrix[i][0]==0)
        {
            for(int j=1;j<l2;++j)
                matrix[i][j]=0;
        }
    }
    for(int i=1;i<l2;++i)
    {
        if(matrix[0][i]==0)
        {
            for(int j=1;j<l1;++j)
                matrix[j][i]=0;
        }
    }
    if(num_row==0)for(int i=0;i<l1;++i)matrix[i][0]=0;
    if(num_col==0)for(int i=0;i<l2;++i)matrix[0][i]=0;
    return ;
}
};
```

**###思路**

遍历数组，若matrix[i][j]==0，保存下i、j，用于以后更改matrix，需要额外空间O(m+n)，第一种方法只需要常数的额外空间(num_row和num_col)。

**###code**

```
class Solution {
public:
void setZeroes(vector<vector<int>>& matrix) {
    unordered_map<int,int>rows;
    unordered_map<int,int>cols;
    for(int i=0;i<matrix.size();++i)
    {
       for(int j=0;j<matrix[0].size();++j)
        {
            if(matrix[i][j]==0)
            {
                rows[i]=1;
                cols[j]=1;
            }
        }     
    }
       for(int i=0;i<matrix.size();++i)
    {
       for(int j=0;j<matrix[0].size();++j)
        {
            if(rows.find(i)!=rows.end()||cols.find(j)!=cols.end())
            {
                matrix[i][j]=0;
            }
        }     
    }
}
};
```

