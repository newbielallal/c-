---
title: leetcode 29  两数相除
tags:
  - c++ 
categories: c++ 
---
可以利用减法模拟除法，但是速度会很慢。

<!-- more -->

### 题目

给定两个整数，被除数 dividend 和除数 divisor。将两数相除，要求不使用乘法、除法和 mod 运算符。

返回被除数 dividend 除以除数 divisor 得到的商。

示例 1:

输入: dividend = 10, divisor = 3
输出: 3
示例 2:

输入: dividend = 7, divisor = -3
输出: -2
说明:

被除数和除数均为 32 位有符号整数。
除数不为 0。
假设我们的环境只能存储 32 位有符号整数，其数值范围是 [−231,  231 − 1]。本题中，如果除法结果溢出，则返回 231 − 1。

### 思路

本来是用减法代替除法的，果然一拍脑门想出的办法都是过不了时间的，既然减法不行，那就用乘法，直接用移位代替乘法，速度更快，效果一样的。具体举例如下所示：

被除数：17 除数：2
17大于2*2=4
继续比较（同时temp*2，mid*2）
17>4*2=8
继续比较（同时temp*2，mid*2）
17>8*2=16
继续比较（同时temp*2，mid*2）
17<16*2
所以更改result为8，result+=mid;（因为temp是每次乘上2，代表除数中有2的n次方个除数，所以mid也是每次都乘上2的）
17-16=1
1小于除数2，结束，输出结果8

### code

    class Solution {
	public:
	    int divide(int dividend, int divisor) {
	         if((dividend==INT_MIN && divisor==-1)||(dividend==INT_MAX && divisor==1)) return INT_MAX;
              //题目说结果溢出时候返回2^31-1，只有在被除数为INT_MIN的时候，除数为-1才可能会溢出，其他时候都能正确运行得到结果。
	        if(dividend==0) return 0;//除数不会使是0；
	        int sign=((dividend<0)^(divisor<0))? -1 : 1;//如果符号不是一样的情况下，就说明结果是负数。
	        long x=(long)dividend,y=(long)divisor;//将除数和被除数转换成long型，防止溢出。
	        if(dividend<0)
	            x=-(long)dividend;
	        if(divisor<0)
	            y=-(long)divisor;
	        long result=0;
	        while(x>=y)//这里就是计算的过程。
	        {
	            long temp=y,mid=1;
	            while(x>=(temp<<1))
	            {
	                mid<<=1;
	                temp<<=1;
	            }
	            result+=mid;
	            
	            x-=temp;
	        }
	        return sign>0 ? result : -result;
	    }
	};



