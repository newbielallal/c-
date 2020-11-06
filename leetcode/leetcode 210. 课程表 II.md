**###题目**

现在你总共有 n 门课需要选，记为 0 到 n-1。

在选修某些课程之前需要一些先修课程。 例如，想要学习课程 0 ，你需要先完成课程 1 ，我们用一个匹配来表示他们: [0,1]

给定课程总量以及它们的先决条件，返回你为了学完所有课程所安排的学习顺序。

可能会有多个正确的顺序，你只要返回一种就可以了。如果不可能完成所有课程，返回一个空数组。

- 输入: 2, [[1,0]]
- 输出: [0,1]
- 解释: 总共有 2 门课程。要学习课程 1，你需要先完成课程 0。因此，正确的课程顺序为 [0,1]
- 输入: 4, [[1,0],[2,0],[3,1],[3,2]]
- 输出: [0,1,2,3] or [0,2,1,3]

**###思路**

先用的第207. 课程表题的解法来判断是否可以成功学习所有课程。

**如果不可以**，返回空数组。

**如果可以**，设置一个flag数组，代表学过了哪些课程，然后检查邻接表，如果一个课程此时能被学习，那么将flag中对应的位置置为1，如果不行，继续看下一个课程能否被学习。不断访问这个邻接表判断课程能否被学习，直到所有的课程都被学习为止。

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
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites, 
                    vector<vector<int>>&adjacency) {
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
    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
        vector<vector<int>>adjacency(numCourses);
        if(canFinish(numCourses, prerequisites, adjacency) == false)
            return {};
        flag = vector<int>(numCourses, 0);
        vector<int>res;

        while(res.size() < numCourses)//判断是否所有课程都被学习了
        {
            for (int i = 0 ; i<adjacency.size() && res.size() < numCourses;++i)
            {
                bool flag_ = true;
                if(flag[i] == 1)
                {
                    continue;
                }
                if(adjacency[i].size() == 0 && flag[i] != 1)
                {
                    flag[i] = 1;
                    res.push_back(i);
                    continue;
                }
                for(int j = 0; j < adjacency[i].size(); ++j)
                {
                    if(flag[adjacency[i][j]] == 0)
                    {
                        flag_ = false;
                        break;
                    }
                }
                if(flag_)
                {
                    flag[i] = 1;
                    res.push_back(i);
                }
            }
        }
        return res;        
    }
};
```