**###题目**

格雷编码是一个二进制数字系统，在该系统中，两个连续的数值仅有一个位数的差异。给定一个代表编码总位数的非负整数 n，打印其格雷编码序列。格雷编码序列必须以 0 开头。

- 输入：2
- 输出：[0,1,3,2]

**###思路**

根据维基百科介绍的格雷码的三种性质，我们可以得出第一种方法-镜像法，观察下面的几个格雷编码的二进制：

- 0 ：0  (0)
- 1：0 1 (0,1)
- 2：**0**0 **0**1 **1**1 **1**0  (0,1,3,2)
- 3：**0**00 **0**01 **0**11 **0**10 **1**10 **1**11 **1**01 **1**00 (0,1,3,2,6,7,5,4)

观察可以看出从二个格雷码开始，第n个的格雷码集合的二进制是由第n-1个的格雷码集合的二进制分别在前面加上0、1所组成，但注意排列的时候是一个镜像关系，例如第三个格雷码是由第二个格雷码(00、01、11、10)在前面分别添加0、1所组成，但是添加0的时候的顺序是00、01、11、10，添加1的时候的顺序是10、11、01、00，发现了这个特点就很好写代码了。

**###code**

```

class Solution {
public:
vector<int> grayCode(int n) {
    if(n<=0)return {0};//0、1为特殊情况
    if(n==1)return {0,1};
    vector<int>res;
    res.push_back(0);
    res.push_back(1);
    int num=2;
    for (int i=2;i<=n;++i)
    {
        int l=res.size();
        for(int j=l-1;j>=0;--j)//要逆序添加。
        {
            //前面加0的那部分就用原来的res
            res.push_back(res[j]+num);//在前面加上1
        }
        num=num<<1;
    }
    return res;
}
};
```

**###思路**

维基百科介绍的第二个方法就是二进制转格雷码，首先假设以二进制为0的值做为格雷码的第0项，第n个数的二进制数与其格雷码之间的关系可以根据格雷码的定义得到：

 ![img](https://mmbiz.qpic.cn/mmbiz_svg/bj9JGugn6UeichWGHZwfNPhgkiaLbnibXJxcdKo3cC4eIEhnRkok7r7l8l2UjlrrQhZgEvpVRAScqrUypYw1jBzpTLVNtwIoptm/640?wx_fmt=svg&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1) 。

上式中G(n)表示格雷码，B(n)代表二进制码，n代表第n位。计算过程如下图所示(图片来源网络)

![img](https://mmbiz.qpic.cn/mmbiz_jpg/90saic2EqxkJzywSibibpSLkjaKn3EOXfrLs9Uf7etKkXA9PsxpnXo4RvoOb16zHicSEVBCrtklrGfHs7nXrrY4TEw/640?wx_fmt=jpeg&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1)



在程序中如何体现这个错位异或呢？

假设此时计算第n个格雷码，那么我们将n与n>>1进行异或，这样n中的二进制右移一位之后再与原来的i异或，就达成了 ![img](https://mmbiz.qpic.cn/mmbiz_svg/bj9JGugn6UeichWGHZwfNPhgkiaLbnibXJxtITlqqUNJTTaPDfNk5Zr3U2FwuBWmXmNKQY42iciaWA8TvqN3zkQO4riaBWYO2ks3KN/640?wx_fmt=svg&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1) 的要求，二进制的第一位会与0进行异或，相当于保持原来的数不变，事实证明移位计算是真的快，0ms。

**###code**

```
class Solution {
public:
vector<int> grayCode(int n) {
    int l=pow(2.0,n);
    vector<int>res(l,0);
    for(int i=0;i<l;++i)
    {
        res[i]=(i>>1)^i;
    }
    return res;
}
};
```

**###思路**

第三种方法也叫直接排列，以二进制为0值的格雷码为第零项，第一项改变第零项最右边的位元，第二项改变第一项右起第一个为1的位元的左边位元，第三对第二项的改变、第四项对第三项的改变方法同第一对第零项、第二项对第一项的改变，如此循环，即可排列出n个位元的格雷码。

**###code**

```
class Solution {
public:
vector<int> grayCode(int n) {
    int l=pow(2.0,n);
    vector<int>temp(n,0);
    vector<int>res;
    res.push_back(0);
    bool flag=true;
    for(int i=1;i<l;++i)
    {
        if(flag)//第一次改变
        {
            temp[n-1]=temp[n-1]^1;
            flag=false;
        }
        else
        {
            for(int j=n-1;j>0;--j)//第二次改变
            {
                if(temp[j]==1)
                {
                temp[j-1]=temp[j-1]^1;
                flag=true;
                break;
                }
            }
        }
        int num=0;
        for(auto a:temp)//将格雷码转换成10进制存储。
            num=num*2+a;
        res.push_back(num);
    }
    return res;
}
};
```

 