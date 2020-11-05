---
title: leetcode 1011 在 D 天内送达包裹的能力
tags:
  - c++ 
categories: c++ 
---
问题不复杂，就是不停向上取值然后尝试能否成功就可以了
<!-- more -->

### 题目
传送带上的包裹必须在 D 天内从一个港口运送到另一个港口。

传送带上的第 i 个包裹的重量为 weights[i]。每一天，我们都会按给出重量的顺序往传送带上装载包裹。我们装载的重量不会超过船的最大运载重量。

返回能在 D 天内将传送带上的所有包裹送达的船的最低运载能力。

 

示例 1：

输入：weights = [1,2,3,4,5,6,7,8,9,10], D = 5
输出：15
解释：
船舶最低载重 15 就能够在 5 天内送达所有包裹，如下所示：
第 1 天：1, 2, 3, 4, 5
第 2 天：6, 7
第 3 天：8
第 4 天：9
第 5 天：10

请注意，货物必须按照给定的顺序装运，因此使用载重能力为 14 的船舶并将包装分成 (2, 3, 4, 5), (1, 6, 7), (8), (9), (10) 是不允许的。 
### 思路
思路比较简单，首先找到货物数组的最大值，因为能满足成功运载货物最低要求的运载能力就是货物最大值，然后逐渐往上增加这个值，知道满足能够D天之内送达就可以了，因为没用什么技巧，所以速度很慢，耗时挺多的。
### code

     int shipWithinDays(vector<int>& weights, int D) {
        int res=*max_element(weights.begin(), weights.end());//找到最大值，因为题目给了参数限制，所以就没管边界的事情了。
        while(1)
        {
            int day=0;
            int weight=0;
            for(int i=0;i<weights.size();++i)
            {
                weight+=weights[i];
                if(weight>res)
                {
                    ++day;
                    weight=weights[i];
                }
            }
            if(++day>D)//判断是否满足条件，不满足加一，满足返回答案。
                ++res;
            else
                return res;
            
        }
        return res;
    }

### 思路
原理其实和上一种办法没什么大的区别，但是在寻找能够满足条件的最低运载能力的时候使用的是二分法来进行寻找，所以会快很多，因为二分法是logN，上面相当于是直接遍历，就是N，所以时间快了很多。
### code

     int shipWithinDays(vector<int>& weights, int D) {
        int l=*max_element(weights.begin(), weights.end());//找到最大值，因为题目给了参数限制，所以就没管边界的事情了。
        int r=INT_MAX;//这个值可以不用设置这么大，根据对天数和货物重量的约束条件可以调小，加快速度。
        while(l<r)
        {
            int mid=l+((r-l)>>1);//当前进行测试的重量。
            int day=0;
            int weight=0;
            for(int i=0;i<weights.size();i++)
            {
                weight+=weights[i];
                if(weight>mid)
                day++,weight=weights[i];                
            }
            if(++day>D) l=mid+1;//天数超了，说明需要增加运载能力。
            else  r=mid;//天数大于等于D，但是要找最小运载能力，所以等于时不能返回，只能让r=mid逐渐逼近。
        }
        return l;
    }

