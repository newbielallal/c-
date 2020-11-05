---
title: leetcode 8. 字符串转换整数 (atoi)
tags:
  - c++ 
categories: c++ 
---
单纯的暴力法，但是可以对比下库函数是怎么写的。
<!-- more -->

### 题目

请你来实现一个 atoi 函数，使其能将字符串转换成整数。

首先，该函数会根据需要丢弃无用的开头空格字符，直到寻找到第一个非空格的字符为止。

当我们寻找到的第一个非空字符为正或者负号时，则将该符号与之后面尽可能多的连续数字组合起来，作为该整数的正负号；假如第一个非空字符是数字，则直接将其与之后连续的数字字符组合起来，形成整数。

该字符串除了有效的整数部分之后也可能会存在多余的字符，这些字符可以被忽略，它们对于函数不应该造成影响。

注意：假如该字符串中的第一个非空格字符不是一个有效整数字符、字符串为空或字符串仅包含空白字符时，则你的函数不需要进行转换。

在任何情况下，若函数不能进行有效的转换时，请返回 0。

说明：

假设我们的环境只能存储 32 位大小的有符号整数，那么其数值范围为 [−231,  231 − 1]。如果数值超过这个范围，请返回  INT_MAX (231 − 1) 或 INT_MIN (−231) 。

示例 1:

输入: "42"
输出: 42
示例 2:

输入: "   -42"
输出: -42
解释: 第一个非空白字符为 '-', 它是一个负号。
     我们尽可能将负号与后面所有连续出现的数字组合起来，最后得到 -42 。
示例 3:

输入: "4193 with words"
输出: 4193
解释: 转换截止于数字 '3' ，因为它的下一个字符不为数字。
示例 4:

输入: "words and 987"
输出: 0
解释: 第一个非空字符是 'w', 但它不是数字或正、负号。因此无法执行有效的转换。
示例 5:

输入: "-91283472332"
输出: -2147483648
解释: 数字 "-91283472332" 超过 32 位有符号整数范围。 
     因此返回 INT_MIN (−231) 。
### 思路
对字符串的字符挨个检查，注意细节上的处理就ok了,主要是处理下面几个问题：
1--指针为NULL
2--空字符处理
3--正号与负号的处理
4--溢出处理
5--如果遇到异常字符怎么处理。
### code

     class Solution {
	public:
    int myAtoi(string str) {
       int l=str.size();
        if(l<=0)//如果字符串为空，直接返回0，
            return 0;
        int i=0;
        for(i=0;i<l;i++)
        {
            if(str[i]==' ')//取出字符串首部的空格。
                continue;
            else
            {
                break;
            }
        }
        long long res=0;//因为可能会大于INT_MAX，所以用了这个，防止溢出。
        int flag=1;//用来记录正负。
        if(i<l)//判断正负号是否存在。
        {
            if(str[i]=='-')
            {
                flag=0;
                i++;
            }
            else if(str[i]=='+')
                i++;
          
        }
        for(;i<l;++i)
        {
            if(str[i]<48||str[i]>57)//如果遇到非法输入，直接就结束了。
                break;
            else
                res=res*10+(str[i]-48);
            if(res>INT_MAX)//如果产生了溢出。
            {
                res=INT_MAX;
                
                if(flag)//正数直接返回int最大值
                    return res;
                return -1*res-1;//负数返回int最小值，因为int最小值可以表示的比int最大值多1，所以减了1.
            }
                
        }
        if(flag)//按照正负号正常返回。
            return res;
        return -1*res;
    }
	};

### 思路

c语言提供的atoi函数的标准写法，对输入要求比较高。
例如：
输入   输出
asd123 0
123    123
-123   -123
+123   123
++123  0
11r123 11
  1123 1123
为空   0
“*”   0 
"999999999999999" 返回输入太大，int型无法表示，报错。

### code

     isspace(int x)//判断是否是无效的输入。
	{
	 if(x==' '||x=='\t'||x=='\n'||x=='\f'||x=='\b'||x=='\r')
	  return 1;
	 else  
	  return 0;
	}
	isdigit(int x)//判断是否是数字
	{
	 if(x<='9'&&x>='0')         
	  return 1; 
	 else 
	  return 0;
	 
	}
	int atoi(const char *nptr)
	{
	        int c;              /* current char */
	        int total;         /* current total */
	        int sign;           /* if '-', then negative, otherwise positive */
	 
	        /* skip whitespace */
	        while ( isspace((int)(unsigned char)*nptr) )//如果判断该字符是无效输入中的一种，直接字符串指针加加。
	            ++nptr;
	 
	        c = (int)(unsigned char)*nptr++;
         //如果char默认为signed（可能是平台相关的），则将char转为int时，会有符号位扩展，而unsigned char则不会。
        //atoi函数应该希望避免符号位扩展而带来问题。不过，好在数字0到9的ACSII码并没有超过0x7F，
        //因此是否事先转成unsigned char应该不会对结果有影响。

	        sign = c;           /* save sign indication */
	        if (c == '-' || c == '+')
	            c = (int)(unsigned char)*nptr++;    /* skip sign */
	 
	        total = 0;
	        while (isdigit(c)) //判断是否是数字。
           {
	            total = 10 * total + (c - '0');     /* accumulate digit */
	            c = (int)(unsigned char)*nptr++;    /* get next char */
	        }
	 
	        if (sign == '-')
	            return -total;
	        else
	            return total;   /* return result, negated if necessary */
	}
 
