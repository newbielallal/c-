**###第一题**

给你一份旅游线路图，该线路图中的旅行线路用数组 paths 表示，其中 paths[i] = [cityAi, cityBi] 表示该线路将会从 cityAi 直接前往 cityBi 。请你找出这次旅行的终点站，即没有任何可以通往其他城市的线路的城市。

**题目数据保证线路图会形成一条不存在循环的线路，因此只会有一个旅行终点站。**

- 输入：paths = [["London","New York"],["New York","Lima"],["Lima","Sao Paulo"]]
- 输出："Sao Paulo"
- 输入：paths = [["B","C"],["D","B"],["C","A"]]
- 输出："A"
- 输入：paths = [["A","Z"]]
- 输出："Z"

**###思路**

因为题目保证不会存在循环的线路，所以直接用的暴力法，直接判断paths中的每个字符串的终点字符串是否是其它字符串的起点字符串，如果不是就直接输出结果。

**###code**

```cpp
class Solution {
public:
    string destCity(vector<vector<string>>& paths) {
        string end="";
        for(int i=0;i<paths.size();++i)
        {
            string temp=paths[i][1];
            int j=0;
            for(;j<paths.size();++j)
            {
                if(paths[j][0]==temp)
                    break;
            }
            if(j==paths.size())
                return temp;

        }
        return "";
    }
};
```

**###第二题**

给你一个由若干`0`和`1`组成的数组`nums`以及整数`k`。如果所有`1`都至少相隔`k`个元素，则返回`True`；否则，返回`False`。

- 输入：nums = [1,0,0,0,1,0,0,1], k = 2
- 输出：true

**###思路**

这个题目还比较简单，如果是每两个相邻的1都满足相隔至少k个元素的要求，那么由他们组成的数组肯定也是满足这个要求的，所以只需要判断数组中的第一个1与第二个1、第二个1与第三个1、第n-1个1与第n个1是否都满足情况即可。

**###code**

```cpp
class Solution {
public:
    bool kLengthApart(vector<int>& nums, int k) {
        for(int i=0;i<nums.size();++i)
        {
            if(nums[i]==1)
            {
                for(int j=i+1;j<nums.size();++j)
                {
                    if(nums[j]==1)
                    {
                        if(j-i-1<k)
                            return false;
                        else
                            break;
                    }
                }

            }
        }
        return true;
    }
};
```

**###第三题**

给你一个整数数组 nums ，和一个表示限制的整数 limit，请你返回最长连续子数组的长度，该子数组中的任意两个元素之间的绝对差必须小于或者等于 limit 。

如果不存在满足条件的子数组，则返回 0 。

- 输入：nums = [8,2,4,7], limit = 4
- 输出：2

**###思路**

最开始用的暴力法，从nums[0]开始，一直到nums[i]，找出每个起始的最长的满足要求的连续子数组，当然是超时了，所以就换成一个滑动窗的方法了，具体思路为：

- 设置left、right代表滑动窗口的左边和右边，res代表最长子数组的长度。
- 用min_num、max_num表示窗口内的最大值和最小值，一直更新，若最大值和最小值的差满足要求，那么right往前走，更新res。
- 如果最大值和最小值之差不满足情况，那么代表right往前走之后加入的新的元素过大或者过小，此时我们需要更新滑动窗口。
- 更新的方法是首先将left的值修改为right，然后将left--再看abs(nums[right]-nums[left])的值满足要求不，这里不弄成max_num-min_num的原因主要是需要回溯left，这样可以避免不正确的更改max_num、min_num。这一步的目的是为了得到一nums[right]为右边界的最大满足情况的连续子数组。
- 得到满足要求的子数组后，滑动窗的右边然后又按照同样的规则继续往右走。
- 最后输出res。

**###code**

```cpp
class Solution {
public:
    int longestSubarray(vector<int>& nums, int limit) {
        int left = 0;
        int right = 0;
        int res = 0;
        int min_num= nums[0];
        int max_num = nums[0];
        for(int right=0; right<nums.size(); ++right){
            
            min_num = min(min_num, nums[right]);
            max_num = max(max_num, nums[right]);
            
            if(max_num-min_num<=limit){
                res = max(res,right-left+1);
            }
            else{
                min_num=nums[right];
                max_num=nums[right];
                left=right;
                while(limit>=abs(nums[right]-nums[left])){
                    min_num = min(min_num, nums[left]);
                    max_num = max(max_num, nums[left]);
                    left--;
                }
                left++;
            }
        }
        return res;
    }
};
```

**###第四题**

给你一个 m * n 的矩阵 mat，以及一个整数 k ，矩阵中的每一行都以非递减的顺序排列。

你可以从每一行中选出 1 个元素形成一个数组。返回所有可能数组中的第k个最小数组和。

- 输入：mat = [[1,3,11],[2,4,6]], k = 5
- 输出：7

**###思路**

用的是暴力法的方法来处理，下来之后看了评论区别人的，感觉简洁很多，就修改了一下代码。具体思路就是一行一行的对这个矩阵进行处理。

首先假设如果矩阵mat只有一行，那么整个最后得到的数组和其实就是mat[0]。

现在假设mat有两行，那么最后的数组和就是mat[0]中的元素分别加上mat[1]中的元素，这里可以做一个处理，用multiset来存储数组和，multiset是有序的，然后只取multiset的前k个数组和就行了，因为每一行取的元素都和其它行的是独立的，所以截取multiset中的前k个元素，其它的元素不要最后不影响结果。

然后利用这样的方法处理第三行、第四行、第n行，最后输出multiset的第k个元素就可以了。

**###code**

```cpp
class Solution {
public:
    int kthSmallest(vector<vector<int>>& mat, int k) {
        vector<int>res(mat[0].begin(),mat[0].end());//第一行
        for(int i=1;i<mat.size();++i)//按行处理
        {
            multiset<int>temp;//有序容器
            for(int j=0;j<res.size();++j)
            {
                for(int k=0;k<mat[0].size();++k)
                //将前i-1行得到的前k个数组和与第i行的元素分别相加。
                    temp.insert(res[j]+mat[i][k]);
            }
            //截取前k个和
            res.assign(temp.begin(),temp.end());
            res.resize(min(k,(int)res.size()));
        }
        return res.back();
    }
};
```