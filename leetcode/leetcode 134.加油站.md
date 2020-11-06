**###题目**

在一条环路上有 N 个加油站，其中第 i 个加油站有汽油 gas[i] 升。

你有一辆油箱容量无限的的汽车，从第 i 个加油站开往第 i+1 个加油站需要消耗汽油 cost[i] 升。你从其中的一个加油站出发，开始时油箱为空。

如果你可以绕环路行驶一周，则返回出发时加油站的编号，否则返回 -1。

说明:

- 如果题目有解，该答案即为唯一答案。
- 输入数组均为非空数组，且长度相同。
- 输入数组中的元素均为非负数。

**###思路**

思路比较简单，类似于暴力法了，时间复杂度为 ![[公式]](https://www.zhihu.com/equation?tex=O%28N%5E2%29) 。

- 判断输入的cost和gas是否合理？
- 计算cost和gas的和，如果前者的和小于等于后者，那么肯定是有一个可以作为起点的加油站的。
- 利用双指针遍历每个加油站，首先start指向目前作为起点的加油站，然后cur往前走，看是否能够回到start，如果不行，那么更改start=start++，cur=start+1，最后找出其中可以作为起点的加油站，返回结果，注意细节上的处理就可以了。

**###code**

```cpp
class Solution {
public:
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
        //看输入数据是否合理
        if(gas.size()==0||gas.size()!=cost.size())return -1;
        //计算消耗的油和能提供的油
        int temp1 = accumulate(gas.begin(), gas.end(), 0);
        int temp2 = accumulate(cost.begin(), cost.end(), 0);
        //若消耗的小于或等于提供的，那么一定有一个起点可以，否则输出-1
        if (temp1 < temp2) return -1;
        int l= gas.size();
        if (l == 1) return 0;
        int start = 0;
        int cur = 1;
        int oil = gas[0] - cost[0];
        //因为已经证明了肯定有一个加油站可以作为起点
        //依次遍历每个加油站，找到满足条件的那个。
        while (cur != start&&start<l) {
            if (oil >=0) {
                oil += gas[cur] - cost[cur];
                cur = (cur + 1) % l;
            } else {
                start++;
                cur=start+1;
                cur=cur%l;
                oil= gas[start] - cost[start];
            }
        }
        return start;
    }
};
```