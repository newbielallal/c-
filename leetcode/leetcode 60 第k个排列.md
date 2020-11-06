\### 题目

给出集合 [1,2,3,…,n]，其所有元素共有 n! 种排列。

按大小顺序列出所有排列情况，并一一标记，当 n = 3 时, 所有排列如下：

"123"
"132"
"213"
"231"
"312"
"321"
给定 n 和 k，返回第 k 个排列。

说明：

给定 n 的范围是 [1, 9]。
给定 k 的范围是[1,  n!]。
示例 1:

输入: n = 3, k = 3
输出: "213"
示例 2:

输入: n = 4, k = 9
输出: "2314"


\### 思路

​    可以不用回溯法，直接通过要确定第几个排列，从而确定每个位置的元素。

我们知道N个元素一共有n！种排列，那么第n个数的每个不同的开头都有（n-1）！种排列，那么就可以可以对k做(n-1)!的除法得到第1个位置的数字应该是多少，然后再将k减去t*(n-1)!在开始循环，其中t就是k对（n-1)!做除法得到的商，具体通过一个例子来讲解：

假设 n=5,k=32，建立num矩阵[1,2,3,4,5].结果为res=“”；

通过计算得到（n-1)!=24，那么k除以24得到的是一个大于1小于2的数（这里不能直接用两个int相除，因为我们要判断是否这个除数时大于某个整数m的，因为等于m的时候取m-1，大于m小于m+1的时候取值时m），那么将t取值为1，取num[t]作为第一位的数，res=2,在num中删除掉num[t]，num变为[1,3,4,5],k=k-t*24=8.

（n-2)!=6，8/6大于1小于2，所以t取1，第二位的数为num[t],删除num[t],num=[1,4,5],然后res=23,k=k-6=2;

（n-3)!=2，2/2等于1，所以t取0，第3位的数为num[t],删除num[t],num=[4,5],然后res=231,k=k-2*0=2;

（n-4)!=1，2/1等于2，所以t取1，第4位的数为num[t],删除num[t],num=[4],然后res=2315,k=k-1*1=1;

（n-5)!=1，1/1等于1，所以t取0，第5位的数为num[t],删除num[t],num=[],然后res=23154,k=k-1*1=0;

循环次数达到n的长度，循环结束，输出结果23154。



\### code

```cpp
class Solution {
public:
int jc(int n)
{
    int num=1;
    for(int i=1;i<=n;++i)
            num=num*i;
    return num;
}
    string getPermutation(int n, int k) {
        vector<string> num={"1","2","3","4","5","6","7","8","9"};
        if(n<=1)
            return "1";
        string res;
        for(int i=1;i<=n;++i)
        {
            int temp=jc(n-i);
            
            int l=ceil(double(k)/double(temp))-1;
            k=k-l*temp;
            res=res+num[l];
             num.erase (num.begin()+l);
        }
        return res;
        

    }
};
```

![点击并拖拽以移动](data:image/gif;base64,R0lGODlhAQABAPABAP///wAAACH5BAEKAAAALAAAAAABAAEAAAICRAEAOw==)