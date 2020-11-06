**###题目**

给定一个数组，它的第 i 个元素是一支给定的股票在第 i 天的价格。设计一个算法来计算你所能获取的最大利润，**你最多可以完成两笔交易**。

**注意: 你不能同时参与多笔交易（你必须在再次购买前出售掉之前的股票）。**

- 输入: [3,3,5,0,0,3,1,4]
- 输出: 6
- 输入: [1,2,3,4,5]
- 输出: 4
- 输入: [7,6,4,3,1]
- 输出: 0

**###思路**

因为题目说了最多完成两笔交易，并且两笔交易不能够同时进行，所以可以这样进行分解，假设有prices数组，假设其中有一个prices[i]，它的前面有一笔交易，它的后面有一笔交易，prices[i]可能包含在两笔交易中其中一笔。下面的两种情况就是讨论这个假设合理性的：

- 只有一笔交易，但是可以假设成两次交易，在一天之内先卖出再买入，这一天就是prices[i]这一天。
- 两笔交易，那肯定是可以分开的。

那么只需要找出prices中每个价格前面的序列中能够得到的最大利润，以及后面的序列能够得到的最大利润，将两者相加，就是此价格作为中点能得到的最大利润。再找出所有的最大利润中最大的那个就是结果了,所以分两步进行：

- 首先从前往后计算更新数组money，money[i]代表prices[0]到prices[i]能够得到的最大利润。
- 然后再从prices.back()往前更新，每次得到从prices.back()到当前位置**i**能够得到的最大利润，再用这个最大利润加上money[i]更新最后输出的结果res。

**###code**

```cpp
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        if(prices.size()<=1)return 0;
        int temp=prices[0];
        vector<int>money;
        money.push_back(0);
        for(int i=1;i<prices.size()-1;++i)//第一笔交易
        {
            money.push_back(max(money[i-1],prices[i]-temp));
            temp=min(temp,prices[i]);//从前往后，所以找最小。
        }
        temp=prices.back();
        int res=money.back();
        //第二笔交易
        for(int i=prices.size()-2;i>=0;--i)//等于0是为了计算当prices只有两个元素的情况。
        {
            res=max(res,temp-prices[i]+money[i]);
            temp=max(temp,prices[i]);//从后往前，所以找最大。
        }
        return res;
    }
};
```