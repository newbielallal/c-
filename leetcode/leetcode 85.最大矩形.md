**###题目**

给定一个仅包含 0 和 1 的二维二进制矩阵，找出只包含 1 的最大矩形，并返回其面积。

- 输入：

- ["1","0","1","0","0"]

- ["1","0","1","1","1"]

- ["1","1","1","1","1"]

- ["1","0","0","1","0"]

- 输出：6

  

**###思路**



利用动态规划，设置二维dp矩阵，其中dp[i][j]代表在第i行中包含第j个元素的最长的连续'1'的长度。例如[1,1,0,0,1,1,0,1]，相应的dp矩阵的值为[1,2,0,0,1,2,0,1]。

下一步开始遍历整个矩阵，遍历每一个元素的同时更新dp,同时计算当前所能构成的最大面积矩形，最大面积的计算原理如下：



- 假设dp[i][j]的值为5，在只考虑第i行且带上matrix[i][j]这个1时能组成的最大矩阵面积为5,因为这个矩形的高为1，底为![img](https://mmbiz.qpic.cn/mmbiz_svg/bj9JGugn6UeichWGHZwfNPgicTSP5pEQ27kgUmRqtvNE21j1y6OGDmwETe3iaWYTNgoaNwJhEXlO5qBxhQ8FlgNpaOH3iauxOrfm/640?wx_fmt=svg&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1)。

- 再考虑最大面积矩形带上第i-1行且要带上matrix[i-1][j]，此情况下能组成的最大矩形的高为2，底为![img](https://mmbiz.qpic.cn/mmbiz_svg/bj9JGugn6UeichWGHZwfNPgicTSP5pEQ27U0zhl1ic196Z5C6ctFXZVXibqicy2DSHUmgcC1hX8jsAu4lnqhqIKv66icS1YrxYcXqG/640?wx_fmt=svg&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1)

- 再考虑带上第i-2行且带上matrix[i-2][j]，此情况下能组成的最大矩形的高为3，底为![img](https://mmbiz.qpic.cn/mmbiz_svg/bj9JGugn6UeichWGHZwfNPgicTSP5pEQ27yq8GDMDYhTKJ83d9ibxyKd3wnVNFXgMlB5f6mLv1LgjVpafw3Bw5mkT3wjsKqGhBE/640?wx_fmt=svg&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1)

- 一直到第0行，此情况下的最大矩形的高为i+1,底为 ![img](https://mmbiz.qpic.cn/mmbiz_svg/bj9JGugn6UeichWGHZwfNPgicTSP5pEQ27FnAahQ9j6sgswhq2ekZPunSqvtatW794kNgFc8owCIeYt1ktKzJSqek4tyPo2yTF/640?wx_fmt=svg&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1)

  

  通过上面的计算，考虑了所有的能够组成的矩形，那么matrix能够组成的最大矩形肯定也会被计算一次，所以能够找出最大矩形面积,我个人感觉其实和暴力法差不多，但是利用了dp数组保存下来的信息可以减少很多冗余计算。

  

**###code**

```
class Solution {
public:
int maximalRectangle(vector<vector<char>>& matrix) {
    if(matrix.empty())return 0;
    int row=matrix.size(),col=matrix[0].size();
    vector<vector<int>>dp(row,vector<int>(col,0));
    int maxarea=0;
    for(int i=0;i<row;++i)
    {
        for(int j=0;j<col;++j)
        {
            if(matrix[i][j]=='1')
                dp[i][j]= j==0 ? 1:dp[i][j-1]+1;
             int width=dp[i][j];
             for(int z=i;z>=0;--z)
             {
                 if(dp[z][j]==0)//如果为0，那么后续所有的计算结果都为0，没必要算了
                    break;
                 width=min(dp[z][j],width);//找出最小长度作为宽
                 maxarea=max(maxarea,width*(i-z+1));
             }
        }
    }
    return maxarea;
}
};

```

**###思路**



官方题解提出的这个思路我还真没想到，相当于将这个矩形数组转换成一个柱状图，这样就可以用84题的解法了。

例如存在一个矩形**matrix=[1,1,1,1],[0,1,1,0],[0,0,1,1]。**

matrix[0]、matrix[0]和matrix[1]、matrix[0]和matrix[1]和matrix[2]转换成leetcode 84要求的柱形图分别是[1,1,1,1]、[0,2,2,0]、[0,0,3,1]，转换成柱形图如图所示：

![img](https://mmbiz.qpic.cn/mmbiz_png/90saic2EqxkLXt9QxQWNIoIia6hJexB1M3B8j7icHMZa1mmbdI7eNs4cydGKk7RAM0J4flE8zicjmM2oOSz7hcdptg/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1)



![img](https://mmbiz.qpic.cn/mmbiz_png/90saic2EqxkLXt9QxQWNIoIia6hJexB1M3vj4naawN55LV0hKCIEtslLBsM3jQZ110rCd6sGLSN6PickbfSus8LHA/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1)

![img](https://mmbiz.qpic.cn/mmbiz_png/90saic2EqxkLXt9QxQWNIoIia6hJexB1M3BpudgZBT14c2vxu4DpVH86TicMQtaQYic6lQOciaAgTyia5XByyMLEPUiag/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1)



利用84题的解法分别求出上面三个柱形图的最大面积即可，所以整个算法流程为：

- 将矩形matrix按照1行到n行分别求出矩形图。
- 利用84题的解法求出每个矩形图的最大面积。

**###code**

```

class Solution {
public:
int max_area_f(vector<int>heights)
{
    stack<int>s;
    s.push(-1);//加上方便计算
    int max_res=0;
    for(int i=0;i<heights.size();++i)
    {
        while(s.top()!=-1&&heights[i]<=heights[s.top()])
        {
            int index=s.top();
            s.pop();
            max_res=max(max_res,heights[index]*(i-s.top()-1));
        }
        s.push(i);
    }
    while(s.top()!=-1)
    {
        int index=s.top();
        s.pop();
        max_res=max(max_res,heights[index]*(int(heights.size())-s.top()-1));
    }
    return max_res;
}
int maximalRectangle(vector<vector<char>>& matrix) {
    if(matrix.empty())return 0;
    int row=matrix.size(),col=matrix[0].size();
    vector<int>dp(col,0);
    int max_area=0;
    for(int i=0;i<row;++i)
    {
        for(int j=0;j<col;++j)
            dp[j]= matrix[i][j]=='0'?0:dp[j]+1;
        max_area=max(max_area,max_area_f(dp));   
    }
    return max_area;
}
};
```

***###思路***

这个方法的基于这样一个原理，某一个元素不断向上方遍历，直到遇到“0”，以此找到其能组成的矩形的最大高度**h**，然后向左右两边扩展，扩展过程中形成的矩形要满足高度为**h**，最大面积矩形肯定是这样组成的。

因为假如有一个最大矩形，它的高为**h**，左边界 **l**，右边界 **r**，那么在矩形的最下面这一行的区间[l, r]中必然存在一点，包括它自己在内以及它上方的1的个数为h个，也就是我们说的高为h，这一个点就是我们上一段话中要找出的那个元素。利用反证法，假设不存在这样的点，那么肯定矩形的底部这一行[l, r]范围内所有的元素的高度均大于h，那肯定是可以通过延伸高度来生成更大的矩形，因此该矩形不是最大矩形，所以可以证明第一段说的那个元素存在。

因此，对于每个点，只需要计算出它的h，在能保证h的情况下左右能扩展的最远距离，然后再算面积并不断更新最大面积就可以了。在这个遍历过程中，我个人觉得最难理解的地方就是如何更新right、left，下面就说如何更新height、left、right。

- 对于height，它的更新只需要判断matrix[i][j]是否为1，如果为1，那么height的值为matrix[i-1][j]的height加1即可，如不为1，height为零。
- 对于left，如果matrix[i][j]为1，那么left的值为matrix[i-1][j]的left值与cur_left中的最大值，其中cur_left为此行中的上一个0的序号加一，代表左边不可能扩展过此列；如果matrix[i][j]为0，那么它的left为0，这是因为当matrix[i][j]为0时，height为0，所以left的值取多少，计算出的面积都是0，但它必须小于等于0，不然会影响它的下一个元素的left的取值，因为某元素的的上一行的对应元素的left过大，就表明它限制了左延的边界，但其实当其为0时，其并不能够限制左延的边界，再将cur_left设为j+1，代表遇到0了。
- 对于right，如果matrix[i][j]为1，那么right的值为matrix[i-1][j]的right值与cur_right中的最小值，其中cur_right为此行中的后面的第一个0的序号减一，代表右边不可能扩展过此列；如果matrix[i][j]为0，那么它的right为n-1，这是因为当matrix[i][j]为0时，height为0，所以right的值取多少，计算出的面积都是0，但它必须大于等于matrix的列数，不然会影响它的下一个元素的right的取值，将cur_left设为j-1，代表遇到0了。

最后计算面积为 ![img](https://mmbiz.qpic.cn/mmbiz_svg/bj9JGugn6UeichWGHZwfNPgicTSP5pEQ27l7vKHSSVUoYzCibverR53eYaB8ywQcW7clG5XZFD0NhLr2GjgEE2ZwHwkdDIzkt6a/640?wx_fmt=svg&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1) ，不断更新就可以了，其实用将长宽高设置为二维矩阵，那么left和right的更新就会方便很多，不过这里使用的解法是用的一维矩阵，所以在更新left和right的时候就有些绕。

***###code***

```

class Solution {
public:
int maximalRectangle(vector<vector<char>>& matrix) {
  if(matrix.empty()) return 0;
  int row = matrix.size();
  int col = matrix[0].size();

  vector<int>left(col,0); 
  vector<int>right(col,col);
  vector<int>height(col,0);

  int maxarea = 0;
  for(int i = 0; i < row; i++) 
  {
      int cur_left = 0, cur_right = col-1;
      // update height
      for(int j = 0; j < col; ++j) {
          if(matrix[i][j] == '1') height[j]++;
          else height[j] = 0;
      }
      // update left
      for(int j=0; j<col; ++j) {
          if(matrix[i][j]=='1') left[j]=max(left[j],cur_left);
          else {left[j]=0; cur_left=j+1;}
      }
      // update right
      for(int j = col - 1; j >= 0; --j) {
          if(matrix[i][j] == '1') right[j] = min(right[j], cur_right);
          else {right[j] = col-1; cur_right = j-1;}    
      }
      // update area
      for(int j = 0; j <col; j++) {
          maxarea = max(maxarea, (right[j] - left[j]+1) * height[j]);
      }
  }
  return maxarea;
}
};
```

