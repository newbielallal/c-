---
title: leetcode 45 跳跃游戏Ⅱ
tags:
  - c++ 
categories: c++ 
---

第一种思路果然超时了。
<!-- more -->

### 题目

给定一个非负整数数组，你最初位于数组的第一个位置。

数组中的每个元素代表你在该位置可以跳跃的最大长度。

你的目标是使用最少的跳跃次数到达数组的最后一个位置。

示例:

输入: [2,3,1,1,4]
输出: 2
解释: 跳到最后一个位置的最小跳跃数是 2。
     从下标为 0 跳到下标为 1 的位置，跳 1 步，然后跳 3 步到达数组的最后一个位置。
说明:

假设你总是可以到达数组的最后一个位置。


### 思路

开始想的比较简单，就用动态规划呗，两重循环，dp记录下到达每个位置所用的步数，然后当前dp的值就是能够到达自己这个位置的例如说j的步数加1，dp[i]=dp[j]+1,在nums[j]能够一步到达nums[i]且dp[j]是所有能够一步到达nums[i]中所用步数最少的那个（j<i），但是不出意外，还是超时了，最后一个测试用例没过，显然是专门设置的。

### code

	class Solution {
	public:
	    int jump(vector<int>& nums) {
	        if(nums.size()==0)
	            return 0;
	        vector<int>dp(nums.size(),nums.size()-1);
	        dp[0]=0;
	        for(int i=0;i<nums.size();++i)
	        {
	            for(int j=0;j<i;++j)
	            {
	                if((i-j<=nums[j]))
	                {
	                    dp[i]=min(dp[i],dp[j]+1);
	                }
	            }
	        }
	        return dp.back();
	
	    }
	};

### 思路

这个有点像贪婪算法，每次都走到下一步能走到最远最远的地方的那一个位置，然后这样算下来肯定走的步数是最少的。
### code

	class Solution {
	public:
	    int jump(vector<int>& nums) {
	        int i = 0, j = 1, steps = 0, n = nums.size();
	        while(j < n)
	        {
	            int end = min(nums[i] + i + 1, n);//从0开始的，所以要加1，end代表从i出发，一步能走到的最远的位置，
	            while(j < end)//找出范围内哪个位置的下一步能走到最远位置的，然后它就是这一步要走到的地方。
	            {
	                if(nums[j] + j > nums[i] + i )//如果j的位置能到达的最远位置大于i的位置能够到达的最远位置，
                      //那么就走到j那个地方去，所以将i赋值为j。
	                     i = j;
	                j ++;//继续往后遍历。
	            }
	            steps ++;//找到最大位置之后，i走到那个地方，步数加一。
	        }
	        return steps;
	    }
	};