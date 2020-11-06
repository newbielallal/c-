**###题目**

你这个学期必须选修 numCourse 门课程，记为 0 到 numCourse-1 。

在选修某些课程之前需要一些先修课程。 例如，想要学习课程 0 ，你需要先完成课程 1 ，我们用一个匹配来表示他们：[0,1]

给定课程总量以及它们的先决条件，请你判断是否可能完成所有课程的学习？

**###思路**

先建立好邻接表。使用深度优先遍历，确定每门课程的每个前置课程都不存在环，若存在环，那么必定是不可能的。

具体可以看注释，注释写得比较详细。

**###code**

```cpp
class Solution {
public:
    vector<int>flag;//代表某个课程能否成功完成学习。1：不能，-1：能，0：暂时不清楚
    bool dfs(int num, vector<vector<int>>& adjacency)//判断某课程能够被学习。
    {
        if (adjacency[num].size() == 0)//没有前置课程，能够被学习
            return true;
        if(flag[num] == 1)return false;//通过flag直接返回是否能够被学习。
        if(flag[num] == -1)return true;
        bool res = true;

        flag[num] = 1;//要先将这一位设置为1，这样如果遇到环就会直接返回false，否则就死循环了
        for(int j = 0; j < adjacency[num].size(); ++j)
        {
            res = dfs(adjacency[num][j],adjacency);
            if(!res)
            {
                return res;//不能学习，返回false，flag对应位是1.
            }
        }

        flag[num] = -1;//能够学习，重置为-1，返回true
        return res;
    } 
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        vector<vector<int>>adjacency(numCourses);
        flag = vector<int>(numCourses, 0);

        for(int i = 0; i < prerequisites.size(); ++i)//记录每个课程的前置课程
        {
            adjacency[prerequisites[i][0]].push_back(prerequisites[i][1]);
        }

        for(int i = 0; i < numCourses;++i)//判断每个课程能否被学习
        {
            for(int j = 0; j < adjacency[i].size(); ++j)//判断每个课程的每个前置课程能否被学习。
            {
                bool res = dfs(adjacency[i][j],adjacency);
                if(!res)
                {
                    return res;
                }
            }
        }
        return true;
    }
};
```