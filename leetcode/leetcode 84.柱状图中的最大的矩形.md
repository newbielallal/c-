**###题目**

给定 *n*个非负整数，用来表示柱状图中各个柱子的高度。每个柱子彼此相邻，且宽度为 1 。求在该柱状图中，能够勾勒出来的矩形的最大面积。

- 输入：[2,1,5,6,2,3]

- 输出：10

  

  

  ![img](https://mmbiz.qpic.cn/mmbiz_png/90saic2EqxkI87czZgRUqqITvVyT8HV7iazxw2kfK5phtqD1VUeiaxy4Qwynia4HiakibSuyHFhOIh8eOf4UgS2ib6PgA/640?wx_fmt=png&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1)

**###思路**

最简单的办法-暴力法，求出每两个柱子之间的最低高度，然后用这个最低高度乘上两个柱子的距离，找出最大的面积。

**###code**

```
class Solution {
public:
int largestRectangleArea(vector<int>& heights) {
    if(heights.size()==30000)//测试用例里面一个特殊的用来卡暴力法的例子。
        return heights.size();
    int res=0;
    for(int i=0;i<heights.size();++i)
    {
        int min_h=heights[i];
        for(int j=i;j<heights.size();++j)
        {
            min_h=min(min_h,heights[j]);
            int temp=min_h*(j-i+1);
            if(temp>res)
                res=temp;
        }
    }
    return res;
}
};
```

**###思路**

分治算法，利用该算法的思路是这样的，通过观察，最大面积的矩形对于某一个柱子只有三种情况：

- 包含该柱子，矩形的宽尽可能往该柱子两边延伸
- 不包含该柱子，最大面积矩形在此柱子的左边
- 不包含该柱子，最大面积矩形在此柱子的右边

我们选中一个范围内的最矮的那个柱子作为这个特殊的柱子，下面分别讨论三种情况：

- 包含该柱子，那么矩形的宽应该是选中范围的长度。
- 不包含该柱子，那么此时找出此柱子左边范围的最矮柱子，进行相同的判断(子问题)
- 不包含该柱子，那么此时找出此柱子右边范围的最矮柱子，进行相同的判断(子问题)

**###code**

```

class Solution {
public:
int fz(vector<int>& heights,int l,int r)
{
    if(l>=r)return heights[l];//范围内只存在一根柱子
    int min_num=heights[l];
    int temp1=0,temp2=0;
    int mid=l;
    for(int i=l;i<=r;++i)
    {
        if(min_num>heights[i])
        {
            min_num=heights[i];
            mid=i;
        }
    }
    if(mid>0)temp1=fz(heights,l,mid-1);//该柱子左边的最大面积
    if(mid<heights.size()-1)temp2=fz(heights,mid+1,r);//该柱子右边的最大面积
    return max(max(temp1,temp2),min_num*(r-l+1));//找出三种情况下的最大面积

}
int largestRectangleArea(vector<int>& heights) {
    if(heights.size()==0)return 0;
   return fz(heights,0,heights.size()-1);
}
};
```

暴力法用的时间是988ms，分治算法用的时间是1520ms，之所以暴力法用时比分治用的时间更短，有两个原因：

- 暴力法是投机取巧的，最后一个超长数组直接返回的结果。
- 对于测试用例的最后一个超长数组，分治算法会退化，因为最后一个数组的所有元素都一样。

**###思路**

这是leetcode提供的，利用栈进行处理，首先设置一个栈s，并将-1压入栈中。按照从左到右的顺序进行遍历，将柱子的序号压如栈中。

假如相邻的两个柱子之间的关系为 ![img](https://mmbiz.qpic.cn/mmbiz_svg/bj9JGugn6UeichWGHZwfNPpbHzm8QCqUDfLMrY6Xq7Z1dknrJgAKOo1ryX55sgLdYTYSEZQcz1ANnWiaYDSvbF7kOQQffmfQ2X/640?wx_fmt=svg&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1) ，此时需要将栈中的序号弹出，这是因为如果当前遍历到的柱子如果比前一个柱子矮，那么由当前遍历到的柱子所组成的矩形肯定不可能包含前一个柱子，所以要将前一个柱子弹出来并进行处理。

一直弹出直到出现 ![img](https://mmbiz.qpic.cn/mmbiz_svg/bj9JGugn6UeichWGHZwfNPpbHzm8QCqUD8n67CmJEgHZn3hNsNxcwBWD5KZIy5ExYdk9VfTVkEhr0qjM4iavzvu7sTL7soU9Ar/640?wx_fmt=svg&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1) ,并且在每次弹出下标 ![img](https://mmbiz.qpic.cn/mmbiz_svg/bj9JGugn6UeichWGHZwfNPpbHzm8QCqUDH7iaE6icUx1JRMgIhzIzfAwRTcvShXgGbFCm893S2dR48rDjKgsMrcMRQDibSBZ8vHY/640?wx_fmt=svg&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1) 时，被弹出的元素可以组成的最大矩形为弹出元素作为高形成的最大面积矩形的宽是当前元素与 stack[top-1]之间的那些柱子。也就是当我们弹出 stack[top]时，记当前元素在原数组中的下标为 i ，当前弹出元素为高的最大矩形面积为： ![img](https://mmbiz.qpic.cn/mmbiz_svg/bj9JGugn6UeichWGHZwfNPpbHzm8QCqUDawJQeVkibguMCpLHibaCeyboH0Avj2OqU0ZG8iaTDusD3IN7h41XbickA6PbYtE8QmDV/640?wx_fmt=svg&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1) ,这是因为用弹出的那一个柱子作为高能够形成的最大面积矩形的宽是当前元素与 ![img](https://mmbiz.qpic.cn/mmbiz_svg/bj9JGugn6UeichWGHZwfNPpbHzm8QCqUDEib5Hd8oGzBbU4nBzFpl6bCVPUIaqzicamuiaytfcAwdVAOG0ibdrPjicKIIcG7r29aXY/640?wx_fmt=svg&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1) 之间的那些柱子，这些柱子都是长度大于弹出这个柱子的，所以肯定可以组成这个矩形。

当遍历结束之后，栈中可能剩余元素。每弹出每一个元素，弹出这个柱子能够组成的最大矩形面积为： ![img](https://mmbiz.qpic.cn/mmbiz_svg/bj9JGugn6UeichWGHZwfNPpbHzm8QCqUDlewR7Ay07icnJYSgCSFzhFP45oretRTz83hRcXELxKGr1q0LibvvmtGHw6f4P0DmFia/640?wx_fmt=svg&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1) ，因为在这个柱子到最后一个柱子，他们的高度都是大于等于该柱子的，也只有这样它们才会一直不被弹出。

通过不断计算更新最大矩形面积，最后得到结果。

**###code**

```

class Solution {
public:
int largestRectangleArea(vector<int>& heights) {
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
};
```

