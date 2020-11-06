**###题目**

给出一个无重叠的 ，按照区间起始端点排序的区间列表。

在列表中插入一个新的区间，你需要确保列表中的区间仍然有序且不重叠（如果有必要的话，可以合并区间）。

输入: intervals = [[1,3],[6,9]], newInterval = [2,5]

输出: [[1,5],[6,9]]

**###思路**

有点取巧了，把newInterval插入进intervals，就和56题的解法一样了。

**###代码**

```cpp
class Solution {
public:
static bool f(vector<int>&a,vector<int>&b)
{
    return a[0]<b[0];
}
vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval) {
    intervals.push_back(newInterval);
     if(intervals.size()<=1)
        return intervals;
    sort(intervals.begin(),intervals.end(),f);
    vector<vector<int>> res;
    vector<int>temp;
    temp.push_back(intervals[0][0]);
    int num=intervals[0][1];
    int index=1;
    while(index<intervals.size())
    {
        if(intervals[index][1]>num)
       {
            if(intervals[index][0]<=num)
                num=intervals[index][1];
            else
            {
                temp.push_back(num);
                res.push_back(temp);
                temp.clear();
                temp.push_back(intervals[index][0]);
                num=intervals[index][1]; 
            }
        }
        index++;
    }
    temp.push_back(num);
    res.push_back(temp);
    return res;
}
};
```

\###思路

对第一种方法进行改进，上一种方法未利用上intervals其实已经是一个符合规则的vector集合，所以这一种方法中需要我们利用上这一条件，步骤如下：

- 将intervals[i][0]<newInterval[0]的vector全部添加进res中。
- 然后判断newInterval是否可以和上一步添加的最后一个vector合并。
- 最后将intervals中剩下的vector挨个和res中的最后一个vector合并。

\###代码

```cpp
class Solution {
public:
vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval) {
    int begin=newInterval[0],end=newInterval[1];
    vector<vector<int>>res;
    if(intervals.size()<=0)
    {
         res.push_back(newInterval);
         return res;
    }
    int i=0;
    for(;i<intervals.size();++i)//步骤一
    {
        if(intervals[i][0]<begin)res.push_back(intervals[i]);
        else
        break;
    }
    if(res.size()==0)//步骤二
        res.push_back(newInterval);
    else
    {
        if(res.back().back()<begin)
        {
            res.push_back(newInterval);
            res.back().back()=end;
        }
        else if(res.back().back()>=end)
            return intervals;
        else
            res.back().back()=end;
    }
    for(;i<intervals.size();++i)//步骤三
    {
        if(intervals[i][1]<=end)
            {
               continue;
            }
        else
        {
            if(intervals[i][0]>end)
                res.push_back(intervals[i]);
            else
                {
                    end=intervals[i][1];
                    res.back().back()=end;
                }
        }
    }
    return res;
}
};
```