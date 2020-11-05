---
title: 最近关于c++学习的笔记
tags:
  - c++ 
categories: c++学习 
---

最近学习的一些知识点

<!-- more -->

再做两数之和这个问题的时候，关于res[nums[i]]=i这条语句的放置位置导致了结果的完全不同。
题目：
给定一个整数数组 nums 和一个目标值 target，请你在该数组中找出和为目标值的那两个整数，并返回他们的数组下标。
你可以假设每种输入只会对应一个答案。但是，你不能重复利用这个数组中同样的元素。
1、正确解法
vector<int> twoSum(vector<int>& nums, int target) {
        map <int,int> res;
      
        map<int,int>::iterator iter;
        for(int i=0;i<nums.size();i++)
        {
           
            iter = res.find(target-nums[i]);
            
            if(iter!=res.end())
             {
                 
                 
                 return {res[target-nums[i]],i};
             }
             res[nums[i]]=i;//将此语句放在前方就会出错。
        }
        return {-1,-1};
    }
2、错误解法
vector<int> twoSum(vector<int>& nums, int target) {
        map <int,int> res;
        vector<int> num;
        map<int,int>::iterator iter;
        for(int i=0;i<nums.size();i++)
        {
           
            iter = res.find(target-nums[i]);
             res[nums[i]]=i;
            if(iter!=res.end())
             {
                 num.push_back(res[target-nums[i]]);
                 num.push_back(i);
                 return num;
             }
        }
        return num;
    }
解析：错误写法中在结果输出前就进行了res的添加操作，如果有两个相同的数字相加等于结果，如果先进行赋值，就会将前一个覆盖掉，例如【3，3】，需要得到6，后赋值会得到【0，1】，而错误解法就会得到【1，1】。

字典的初始化方式：
1、dict[i]=j;dict[t]=y;
2、初始化时进行定义｛｛i，j｝，｛t,y｝｝
	
这个博客https://blog.csdn.net/qq_32320399/article/details/81518476 没怎么看懂。

为什么哈希结构的速度要比顺序存储结构的速度快，因为哈希结构是将KEY值与地址进行对应，省去了查找的时间。

在使用递归进行数组的检查问题时，尤其是满足什么条件在数组内部进行扩展时，一定要注意将检查过的数组进行设置，否则很有可能陷入死循环导致栈溢出，例如检查数组中相邻1的个数，如果检查过的1未置成0，则递归会在相邻的几个1之间来回跳动。

1018：能被5整除的二进制前缀。给定一个只包含0、1的数组，如果组成的二进制数能被5整除，就将结果加上true，反之在结果中加上false
第一次求解：
        vector<bool>res;
        long int cout=0;
        for(int i=0;i<A.size();i++)
        {
            cout=cout*2+A[i];
            if(cout%5==0)
                res.push_back(true);
            else
                res.push_back(false);
            
            
        }
        return res;
思路虽然正确，但是在A过长的时候会导致count溢出，第一次相出的办法是，如果（a+b）%5==0，那我将count减去一个很大的并且能够被5整除的数，在进行余下数字的判断。但是后来一想，不是直接取余就可以了嘛，a最大的能够被5整除的一部分，不就是a-a%5嘛。
a=a*2+A[i];   
// 40ms: a*2+A[i]                 
24ms: (a<<1)+A[i] 
a=a%5;
在进行除以2或者乘以2的操作时，使用位运算普遍比使用乘除法速度要快很多。比如上面，快了接近一倍。

做题的时候一定要注意边界条件的判断，尤其是变过形式之后的循环，还有就是编程的时候可以针对不同的数据设立不同的判断条件，可以很大程度上避免过多无用的运算。并且在循环很多的时候，一定要注意判断语句的位置。

int型不能在一条语句中直接转换成double型，涉及到低维向高维转换。（存疑，可能是其他地方写错了。）

对于分治算法，最重要的是要找到简单的基线条件，进而确定如何缩小问题的规模，使其符合基线条件。

strlen统计长度不包括'/0'。

解决链表问题时，可以使用两个指针进行遍历，并且设置两个指针的出发时间、或者遍历速度不一致，这样相比于一个指针，可能就只需要一次遍历了就能够解决问题。

162.峰值元素是指其值大于左右相邻值的元素。给定一个输入数组 nums，其中 nums[i] ≠ nums[i+1]，找到峰值元素并返回其索引。数组可能包含多个峰值，在这种情况下，返回任何一个峰值所在位置即可。
你可以假设 nums[-1] = nums[n] = -∞。
示例 1:
输入: nums = [1,2,3,1]
输出: 2
解释: 3 是峰值元素，你的函数应该返回其索引 2。
在要求时间复杂度是0（logn）的时候一般优先考虑二分查找。
int findPeakElement(vector<int>& nums) {
        int left=0;
        int right=nums.size()-1;
        while (left < right)
        {
        int mid = left + (right - left) / 2;
        if (nums[mid] > nums[mid + 1]) //nums[i]>nums[i+1],峰值一定在i之前（包括i），反之若nums[i]<nums[i+1],则峰值一定在i+1之后（包括i+1），这是由于边界为-无穷所决定的。
        {
            right = mid;
        } 
        else {
            left = mid + 1;
        }
            //不可能存在相等的情况。
    }
    return left;｝

声明：vector<T>  vec;
方法一： return vec.at(vec.size()-1);
方法二： return vec.back();
方法三： return vec.end()-1;  注意：end指向末尾元素的下一个元素。
方法四： return vec.rbegin();//这四种方法都是寻找最后一个元素。
vec.clear() //清除所有元素，但是保留这个vector。

（1）调用类或者结构之内的成员时，指针变量使用->,非指针变量用.进行读取，所有的指针变量读取成员是都是使用->。
（2）完全二叉树从1开始时，子节点与父节点的关系是：左子节点=父节点*2，右子节点=父节点*2+1，如果是从0开始的，那么子节点与父节点的关系是：左子节点=父节点*2+1，右子节点=父节点*2+2。
（3）尾递归是最简单的递归，编译器会自动将其优化为循环。
（4）抽象数据类型的三要素：1、类型名称 2、数据对象集 3、操作集
（5）结构体一般喜欢传指针，因为传指针更方便，一般传值只是复制，或者传引用也可以。