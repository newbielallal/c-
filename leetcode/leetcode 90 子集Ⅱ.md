**###题目**

给定一个可能包含重复元素的整数数组 *nums*，返回该数组所有可能的子集。

说明：解集不能包含重复的子集。

- 输入：[1,2,2]
- 输出：[[2],[1],[1,2,2],[2,2],[1,2],[]]

**###思路**

和第78题有一点不同，增加了重复元素。

但是本题依然可以利用回溯法。假设***nums***的长度为k，那么以长度限制为 ![img](https://mmbiz.qpic.cn/mmbiz_svg/bj9JGugn6UeichWGHZwfNPjhibOQpYu3AC5PfIDaicvpCmyKSTHN5ORsUjo4BQl4icL11dgA2IuMalnnrSWxNVXWsoyvrdX2nDibm/640?wx_fmt=svg&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1) 分别进行回溯法找出长度为 ![img](https://mmbiz.qpic.cn/mmbiz_svg/bj9JGugn6UeichWGHZwfNPjhibOQpYu3AC5PfIDaicvpCmyKSTHN5ORsUjo4BQl4icL11dgA2IuMalnnrSWxNVXWsoyvrdX2nDibm/640?wx_fmt=svg&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1) 的子串，最后添加上空和***nums\***就写出了所有的子集，不同的地方就是回溯的过程中不能添加上同样的数字，所以需要对***nums***提前进行排序，回溯到相邻的相同数字就直接跳过。

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
        if(i>begin&&nums[i]==nums[i-1])//重复元素跳过
            continue;
        temp.push_back(nums[i]);
        huishu(res,k,nums,l+1,i+1,temp);
        temp.pop_back();
    }
    return;
}
vector<vector<int>> subsetsWithDup(vector<int>& nums) {
    if(nums.size()==0)return {};
    vector<vector<int>>res;
    sort(nums.begin(),nums.end());
    for(int i=1;i<nums.size();++i)//1-k回溯
    {
        vector<int> temp;
        huishu(res,i,nums,0,0,temp);
    }
    res.push_back({});
    res.push_back(nums);
    return res;
}
};
```

