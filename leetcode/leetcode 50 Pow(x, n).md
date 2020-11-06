**###题目**

实现pow(x,n) ，即计算 x 的 n 次幂函数。

说明:

- -100.0 < *x* < 100.0
- *n* 是 32 位有符号整数，其数值范围是 [−231, 231 − 1] 。

**###思路**

首先利用暴力法尝试，暴力法的思路很简单，就是将x乘以n次，在n为负的情况下，将n取绝对值，然后将x变成1/x，然后就和n为正的时候计算思路一样。

**###code**

```cpp
class Solution {
public:
    double myPow(double x, int n) {
        long long i = n;//n有-2^31,变成正数后会超过int型的范围，所以用long long防止溢出。
        if (i < 0) {
            x = 1 / x;
            i = abs(i);
        }
        double res= 1.0;
        for (; i; --i)
            res= res* x;
        return res;
    }
};
```

运行之后发现暴力法并不能通过用例x=1.00000,n=2147483647.因为暴力法是每次循环乘一个x，所以我们的优化方法就是每次让多个x相乘，减少循环次数。

**###思路**

假如已知X^n的结果，那怎么得出X^(2n)的结果，以第一种方法来说，就是将X^n再乘n次X，其实完全没必要这样计算，可以直接让X^n乘上X^n,这样只用计算一次。第二种方法的本质就是这样的。

- 在n为偶数的情况下，可以将X^n变成X^(n/2)*X^(n/2);
- 在n为奇数的情况下，可以将X^n变成X^(n/2)*X^(n/2)*X；
- 在n为0的情况下，直接返回1.0，这也是递归的跳出点。

**###code**

```cpp
class Solution {
public:
double digui(double x, long long n) {
    if (n == 0) {
        return 1.0;
    }
    double half = digui(x, n / 2);//先计算出half的值。
    if (n % 2 == 0) {
        return half * half;//如果在return里面计算，会有很多冗余计算，会超时。
    } else {
        return half * half * x;
    }
}
double myPow(double x, int n) {
    long long i = n;//同理，防溢出
    if (i < 0) {
        x = 1 / x;
        i = abs(i);
    }
    return digui(x, i);
}
};
```

此方法成功通过，并且运行时间短。

![img](https://pic1.zhimg.com/80/v2-b6cae263c1b967cd858eb510459e154c_720w.jpg)

**###思路**

大部分递归都可以写成循环，递归一般可以用循环代替，所以试着将第二种方法里的递归改成循环，但是有不同的地方。

- i为偶数，temp=temp*temp
- i为奇数，temp=temp*temp*temp，这里不是再乘上一个x了。
- i为0，跳出循环，输出结果。

**###code**

```cpp
class Solution {
public:
    double myPow(double x, int n) {
        long long i = n;
        if (i < 0) {
            x = 1 / x;
            i = abs(i);
        }
        double res = 1;
        double temp = x;
        for (i; i ; i/= 2) {
            if ((i % 2) == 1)//递归是从下往上乘，这个其实是从上往下乘，所以不能乘x。 
            {
                res = res * temp;
            }
            temp = temp * temp;
        }
        return res;
    }
};
```