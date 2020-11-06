**第一题：**[根据数字二进制下 1 的数目排序]

给你一个整数数组 arr 。请你将数组中的元素按照其二进制表示中数字 1 的数目升序排序。如果存在多个数字二进制中 1 的数目相同，则必须将它们按照数值大小升序排列。请你返回排序后的数组。

**###思路**

其实也没什么复杂的，就是利用pair将每个数和它的二进制中1的个数组合起来，然后再对这个pair进行排序。

**###code**

```cpp
class Solution {
public:
    void erjinzhi(vector<int>&num,vector<int>&arr)//计算二进制1的个数
    {   
        for(auto i:arr)
        {
            int j=0;
            while(i>0)
            {
                if(i%2!=0)
                    ++j;
                i=i/2;
            }
            num.push_back(j);
        }
        return ;
        
    }
    static bool cmp(pair<int, int> a,pair<int, int> b) {
        if(a.second!=b.second)
            return a.second<b.second;//自定义的比较函数
        else
            return a.first<b.first;
    }
    vector<int> sortByBits(vector<int>& arr) {
        if(arr.size()<=1)
            return arr;
        vector<int>num;
        erjinzhi(num,arr);
        vector<pair<int,int>>arr_num;
        for(int i=0;i<arr.size();++i)
            arr_num.push_back(make_pair(arr[i],num[i]));
        sort(arr_num.begin(),arr_num.end(),cmp);
        vector<int>res;
        for(auto i:arr_num)
        {
            res.push_back(i.first);
        }
        return res;
    }
};
```

**第二题：[每隔 n 个顾客打折]**

超市里正在举行打折活动，每隔 n 个顾客会得到 discount 的折扣。超市里有一些商品，第 i 种商品为 products[i] 且每件单品的价格为 prices[i] 。结账系统会统计顾客的数目，每隔 n 个顾客结账时，该顾客的账单都会打折，折扣为 discount （也就是如果原本账单为 x ，那么实际金额会变成 x-(discount * x)/100)，然后系统会重新开始计数。顾客会购买一些商品， product[i] 是顾客购买的第 i 种商品， amount[i] 是对应的购买该种商品的数目。

请你实现 Cashier 类：

Cashier(int n, int discount, int[] products, int[] prices) 初始化实例对象，参数分别为打折频率n,折扣大小 discount,超市里的商品列表 products 和它们的价格 prices 。

double getBill(int[] product, int[] amount) 返回账单的实际金额（如果有打折，请返回打折后的结果）。

**###思路**

这个感觉就是用一些类的特性就行了，也没啥特点。

**###code**

```cpp
class Cashier {
public:
int discount;
int n;
unordered_map<int, int> price;
int index = 0;
Cashier(int n, int discount, vector<int>& products, vector<int>& prices) {
    this->n = n;
    this->discount = discount;
    for (int i = 0; i < products.size(); i++) {
        price[products[i]] = prices[i];
    }
}

double getBill(vector<int> product, vector<int> amount) {
    index++;
    double value=0;
    for(int i=0;i<product.size();++i)
        value+=price[product[i]]*amount[i];
    if(index%n==0)
    {
        index=0;
        value=value-(value*discount)/100;
    }
    return value;
}
};

/**
* Your Cashier object will be instantiated and called as such:
* Cashier* obj = new Cashier(n, discount, products, prices);
* double param_1 = obj->getBill(product,amount);
*/
```

**第三场：[包含所有三种字符的子字符串数目]**

给你一个字符串 `s` ，它只包含三种字符 a, b 和 c 。请你返回 a，b 和 c 都 **至少** 出现过一次的子字符串数目。

输入：s = "abcabc"

输出：10

解释：包含 a，b 和 c 各至少一次的子字符串为 "abc", "abca", "abcab", "abcabc", "bca", "bcab", "bcabc", "cab", "cabc" 和 "abc" (相同字符串算多次)。

**###思路**

最开始图省事，用的暴力法，果然没过，扎心，果断用的双指针：left=0，right=0,原理如下：

- 从s[left]开始往后找一个子字符串，如果子字符串temp中包含abc，停止寻找。
- 若temp中包含abc，那么temp往后扩展的子字符串也一定包含abc，所以答案直接加上l-right(l为字符串长度，right为temp最后一个字符的下标)，不用往前扩展，从前往后遍历，前面已经被计算过了，然后left++。
- 不包含的情况下，right++，扩大子字符串的长度。

其实就是怎么知道left和right确定的子字符串中含有abc比较麻烦，因为直接每次都寻找就不能通过，所以用一个数组或者字典保存子字符串的abc个数就可以了。



**###code**

```cpp
class Solution {
public:
    int numberOfSubstrings(string s) {
        if(s.size()<3)return 0;
        int l=s.size();
        int left=0;
        int right=0;
        int res=0;
        unordered_map<char,int>map_char;
        //直接用temp.find("a")!=temp.npos&&temp.find("b")!=temp.npos&&temp.find("c")!=temp.npos不能通过
        //所以用一个字典保存abc是否存在。
        map_char['a']=0;
        map_char['b']=0;
        map_char['c']=0;
        map_char[s[0]]++;
        while(right<l)
        {   
            if(map_char['a']&&map_char['b']&&map_char['c'])
            {
               res+=l-right;
               map_char[s[left++]]--;

            }
            else
            {
               right++;
               map_char[s[right]]++;
            }           

        }
        return res;
    }
};
```

**第四题：[有效的快递序列数目]**

给你 n 笔订单，每笔订单都需要快递服务。请你统计所有有效的 收件/配送 序列的数目，确保第 i 个物品的配送服务 delivery(i) 总是在其收件服务 pickup(i) 之后。由于答案可能很大，请返回答案对 10^9 + 7 取余的结果。

- 输入：n = 2
- 输出：6
- 解释：所有可能的序列包括：
- (P1,P2,D1,D2)，(P1,P2,D2,D1)，(P1,D1,P2,D2)，(P2,P1,D1,D2)，(P2,P1,D2,D1) 和 (P2,D2,P1,D1)。(P1,D2,P2,D1) 是一个无效的序列，因为物品 2 的收件服务（P2）不应在物品 2 的配送服务（D2）之后。

**###思路**

一看到这个题目，哈哈哈，这不是排列组合嘛，想起了被概率论支配的恐惧了吧，思路如下：

- 假设求n对快递的有效序列，那么其实可以在n-1对已经摆好的快递对里插入一对新的快递对，那么新插入这一对快递有多少种插入法呢？
- 假设n-1对快递排好了，那么一共有2(n-1)+1个空隙位置，所以一共可以新的那对序列的插入方法一共有2(n-1)+1、2(n-1)、2(n-1)-1、........1的和那么多种，原因如图：

![img](https://pic4.zhimg.com/80/v2-4159957ed614ed251ebc353f11e5978f_720w.jpg)

- n-1对快递对有效的序列假设是a种，那么最后n的有效序列对应该就是a*b(b为上一步求出的和)，因为针对a个n-1的有效快递对，新的那一个序列对都可以有b种插入方式。

**###code**

```cpp
class Solution {
public:
    int countOrders(int n) {
        if(n==1) return 1;
        int last_res=1;
        long long res=0;
        int temp=2;
        int mod=1e9+7;//开始写成10^9+7,一直答案错的，后来输出mod才发现是哪里错了。
        while(temp<=n)
        {
            int temp_num=2*(temp-1)+1;
            res=0;
            while(temp_num)
            {
                res+=temp_num;
                res=res%mod;
                temp_num--;
            }
            res=(last_res*res)%mod;
            last_res=res;
            temp++;
        }
        int  res_int=res;
        return res_int;
    }
};
```