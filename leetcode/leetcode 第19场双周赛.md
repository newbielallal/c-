\#题目

给你一个非负整数 `num` ，请你返回将它变成 0 所需要的步数。 如果当前数字是偶数，你需要把它除以 2 ；否则，减去 1 。

\#思路

当前num是偶数就将其除以2，如果是奇数就将其减去1.

\#code

```cpp
class Solution {
public:
    int numberOfSteps (int num) {
        int res=0;
        while(num>0)
        {
            if(num%2==0)num=num>>1;
            else num=num-1;
            res++;
        }
        return res;
    }
};
```

\#题目

给你一个整数数组 `arr` 和两个整数 `k` 和 `threshold` 。

请你返回长度为 `k` 且平均值大于等于 `threshold` 的子数组数目。

\#思路

刚开始写的时候没注意，子数组是需要连续的，题目难度一下子就降低了好多。设置一个长度为k的滑动窗口，然后在数组arr中往右移动此滑动窗，计算窗口内的平均值，满足条件就输出结果res加一，直到右移到数组末尾，输出res.

\#code

```cpp
class Solution {
public:
    int numOfSubarrays(vector<int>& arr, int k, int threshold) {
        long long sum=0;
        int res=0;
        for(int i=0;i<k;++i)//题目说了k肯定合理，所以直接用。
        {
            sum=sum+arr[i];
        }
        if(sum/k>=threshold)
            res++;
        int left=0;
        int right=k-1;
        while(right<arr.size()-1)
        {    right++;
            sum=sum+arr[right]-arr[left];
            left++;
             if(sum/k>=threshold)
                res++;
        }
        return res;
    }
};
```

\#题目

给你两个数 `hour` 和 `minutes` 。请你返回在时钟上，由给定时间的时针和分针组成的较小角的角度（60 单位制）。

示例 1：

![img](https://pic4.zhimg.com/80/v2-b5646a9e9bb178e12c92d423de91d12b_720w.jpg)

输入：hour = 12, minutes = 30
输出：165

\#思路

之前刷面经的时候做过这个题目，原理是这样的，假设小时的值是h，分钟的值是m，以12点为0度.

处理时针，时针往前走一个小时的度数是30度(360/12=30),所以整点的时候时针对于12点的度数是30*h,

处理分针，分针60的时候是整个一圈，所以分针对于12点为0度的角度是6*m(360/60=6)。

因为分针不为0的时候，时针的度数由两个部分组成：1、30 X h 2、分针不为0的部分映射到时针上，(m/60)X30=0.5 X m(两个星号在一起会自动加粗，所以把星号写成X了，代表乘法)。

所以两者的角度为:30 X h+0.5 X m-6 X m=30 X h-5.5 X m。

题目要求输出更小角，所以输出将结果取绝对值，然后求出补角，选其中更小的那个。

\#code

```cpp
class Solution {
public:
    double angleClock(int hour, int minutes) {
        double res =(30*double(hour)-5.5*double(minutes));
        if(abs(res)<(360-abs(res)))
            return abs(res);
        return 360-abs(res);
    }
};
```

\#题目

给你一个整数数组 arr ，你一开始在数组的第一个元素处（下标为 0）。

每一步，你可以从下标 i 跳到下标：

i + 1 满足：i + 1 < arr.length

i - 1 满足：i - 1 >= 0

j 满足：arr[i] == arr[j] 且 i != j

请你返回到达数组最后一个元素的下标处所需的 最少操作次数 。

注意：任何时候你都不能跳到数组外面。

\#思路

这题目卡了我好久，开始用暴力法和dp都超时了，最后用的bfs，步骤如下：

1、将数组优化，例如 177711177711 优化成177117711，就是将连续的相同的数字删除掉其中的重复项，但是至少要保留两位。

2、集合相同值的下标。

3、利用bfs算法找出最短路径(之前写过bfs的博客，哪天整理一下重新发下)。

具体的就看代码吧。

\#code

```cpp
class Solution {
public:
int minJumps(vector<int>& arr) {
    if(arr.size()<=1)return 0;
    vector<int>temp;
    for (int i = 0, j=0; i < arr.size(); i=j)//优化数组
    {
        temp.push_back(arr[i]);
        for (j = i+1; j< arr.size() && arr[i] == arr[j]; j++);
        if (j-i> 1)
            temp.push_back(arr[i]);
    }
    unordered_map<int,vector<int>>m;
    for(int i=0;i<temp.size();++i)//集合相同值的下标
    {
        m[temp[i]].push_back(i);
    }
    queue<int>bfs;
    bfs.push(0);
    vector<int>dp(temp.size(),arr.size());
    dp[0]=0;
    for(int i=0;!bfs.empty();++i)//bfs遍历
    {
        for(int j=bfs.size();j>0;--j)
        { 
            int index=bfs.front();
            bfs.pop();

            if(index==temp.size()-1)return dp.back();
            if((index+1<temp.size())&&(dp[index]+1<dp[index+1]))
            {

                bfs.push(index+1);
                dp[index+1]=dp[index]+1;
            }
             if(index-1>=0&&dp[index]+1<dp[index-1])
            {
                bfs.push(index-1);
                dp[index-1]=dp[index]+1;
            }
            for(auto& a:m[temp[index]])
            {
                if(dp[a]>dp[index]+1)
                {
                    bfs.push(a);
                    dp[a]=dp[index]+1;
                }
            }
        }

    }
    return 0;
}
};
```