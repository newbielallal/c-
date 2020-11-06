**###第一题**

给你一个整数数组 arr ，以及 a、b 、c 三个整数。请你统计其中好三元组的数量。如果三元组 (arr[i], arr[j], arr[k]) 满足下列全部条件，则认为它是一个 好三元组 。

- 0 <= i < j < k < arr.length
- |arr[i] - arr[j]| <= a
- |arr[j] - arr[k]| <= b
- |arr[i] - arr[k]| <= c
- 其中 |x| 表示 x 的绝对值。

返回好三元组的数量 。

**###思路**

因为是简单，所以就直接暴力法三重循环做的，没啥好说的。

**###code**

```text
class Solution {
public:
    int countGoodTriplets(vector<int>& arr, int a, int b, int c) {
        int count=0;
        
        for(int i=0;i<arr.size();++i)
        {
            for(int j=i+1;j<arr.size();++j)
            {
                for(int k=j+1;k<arr.size();++k)
                {
                    if(((abs(arr[i]-arr[j]))<=a)&&((abs(arr[j]-arr[k]))<=b)&&((abs(arr[i]-arr[k]))<=c)) count++;
                }
            }
        }
        return count;
    }
};
```

**###第二题**

给你一个由不同整数组成的整数数组 arr 和一个整数 k 。每回合游戏都在数组的前两个元素**(即 arr[0] 和 arr[1])**之间进行。比较arr[0]与arr[1]的大小，较大的整数将会取得这一回合的胜利并保留在位置 0 ,较小的整数移至数组的末尾。当一个整数赢得k个连续回合时，游戏结束，该整数就是比赛的赢家 。返回赢得比赛的整数。

- **输入：**arr = [2,1,3,5,4,6,7], k = 2
- **输出：**5

**###思路**

纯粹按照题目意思来写的代码，然后调整数组。比较low。

**###code**

```cpp
class Solution {
public:
    int getWinner(vector<int>& arr, int k) {
        int turn=0;
        int change=0;
        int l=arr.size();
        
        if(l<=2)
            return *max_element(arr.begin(),arr.end());
        if(k>=l)
        {
            return *max_element(arr.begin(),arr.end());
        }
        while(turn<k)
        {
            if(arr[0]>arr[1+change])
            {
                turn++;
                change++;
            }
            else
            {
                vector<int>temp(l,0);
                temp[l-1]=arr[0];
                for(int i=0;change+1+i<l;++i)
                    temp[i]=arr[change+1+i];
                for(int i=1;i<=change;++i)
                    temp[l-change]=arr[change];
                temp[l-1]=arr[0];
                change=0;turn=1;
                for(int i=0;i<l;++i)
                    arr[i]=temp[i];
            }
        }
        return arr[0];
    }
};
```

**###第三题**

给你一个 n x n 的二进制网格 grid，每一次操作中，你可以选择网格的 相邻两行 进行交换。

一个符合要求的网格需要满足主对角线以上的格子全部都是 0 。

请你返回使网格满足要求的最少操作次数，如果无法使网格符合要求，请你返回 -1 。

主对角线指的是从 (1, 1) 到 (n, n) 的这些格子。

**###思路**

做题的时候傻逼了，没看清人家说的一行一行的交换。如果只能一行一行的交换，那代表每一行末尾的连续的0的个数是没有办法改变的，那么首先得到每一行数组的末尾连续0的个数，然后开始从上到下遍历，如果这行的末尾0满足条件，那么向下一行继续查看，如果不满足，那么从下面找最近的能够满足条件的一行通过依次交换的方法交换上来(类似于冒泡排序)，并记录交换次数，如果没有满足条件的一行，直接输出-1。

**###code**

```cpp
class Solution {
public:
    int minSwaps(vector<vector<int>>& grid) {
         int n=grid.size();
        int res=0;
        vector<int>count(n,0);

        for(int i=0;i<n;++i)
        {
            int count_0=0;
            for(int j=n-1;j>=0;--j)
            {
                if(grid[i][j]==0)count_0++;
                else break;
            }
            count[i]=count_0;
        }

        for(int i=0;i<n;++i)
        {
            if(count[i]>=n-i-1)continue;
            else
            {
                int j=i;
                for(;j<n;++j)
                {
                    if(count[j]>=n-i-1)break;
                }
                if(j==n)return -1;
                for(int k=j;k>i;--k)
                {
                    swap(count[k],count[k-1]);
                    res++;
                }
            }
        }
        return res;
    }
};
```

**###第四题**

你有两个有序且数组内元素互不相同的数组nums1和nums2。一条合法路径 定义如下：选择数组 nums1 或者 nums2 开始遍历（从下标 0 处开始）。从左到右遍历当前数组。如果你遇到了 nums1 和 nums2 中都存在的值，那么你可以切换路径到另一个数组对应数字处继续遍历（但在合法路径中重复数字只会被统计一次）。得分定义为合法路径中不同数字的和。请你返回所有可能合法路径中的最大得分。由于答案可能很大，请你将它对 10^9 + 7 取余后返回。

**###思路**

时间不够没做出来，后来看别人说这类似于两个有序数组的合并，我觉得说得很有道理。。。就是将两个有序数组按照两个数组中的共同元素为结点将数组分段，然后由两个共有的元素所组成的两段路径中取路径和较大值作为最后的路径的组成部分，代码是从评论区找的别人的代码。

**###code**

```cpp
class Solution {
public:
    int maxSum(vector<int>& nums1, vector<int>& nums2) {
         int m= nums1.size(),n= nums2.size();
        int i = 0, j = 0;
        long long sum1 = 0, sum2 = 0; // 中间得分
        while (i < m && j < n) {
            // 在双数组中选择较小元素, 右移指针
            if (nums1[i] < nums2[j]) {
                while (i < m && nums1[i] < nums2[j]) sum1 += nums1[i++];
            }
            else if (nums1[i] > nums2[j]) {
                while (j < n && nums1[i] > nums2[j]) sum2 += nums2[j++];
            }
            // 此时双指针位置元素相同, 替换较小得分 (高分也可以跳转到另一数组继续取分)
            else {
                sum1 = sum2 = max(sum1, sum2) + nums1[i];
                i++; j++;
            }
        }
        while (i < m) sum1 += nums1[i++];
        while (j < n) sum2 += nums2[j++];

        return (max(sum1, sum2) % 1000000007);
    }
};
```