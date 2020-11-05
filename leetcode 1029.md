---
title: leetcode 1029 两地调度
tags:
  - c++ 
categories: c++ 
---
如题

<!-- more -->

### 题目
公司计划面试 2N 人。第 i 人飞往 A 市的费用为 costs[i][0]，飞往 B 市的费用为 costs[i][1]。

返回将每个人都飞到某座城市的最低费用，要求每个城市都有 N 人抵达。

### 思路
这个问题其实不应该将ab两地的费用分开来看，而是将两地费用的差值作为一个比较对象来对数组进行重新排序，差值越小，说明越应该选择那个费用更小的城市。


### code
    //因为：非静态成员函数是依赖于具体对象的，而std::sort这类函数是全局的，因此无法再sort中调用非静态成员函数。静态成员函数或者全      局，函数是不依赖于具体对象的, 可以独立访问，无须创建任何对象实例就可以访问。同时静态成员函数不可以调用类的非静态成员。
    static  bool fcmp(vector<int>&a,vector<int>&b)
    //要声明成为静态成员函数或全局函数,将a和b由按值传递改为按引用传递之后，速度从20ms变成了4ms；
    {
        if((a[0]-a[1])<(b[0]-b[1]))
            return true;
        return false;
    }
    int twoCitySchedCost(vector<vector<int>>& costs) {
        //这个其实就是将ab两地费用差最大的值先选择晓得，将数组按照ab之间的距离费用排序。
        int l=costs.size();
        if(l<1)
            return 0;
        sort(costs.begin(),costs.end(),fcmp);
        int res=0;
        for(int i=0;i<l/2;i++)
        {
            res=res+costs[i][0];
        }
        for(int i=l/2;i<l;i++)
            res=res+costs[i][1];
        return res;
    }