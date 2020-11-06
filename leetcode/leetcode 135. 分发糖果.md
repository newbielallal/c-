**###题目**

老师想给孩子们分发糖果，有 N 个孩子站成了一条直线，老师会根据每个孩子的表现，预先给他们评分。

你需要按照以下要求，帮助老师给这些孩子分发糖果：

- 每个孩子至少分配到 1 个糖果。
- 相邻的孩子中，评分高的孩子必须获得更多的糖果。

那么这样下来，老师至少需要准备多少颗糖果呢？

**###思路**

题目要求每个孩子必须至少分配到1颗糖果，所以首先设置一个与ratings数组等长的数组temp用于记录分给孩子们的糖果。

- 因为每个孩子至少分配一颗糖果，所以将temp的初始值都设置为1。
- 然后从前往后遍历整个ratings数组，若 ![[公式]](https://www.zhihu.com/equation?tex=ratings%5Bi%5D%3Eratings%5Bi-1%5D) ，那么相应的 ![[公式]](https://www.zhihu.com/equation?tex=temp%5Bi%5D%3Dtemp%5Bi-1%5D%2B1) 。
- 因为题目要求是相邻孩子中评分高的必须获得更多的糖果，如果只是从前往后遍历，那么在对形如 2 1 2这样的数组最后的输出结果就是 1 1 2，是错误的。
- 再加上一个从后往前遍历的过程，此过程中，如果 ![[公式]](https://www.zhihu.com/equation?tex=ratings%5Bi-1%5D%3Eratings%5Bi%5D+) 且 ![[公式]](https://www.zhihu.com/equation?tex=temp%5Bi-1%5D%3Ctemp%5Bi%5D%2B1) 。那么我们就将temp[i-1]的值设置为temp[i]+1。这样做的原因的每个小朋友分得到糖果的数目只与他的左右朋友有关，所以temp[i-1]的值的变化并不会影响到temp[i+1]以及它之后的分配糖果数目的正确性。

最后输出整个temp数组的和就可以了。

**###code**

```cpp
class Solution {
public:
    int candy(vector<int>& ratings) {
        int l=ratings.size();
        vector<int> temp(l,1);
        for(int i=1;i<l;i++)//从前往后
            if(ratings[i]>ratings[i-1]) 
                temp[i]=temp[i-1]+1;
        for(int i=l-1;i>0;i--)//从后往前
            if(ratings[i-1]>ratings[i] && temp[i-1]<temp[i]+1)
                temp[i-1]=temp[i]+1;
        return accumulate(temp.begin(),temp.end(),0);//输出temp的和。
    }
};
```