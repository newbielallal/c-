---
title: leetcode 18 四数之和 
tags:
  - c++ 
categories: c++ 
---
和三数之和的思路是一样的。
<!-- more -->

### 题目

给定一个包含 n 个整数的数组 nums 和一个目标值 target，判断 nums 中是否存在四个元素 a，b，c 和 d ，使得 a + b + c + d 的值与 target 相等？找出所有满足条件且不重复的四元组。

注意：

答案中不可以包含重复的四元组。

示例：

给定数组 nums = [1, 0, -1, 0, -2, 2]，和 target = 0。

满足要求的四元组集合为：
[
  [-1,  0, 0, 1],
  [-2, -1, 1, 2],
  [-2,  0, 0, 2]
]

### 思路

和三数之和一样的，首先将数组进行排序，其次选择第一个数固定住，然后后面三个数进行移动，例如此时此刻选择的第一个数的下标是i，那么第二个数下标则是i+1，第三个是i+2，第四个就是nums.size()-1，然后就和三数之和一样了，如果四个数相加结果大于target，那么就将第四个数的下标减一，如果小于target，就将第三个数的下标加一，这样进行遍历，直到最后第三个数的下标大于等于第四个数的下标，此时不算直接结束，将第二个数的下标加一，继续进行一样的遍历，第二个数的下标直到到达nums.size()-3截止，然后将第一个数的下标加一，继续进行上述的遍历循环，所以综上，程序的时间复杂度是N^3。
而且这个思路可以扩展到k个数的和，同样是先排好序，然后确定第一个数的下标，第二个数的下标，第三个数的下标，.......一直到第k个数为nums.size()-1，然后依然是根据k个数相加的和来进行第k个数和第k-1个数的下标的移动方式，等到第k-1和第k个数的下标相交之后，再将第k-2个数的下标加一，继续进行上面的遍历，第k-2个数的下标加一到达可以到达的最大值之后，再将第k-3个数的下标加一进行同样的循环运算。所以复杂度为N^(k-1)，只是过程中同样要注意不得重复。

### code

     class Solution{
		public: 
		vector<vector<int>> fourSum(vector<int>& nums, int target) {
	        //三数之和的进阶版本
	        sort(nums.begin(),nums.end());
	        vector<vector<int> > res;
	        if(nums.size()<4)
	            return res;
	        int a,b,c,d,l=nums.size();
	        for(a=0;a<=l-4;a++){
	        	if(a==0||nums[a]!=nums[a-1]) {     //防止重复
	        	for(b=a+1;b<=l-3;b++){
	        		if(b==a+1||nums[b]!=nums[b-1]){ //防止重复
	        		c=b+1,d=l-1;
	        		while(c<d){
	        			if(nums[a]+nums[b]+nums[c]+nums[d]<target)
	        			    c++;
	        			else if(nums[a]+nums[b]+nums[c]+nums[d]>target)
	        			    d--;
	        			else{
	        				res.push_back({nums[a],nums[b],nums[c],nums[d]});
	                        c++;
	        				d--;
	        				while(c<d&&nums[c-1]==nums[c])      //防止重复
	        				    c++;
	        				while(c<d&&nums[d+1]==nums[d])      //防止重复
	        				    d--;
	        				
						}
					}
	                }
				}
	            }
			}
			return res;
	    }
	};