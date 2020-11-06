**###题目**

给定一组不含重复元素的整数数组 nums，返回该数组所有可能的子集。**说明：解集不能包含重复的子集。**

- 输入：nums = [1,2,3]
- 输出：[[3],[1],[2],[1,2,3],[1,3],[2,3],[1,2],[]]

**###思路**

题目说了数组中无重复元素，那么最基本的回溯法就可以了。假设nums的长度为k，那么以长度限制为 ![img](https://mmbiz.qpic.cn/mmbiz_svg/bj9JGugn6UeichWGHZwfNPoib4fAl3rFObqExiaP8GNmVTRic3x1hknrqt7b6r4LcdlmFVvYqP01YA78B0uUEAk5RA5cibRvhwicHx/640?wx_fmt=svg&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1) 分别进行回溯找出长度为 ![img](https://mmbiz.qpic.cn/mmbiz_svg/bj9JGugn6UeichWGHZwfNPoib4fAl3rFObqExiaP8GNmVTRic3x1hknrqt7b6r4LcdlmFVvYqP01YA78B0uUEAk5RA5cibRvhwicHx/640?wx_fmt=svg&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1) 的所有子串，最后再加上一个空的集合就写出了所有的子集。

**###code**

```
class Solution {
public:
void huishu(vector<vector<int>>&res, int k,vector<int>&nums,int l,int begin,vector<int>&temp)
{
    if(temp.size()==k)
        res.push_back(temp);
    for(int i=begin;i<nums.size();++i)//回溯
    {
        temp.push_back(nums[i]);
        huishu(res,k,nums,l+1,i+1,temp);
        temp.pop_back();
    }
    return;
}
vector<vector<int>> subsets(vector<int>& nums) {
    if(nums.size()==0)return {};
    vector<vector<int>>res;
    for(int i=1;i<=nums.size();++i)//1-k回溯
    {
        vector<int> temp;
        huishu(res,i,nums,0,0,temp);
    }
    res.push_back({});
    return res;
}
};
```

**###思路**

该方法思路来自于Donald E. Knuth。长度为n的数组一共有 ![img](https://mmbiz.qpic.cn/mmbiz_svg/bj9JGugn6UeichWGHZwfNPoib4fAl3rFObPZK53gRA31j8hiaPGiaGmwcWwhKWaxUDJlHnYibeho5jaL5JyQhCDRKE7ZicqXcqzPDia/640?wx_fmt=svg&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1) 个子集，那么其实每个子集都可以映射到一个长度为n的位掩码中(位掩码只包含0、1)。

- 其中第 i 位掩码为1，表示nums[i]在子集中；
- 其中第 i 位掩码为0，表示nums[i]不在子集中；

![img](https://mmbiz.qpic.cn/mmbiz_svg/bj9JGugn6UeichWGHZwfNPoib4fAl3rFObPZK53gRA31j8hiaPGiaGmwcWwhKWaxUDJlHnYibeho5jaL5JyQhCDRKE7ZicqXcqzPDia/640?wx_fmt=svg&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1) 个掩码其实就是0到 ![img](https://mmbiz.qpic.cn/mmbiz_svg/bj9JGugn6UeichWGHZwfNPoib4fAl3rFObPZK53gRA31j8hiaPGiaGmwcWwhKWaxUDJlHnYibeho5jaL5JyQhCDRKE7ZicqXcqzPDia/640?wx_fmt=svg&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1) (左闭右开)这些数将其化成一个长度为n二进制表达，然后按照上面的两条规则来确定nums[i]是否在子集中。

例如：nums=[1,2]，那么n=2，四个子集的序号为0、1、2、3,掩码为00、01、10、11。相应的就得到了子集：{}、{2}、{1}、{1,2}。

**###code**

```
class Solution {
public:
vector<vector<int>> subsets(vector<int>& nums) {
    long long n=pow(2,nums.size());
    vector<vector<int>>res;
    for(int i=0;i<n;++i)//将这些掩码挨个进行处理
    {
        vector<int>temp_num;
        long long temp=1;
        for(int j=0;j<nums.size();++j)
        {
            if(temp&i) temp_num.push_back(nums[j]);//对每一位进行与操作，为1就添加。
            temp=temp<<1;//temp除去进行与操作的那一位其它都为0.
        }
        res.push_back(temp_num);
    }
    return res;
}
};
```

