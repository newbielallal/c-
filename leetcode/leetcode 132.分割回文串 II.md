**###题目**

给定一个字符串 *s*，将 *s* 分割成一些子串，使每个子串都是回文串。

返回符合要求的最少分割次数。

- 输入："aab"
- 输出：1

**###思路**

最开始用的暴力法超时了，二维动态规划也挺慢的，这个方法是从评论区找的。

首先建立一个数组huafen用来记录划分次数，数组的长度为s.size()+1，其中huafen[i]代表的是s从下标0开始的长度为i的子数组的最少划分次数。

在最开始不知道最少划分次数的时候首先对huafen数组进行初始化，初始化规则为：

- 1个字符最多划分0次
- 2个字符最多划分1次
- 3个字符最多划分2次
- ..........
- n个字符最多划分n-1次
- 故 ![[公式]](https://www.zhihu.com/equation?tex=huafen%5Bi%5D%3Di-1%3B)

下一步就是开始更新huafen数组，更新规则为：

- 遍历s中的每个字符s[i]，同时更新huafen[i+1]。
- 首先 ![[公式]](https://www.zhihu.com/equation?tex=huafen%5Bi%2B1%5D%3Dmin%28huafen%5Bi%2B1%5D%2Chuafen%5Bi%5D%2B1%29%3B) 因为i+1长度的子字符串肯定是可以分割为i长度子字符串和一个单独的字符的。
- 然后以s[i]为中心，以奇数长度回文和偶数长度回文开始扩展找最长回文字符串，每找到一个回文串就更新一次huafen数组：![[公式]](https://www.zhihu.com/equation?tex=huafen%5Bright%2B1%5D%3Dmin%28huafen%5Bright%2B1%5D%2Chuafen%5Bleft%5D%2B1%29%3B)
- 最后输出huafen.back()即可。

以字符串aaffdds举例，huafen数组的更新过程为：

- -1 0 1 2 3 4 5 6
- -1 0 0 2 3 4 5 6
- -1 0 0 2 3 4 5 6
- -1 0 0 1 1 4 5 6
- -1 0 0 1 1 4 5 6
- -1 0 0 1 1 2 2 6
- -1 0 0 1 1 2 2 6
- -1 0 0 1 1 2 2 3

**###code**

```cpp
class Solution {
public:
    int minCut(string s) {
        vector<int>huafen(s.size()+1);
        for(int i=0;i<huafen.size();++i)
            huafen[i]=i-1;
        for(int i=0;i<s.size();++i)
        {
            huafen[i+1]=min(huafen[i+1],huafen[i]+1);
            if(i==s.size()-1)break;
            int left=i,right=i+1;
            while(s[left]==s[right])
            {
                huafen[right+1]=min(huafen[right+1],huafen[left]+1);
                if(left==0||right==s.size()-1)break;
                left--;
                right++;
            }
            left=i-1;
            right=i+1;
            if(left<0)continue;
            while(s[left]==s[right])
            {
                 huafen[right+1] = min(huafen[right+1], huafen[left]+1);
                if(right == s.size()-1 || left == 0){
                    break;
                }
                --left;
                ++right;
            }
            if(huafen.back()==0)return 0;
        }
        return huafen.back();
    }
};
```