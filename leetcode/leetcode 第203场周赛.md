**###题目**

给你一个整数 n 和一个整数数组 rounds 。有一条圆形赛道由 n 个扇区组成，扇区编号从 1 到 n 。现将在这条赛道上举办一场马拉松比赛，该马拉松全程由 m 个阶段组成。其中，第 i 个阶段将会从扇区 rounds[i - 1] 开始，到扇区 rounds[i] 结束。举例来说，第 1 阶段从 rounds[0] 开始，到 rounds[1] 结束。

请你以数组形式返回经过次数最多的那几个扇区，按扇区编号**升序**排列。

注意，赛道按扇区编号升序逆时针形成一个圆。

**###思路**

因为是简单难度,所以就直接考虑的暴力法了，分三步走：

1、先统计每个扇区经过了多少次

2、然后找出经过扇区次数最多的次数maxnum

3、找出哪些扇区经过了maxnum次

**###code**

```cpp
class Solution {
public:
    vector<int> mostVisited(int n, vector<int>& rounds) {
        vector<int>num(n+1, 0);   
 
        //每个扇区经过了几次
        for(int i = 0; i <size(rounds) - 1; i++)
        {
            if(rounds[i] < rounds[i+1])
            {
                for(int j=rounds[i]+1;j<=rounds[i+1];++j)
                {
                    num[j]++;
                }
            }
            else
            {
                for(int j=rounds[i]+1;j<=n;++j)
                {
                    num[j]++;
                }
                for(int j=1; j<=rounds[i+1];++j)
                {
                    num[j]++;
                }
            }
        }
        num[rounds[0]]++;
        
        //经过的最多次数maxnum
        int maxnum = num[0];
        for(auto i :num)
        {
            if(i > maxnum)maxnum=i;
        }

        //一共有哪些扇区经过了maxnum次
        vector<int>res;
        for(int i=0; i<size(num);++i)
        {
            if(num[i] == maxnum)
                res.push_back(i);
        }
        return res;
    }
};
```

**###题目**

有 3n 堆数目不一的硬币，你和你的朋友们打算按以下方式分硬币：

1. 每一轮中，你将会选出 任意 3 堆硬币（不一定连续）。
2. Alice 将会取走硬币数量最多的那一堆。
3. 你将会取走硬币数量第二多的那一堆。
4. Bob 将会取走最后一堆。
5. 重复这个过程，直到没有更多硬币。

给你一个整数数组 `piles` ，其中 `piles[i]` 是第 `i` 堆中硬币的数目。返回你可以获得的最大硬币数目。

**###思路**

因为每次都只能取第二多的那一堆，所以就直接将硬币堆排好序，然后选择第二大的、第四大的、第六大的......这样到最后累加就可以了。

**###code**

```cpp
class Solution {
public:
    int maxCoins(vector<int>& piles) {
        sort(piles.begin(),piles.end());
        int res=0;
        int l= size(piles);
        int n = l/3;
        for(int i=0;i<n;++i)
        {
            res+=piles[(l-2)-2*i];
        }
        return res;
    }
};
```

**###题目**

给你一个数组 arr ，该数组表示一个从 1 到 n 的数字排列。有一个长度为 n 的二进制字符串，该字符串上的所有位最初都设置为 0 。

在从 1 到 n 的每个步骤 i 中（假设二进制字符串和 arr 都是从 1 开始索引的情况下），二进制字符串上位于位置 arr[i] 的位将会设为 1 。

给你一个整数 m ，请你找出二进制字符串上存在长度为 m 的一组 1 的最后步骤。一组 1 是一个连续的、由 1 组成的子串，且左右两边不再有可以延伸的 1 。

返回存在**长度恰好为m的一组1的最后步骤**。如果不存在这样的步骤，请返回 -1 。

**###思路**

开始一直超时，一直优化，最后三个测试用例还是一直超时，果然还是脑子太僵化了，后来在评论区看了别人的写法，豁然开朗，时间复杂度O(n)可还是秀的。思路后面再补。。。。。

**###code**

```cpp
class Solution {
public:
    int findLatestStep(vector<int>& arr, int m) {
        vector<int>link(arr.size(),-1);
        int res =-1;
        int count = 0;

        for(int i = 0; i < arr.size(); ++i)
        {
            int pos = arr[i] - 1;
            link[pos] = pos;
            int left = pos;
            int right = pos;

            if(0 < pos && link[pos-1] != -1)
            {
                if(((pos - 1) - link[pos-1] + 1) == m)
                {
                    count--;
                }
                left = link[pos - 1];
            }
            if((arr.size() > pos + 1) && link[pos+1] != -1)
            {
                if((link[pos + 1] - (pos + 1)  + 1) == m)
                {
                    count--;
                }
                right = link[pos + 1];
            }
            link[right] = left;
            link[left] = right;
            if((right - left + 1) == m)
            {
                count++;
            }
            if(0 < count)
            {
                res = i + 1;
            }
        }
        return res;
    }
};
```

**###题目**

几块石子 排成一行 ，每块石子都有一个关联值，关联值为整数，由数组 stoneValue 给出。

游戏中的每一轮：Alice 会将这行石子分成两个 非空行（即，左侧行和右侧行）；Bob 负责计算每一行的值，即此行中所有石子的值的总和。Bob 会丢弃值最大的行，Alice 的得分为剩下那行的值（每轮累加）。如果两行的值相等，Bob 让 Alice 决定丢弃哪一行。下一轮从剩下的那一行开始。

只 剩下一块石子 时，游戏结束。Alice 的分数最初为 0 。

返回 Alice 能够获得的最大分数

**###思路**

dp[i][j]代表以i开始以j结束的stoneValue Alice所能拿到的最大值。len的长度从2增加到len(stonevalue)-1，因为只有两个数时的情况已经计算过了，所以直接让len的长度从2开始。动态规划就是解决这类问题的神器，一个大概的思路是这样的。

当有两个值的时候，Alice能够取得的最大值是两个值中的小的那个。

当有三个值的时候，Alice能够取得的值有两种组成 12 3、1 23，由于上一步计算出了所有的两个值时候alice能够取得的最大值，所以直接就可以直接对比了找出哪个结果最大。

当有三个值的时候，第一次划分可能的组合有 1 234 、12 34、123 4，所有的三个值得，两个值的最大取值情况已经计算过了，直接对比出每一步哪种分发可以得到最大值。

这样一直计算直到有len(stonevalue)个值的时候就可以了。

具体思路后面再补。。。。。

**###code**

```cpp
class Solution {
public:
    int dp[500][500];
    int acc[501]; //累加和
int stoneGameV(vector<int>& stoneValue) {
    int size = stoneValue.size();
    //当只有两个数时，只能获得最小数的金币
    for(int i = 1; i < size; i++){
        dp[i-1][i] = min(stoneValue[i-1], stoneValue[i]);
    }
    //累加求和
    acc[1] = stoneValue[0];
    for(int i = 2; i <= size; i++)
    {
        acc[i] = acc[i-1] + stoneValue[i-1];
    }
    for(int len = 2; len < size; len ++){
        for(int i = 0; i < size - len; i++){
            int j = i+len;
            for(int k = i; k < j; k++){
                int left = acc[k+1]-acc[i];
                int right = acc[j+1] - acc[k+1];
                //左则区间和大，选右边；反之亦反；若两者相等，max(left + dp[i][k], right + dp[k+1][j])
                if(left > right) dp[i][j] = max(dp[i][j], right + dp[k+1][j]);
                else if(left < right) dp[i][j] = max(dp[i][j],left + dp[i][k]);
                else{
                    dp[i][j] = max(dp[i][j], max(left + dp[i][k], right + dp[k+1][j]));
                }
            }
        }
    }
    return dp[0][size-1];
}
};
```