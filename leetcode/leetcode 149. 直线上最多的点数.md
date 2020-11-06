**###题目**

给定一个二维平面，平面上有 *n* 个点，求最多有多少个点在同一条直线上。

- **输入:** [[1,1],[3,2],[5,3],[4,1],[2,3],[1,4]]
- **输出:** 4

**###思路**

暴力法混混得了。得出二维平面上的点能够组成的所有直线，再找出哪条直线上的点最多即可，步骤如下：

1. 两个不同的点可以确定一条直线，所以先找出二维平面points中的两个不同的点确定一条直线。
2. 遍历points中的点是否在选出的直线上，判断规则很简单，如果三个点能够组成一条直线，那么一定有 ![[公式]](https://www.zhihu.com/equation?tex=%28x2-x1%29%5Cdiv%28y2-y1%29%3D%28x1-x3%29%5Cdiv%28y1-y3%29) 。根据这个规则判断判断三个点是否在一条直线上，找出所有在这条直线上的点。
3. 输出点数最多的直线。

一些处理上的细节可以看注释。

**###code**

```cpp
class Solution {
public:
int maxPoints(vector<vector<int>>& points) {
    vector<int>res;
    if(points.size()<=2)return points.size();//点数小于等于2不用判断。
    for(int i=0;i<points.size()-1;++i)
    {
        int temp1=points[i][0];//找出第一个点
        int temp2=points[i][1];

         for(int j=i+1;j<points.size();++j)
         {
             int temp3=points[j][0];
             int temp4=points[j][1];

             if(temp1==temp3&&temp4==temp2)continue;//找出不同的点作为第二个点。如果相同的点会计算错误。
             int num=0;
             for(int k=0;k<points.size();++k)
             {
                 //判断是否在一条直线上。
                 if(judge_line(temp1,temp2,temp3,temp4,points[k][0],points[k][1]))
                 {
                     num++;
                 }
             }
             res.push_back(num);
         }
    }
    if(res.size()==0)return points.size();//特殊情况，所有的点都是同一个点，直接输出点数。
    int max_res=res[0];
    for(auto i:res)//找最大。
    {
        if(i>max_res)max_res=i;
    }
    return max_res;
}
bool judge_line(int x1,int y1,int x2,int y2,int x3,int y3)
{
    if(x1==x3&&y1==y3)return true;//与确定直线的两个点中的任意一个点相同
    if(x2==x3&&y2==y3)return true;//肯定在一条直线上。
    return (long(x1-x2))*(y2-y3)==(long(x2-x3))*(y1-y2);//会溢出，所以用long型。
    //因为可能差会有0，所以就用了乘法。
}
};
```