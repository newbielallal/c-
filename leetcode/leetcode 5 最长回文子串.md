---
title: leetcode 5. 最长回文子串
tags:
  - c++ 
categories: c++ 
---
直接利用动态规划，主要是写好状态转移方程。
<!-- more -->

### 题目

给定一个字符串 s，找到 s 中最长的回文子串。你可以假设 s 的最大长度为 1000。

示例 1：

输入: "babad"
输出: "bab"
注意: "aba" 也是一个有效答案。
示例 2：

输入: "cbbd"
输出: "bb"




### 思路

主要是要找好动态转移方程，定义一个长宽等于字符串长度的二维数组，其中若二位数组dp [i] [j]的值为1，代表在s中从下标i开始到下标j这段长度的字符子串是回文字符串，首先，一个字符肯定是回文子串，所以将dp[i] [i]（i从0到字符串长度）都设置为1，然后开始遍历，遍历过程中主要就是转移方程了，假设有s[i]==s[j],那表明它满足了新增的两个字符相等的条件，接下来就是看这两个字符往内层的子串是否也是回文的，所以只要dp[i+1] [j-1]为1，代表从i+1到j-1都是满足回文的，那么s[i]如果等于s[j]，那么回文子串就可以加上两个新成员，还有一种就是它们两是相邻的，那么只要有j-1==1，也可以代表这是一个新增的长度为2的新回文子串，最后再找出长度最长的回文子串输出就可以了，但是这个的时间复杂度为n*2，因为有两重嵌套循环，空间复杂度也是n*2，状态转移方程为：
dp[l] [r] = (s[l]==s[r] && (r-l==1 || dp[l+1] [r-1])) ? true : false

### code

     class Solution {
    public:
    string longestPalindrome(string s) {
        //动态规划做
        int l=s.size();
        if(l==0)
            return "";
        int max_l=0,max_r=0;
        vector<vector<int>>dp(l,vector<int>(l,0));
        for(int i=0;i<l;++i)
            dp[i][i]=1;
        for(int right=1;right<l;++right)
        {
            for(int left=0;left<right;++left)
            {
                if(s[left]==s[right]&&(right-left==1||dp[left+1][right-1]))
                {
                    dp[left][right]=1;
                    if(right-left>max_r-max_l)
                    {
                        max_r=right;
                        max_l=left;
                    }
                }
            }
        }
        return s.substr(max_l,max_r-max_l+1);
            
    }
    };

### 思路

第二种思路就是中心扩展法，速度快了5倍左右吧，思想很简单，就是依次将每个字符串中的字符作为一个可能存在的回文子串的中心字符，那么中心有两种中心方式：
第一种，回文子串长度是奇数，那么就是往两边扩展的，假设中心字符下标为i，那么只要有下标为i-1和i+1的两个字符相等，那么回文子串的长度加2，并且继续一个往前，一个往后遍历，也就是说继续比较下标为i-2和i+2的两个字符，直到找到不相等的或者说到达字符串边界，那么代表以s [i]
为中心的最长回文子串找到了。
第二种，回文子串的长度是偶数，那么就先对比s[i]以及s[i+1]，如果两者相等，那么继续比较s[i-1]和s[i+2]，知道超出字符串的边界或者不相等，这样就能找到最长的回文子串，s[i]可能是中中心，也可能是右中心，但是这个不用分别计算，因为s[i]如果是这个子串的右中心，那么就一定是下一个字符的子串的左中心，所以不会漏掉。

### code

     class Solution {
    public:
    int f(string &s,int i,int len)
    {
        int l1=1;
        int l2=1;
        int l=i-1;
        int r=i+1;
        while(l>=0&&r<len)
        {
            if(s[l]==s[r])
                l1+=2;
            else
                break;
            l--;
            r++;
        }
        for (l = i, r = i+1; l >= 0 && r < s.size() && s[l] == s[r]; l--, r++);
        l2 = r - l - 1;
        return max(l1, l2);
    }
    string longestPalindrome(string s) {
        //中心扩展法
        int len=s.size();
        if(len<=1)
            return s;
        int max_len=0,start=0;
        for(int i=0;i<len;++i)
        {
            int temp=f(s,i,len);
            if(temp>max_len)
            {
                max_len=temp;
                start=i-(temp-1)/2;
            }
        }
        return s.substr(start,max_len);
            
    }
    };

\### 思路

   上诉提到的都是有冗余计算的，这是因为回文串长度的奇偶性造成了不同性质的对称轴位置，前面的解法会当成两种情况处理，可看下面几张图：

中心拓展法：![img](https://img-blog.csdnimg.cn/20200115193914137.png)![点击并拖拽以移动](data:image/gif;base64,R0lGODlhAQABAPABAP///wAAACH5BAEKAAAALAAAAAABAAEAAAICRAEAOw==)



动态规划：![img](https://img-blog.csdnimg.cn/20200115193935637.png)![点击并拖拽以移动](data:image/gif;base64,R0lGODlhAQABAPABAP///wAAACH5BAEKAAAALAAAAAABAAEAAAICRAEAOw==)



马拉车：![img](https://img-blog.csdnimg.cn/20200115193943986.png)![点击并拖拽以移动](data:image/gif;base64,R0lGODlhAQABAPABAP///wAAACH5BAEKAAAALAAAAAABAAEAAAICRAEAOw==)



这是因为由很多子串会被重复的访问，例如下面这个字符串：

![img](https://img-blog.csdnimg.cn/20200115193958706.png)![点击并拖拽以移动](data:image/gif;base64,R0lGODlhAQABAPABAP///wAAACH5BAEKAAAALAAAAAABAAEAAAICRAEAOw==)



​    如果利用上面最快的扩展法，我们可以看到以d为中心的时候，aba被遍历过一次，以b为中心的时候，两个a又被遍历了一次，Manacher可以避免这些计算。

​    首先是第一步，为了避免奇偶两种情况，对字符串做一个预处理，在每个字符的两边插上一个特殊字符，要求这个特殊字符是不会在原串中出现的。这样会使得所有的串都是奇数长度的，因为假设原字符串长度为n，现在字符串长度为3*n，肯定奇数，并且回文串的中心肯定是个奇数，因为每个原来的字符至少两边有个相等的特殊字符。



​    第二步就是解决重复访问的问题，因为回文串的中心为单数，我们用temp[i]表示以i位置为中心的回文字符串最左或者最右到达i的长度，用temp[i] 表示以第 i 个字符为对称轴的回文串的回文半径，因为处理时从左往右的，所以就定义temp[i] 为第 i 个字符为对称轴的回文串的最右一个字符与字符 i 的距离，加上本字符，具体如下：

![img](https://img-blog.csdnimg.cn/20200115194108288.png)![点击并拖拽以移动](data:image/gif;base64,R0lGODlhAQABAPABAP///wAAACH5BAEKAAAALAAAAAABAAEAAAICRAEAOw==)

​    可以通过上表看出，其实temp[i]-1就是以i为中心的最长回文字符串，所以只要求出temp数组，基本就可以搞定了所以引入一个辅助变量 Max_Right，表示以及访问了的所有回文子串能到达的最右的一个字符的位置。另外还要记录下 Max_Right 对应的回文串的对称轴所在的位置，记为 pos,具体的位置如下所示：

![img](https://img-blog.csdnimg.cn/20200115194124898.png)![点击并拖拽以移动](data:image/gif;base64,R0lGODlhAQABAPABAP///wAAACH5BAEKAAAALAAAAAABAAEAAAICRAEAOw==)



   我们从左往右地访问字符串来求temp，假设当前访问到的位置为i。对应上图，因为我们是从左到右遍历i, 而pos是遍历到的所有回文子串中某个对称轴位置（MaxRight最大时），所以必然有pos<=i，然后要处理的情况就是i在max_right左边还是右边。

 1、i在max_right右边，如下图所示：

![img](https://img-blog.csdnimg.cn/20200115194137656.png)![点击并拖拽以移动](data:image/gif;base64,R0lGODlhAQABAPABAP///wAAACH5BAEKAAAALAAAAAABAAEAAAICRAEAOw==)



这种情况下因为s[i]左右的字符串都未处理过，所以只能让Temp[i]=1,后续在做处理。

2、i在max_right的左边

2.1 i关于pos对称的那个点的最远字符未超过以pos为中心的回文字符串

![img](https://img-blog.csdnimg.cn/20200115194234810.png)![点击并拖拽以移动](data:image/gif;base64,R0lGODlhAQABAPABAP///wAAACH5BAEKAAAALAAAAAABAAEAAAICRAEAOw==)



​    点j是点i关于pos的对称点，因为pos是回文字符串的中心，所以i与j肯定相同，并且i与j两边的元素都是相同的，所以只要j的回文字符串在在以pos点为中心的回文字符串的范围内，那么肯定以i为中心的回文字符串也不会超出以pos点为中心的回文字符串，所以直接让temp[i]=temp[j]就可以了。

2.2 i关于pos对称的那个点的最远字符超过以pos为中心的回文字符串

![img](https://img-blog.csdnimg.cn/20200115194249540.png)![点击并拖拽以移动](data:image/gif;base64,R0lGODlhAQABAPABAP///wAAACH5BAEKAAAALAAAAAABAAEAAAICRAEAOw==)



​     同理，点j是点i关于pos的对称点，因为pos是回文字符串的中心，所以i与j肯定相同，并且i与j两边的元素都是相同的，但是以j为中心的回文字符串已经包含以pos为中心的回文字符串外面的元素了，所以依靠以pos为中心的回文字符串所推导出来的i与j附近元素相等这一结论不适用于字符串外的元素，所以只能temp[i]=max_right-i,代表通过以pos为中心的字符串所能保证的最远距离。

 所以就得到对于temp的赋值程序：

```
if(i<max_right)temp[i]=min(temp[2*pos-i],max_right-i);

        else temp[i]=1;
```

![点击并拖拽以移动](data:image/gif;base64,R0lGODlhAQABAPABAP///wAAACH5BAEKAAAALAAAAAABAAEAAAICRAEAOw==)

​      然后就是对数据进行更新，temp[i]的值因为不知道是(可以针对每个情况单独写)哪一种情况下赋值的，所以统一要往外扩展，扩展结束之后需要更新这四个max_right、 pos、res、res_pos。其中res代表最长的temp[i]，res_pos存储i。



最后返回最终的结果就是

```cpp
s.substr((res_pos-res+1)/2,res-1);
```

![点击并拖拽以移动](data:image/gif;base64,R0lGODlhAQABAPABAP///wAAACH5BAEKAAAALAAAAAABAAEAAAICRAEAOw==)

因为上诉提到，temp[i]-1等于该位置的元素在原来的数组中的回文字符串长度，而res_pos-res+1可以得出以i为中心，以temp[i]-1为长度的字符串的第一个元素的位置。




\### code

```cpp
class Solution {
public:
   string longestPalindrome(string s)
{
	if(s.size()==0)
        return "";
    string s1;
    for(auto a:s)
    {
        s1=s1+'#';
        s1=s1+a;
    }
    s1=s1+'#';
    int l=s1.size();
    vector<int>temp(l,0);
    int max_right=0,pos=0,res=0,res_pos=0;
    for(int i=0;i<l;++i)
    {
        if(i<max_right)temp[i]=min(temp[2*pos-i],max_right-i);
        else temp[i]=1;
        while(i-temp[i]>=0&&i+temp[i]<l&&s1[i-temp[i]]==s1[i+temp[i]])
            temp[i]++;
        if(i+temp[i]-1>max_right)
            {max_right=i+temp[i]-1;
            pos=i;}
        if(res<temp[i])
        {
            res=temp[i];
            res_pos=i;
        }
    }
    return s.substr((res_pos-res+1)/2,res-1);
}
};
```

![点击并拖拽以移动](data:image/gif;base64,R0lGODlhAQABAPABAP///wAAACH5BAEKAAAALAAAAAABAAEAAAICRAEAOw==)