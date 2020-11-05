---
title: leetcode 1046 最后一块石头的重量
tags:
  - c++ 
categories: c++ 
---
————————分隔符——————
<!-- more -->

### 题目
有一堆石头，每块石头的重量都是正整数。

每一回合，从中选出两块最重的石头，然后将它们一起粉碎。假设石头的重量分别为 x 和 y，且 x <= y。那么粉碎的可能结果如下：

如果 x == y，那么两块石头都会被完全粉碎；
如果 x != y，那么重量为 x 的石头将会完全粉碎，而重量为 y 的石头新重量为 y-x。
最后，最多只会剩下一块石头。返回此石头的重量。如果没有石头剩下，就返回 0。
### 思路
直接排好序，然后从最后开始粉碎，如果剩下的石头数目大于1，就接着粉碎，若两者重量相等，直接进行下一次粉碎判定，若不等，按顺序插入差值，最后判断数组是否为空，为空输出0，不为空输出唯一的那个元素。
### code
     int lastStoneWeight(vector<int>& stones) {
        sort(stones.begin(), stones.end());
        int len, buf;
        while((len = stones.size()) > 1)
        {
            buf = stones[len - 1] - stones[len - 2];
            stones.erase(stones.end() - 2, stones.end());
            if(buf != 0)
                stones.insert(upper_bound(stones.begin(), stones.end(), buf), buf);
        }
        
        return stones.empty()? 0 : stones.at(0);
    }
