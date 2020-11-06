**###题目**

给你一个整数数组 nums ，请你找出数组中乘积最大的连续子数组（该子数组中至少包含一个数字），并返回该子数组所对应的乘积。

- 输入: [2,3,-2,4]
- 输出: 6
- 解释: 子数组 [2,3] 有最大乘积 6。



- 输入: [-2,0,-1]
- 输出: 0
- 解释: 结果不能为 2, 因为 [-2,-1] 不是子数组。

**###思路**

这种求最值的问题，大部分都是动态规划。这个题也确实是使用动态规划，动态规划最重要的就是设置动态转移方程：

设置dp矩阵**max_product**，其中**max_product[i]**代表以**nums[i]**为结尾的子数组的最大乘积。最后输出**max_product**的最大值即可。那怎么更新**max_product**呢？

![[公式]](https://www.zhihu.com/equation?tex=max_product%3Dmax%28nums%5Bindex%5D%2Cnums%5Bindex%5D%2Amax_product%5Bindex-1%5D%29)

这个式子很好理解，以**nums[i]**为结尾的子数组的最大乘积要么是**nums[i]**自身，要么是nums[i]乘上前面的元素，所以就直接让**nums[i]\*max_product[i-1]**与**nums[i]**进行比较即可。

但是有一个问题就是nums中存在**负数**，负负得正的情况下，上述的矩阵每次都在找最大的，如果有 ：负 正 负。这种情况，答案就会错，所以添加一个**min_product**矩阵用来记录最小的乘积。每次max_product[i]更新的时候还要和nums[i]*前面最小的乘积做比较，这样当nums[i]是一个负数的时候，如果前面的最小乘积也是负数，那么负负得正说不定可以得到一个更大的值，所以最后**max_product**的更新规则修改为：

![[公式]](https://www.zhihu.com/equation?tex=max_product%5Bindex%5D%3D+max%28nums%5Bindex%5D%2C+max%28nums%5Bindex%5D%2Amax_product%5Bindex-1%5D%2Cnums%5Bindex%5D%2Amin_product%5Bindex-1%5D%29%29%3B)

**###code**

```cpp
class Solution {
public:
    int maxProduct(vector<int>& nums) {
        int len_nums = nums.size();
        vector<int>max_product(len_nums,nums[0]);
        vector<int>min_product(len_nums,nums[0]);

        for(int index = 1; index<len_nums; ++index)
        {
            max_product[index]= max(nums[index],
            max(nums[index]*max_product[index-1],nums[index]*min_product[index-1]));
            min_product[index]= min(nums[index],
            min(nums[index]*max_product[index-1],nums[index]*min_product[index-1]));
        }
        return *max_element(max_product.begin(),max_product.end());
    }
};
```

**###思路**

观察第一种方法中**max_product**以及**min_product**的更新代码：

![[公式]](https://www.zhihu.com/equation?tex=max_product%5Bindex%5D%3D+max%28nums%5Bindex%5D%2C+++++++++++++max%28nums%5Bindex%5D%2Amax_product%5Bindex-1%5D%2Cnums%5Bindex%5D%2Amin_product%5Bindex-1%5D%29%29%3B+++++++++++++)

![[公式]](https://www.zhihu.com/equation?tex=min_product%5Bindex%5D%3D+min%28nums%5Bindex%5D%2C+++++++++++++min%28nums%5Bindex%5D%2Amax_product%5Bindex-1%5D%2Cnums%5Bindex%5D%2Amin_product%5Bindex-1%5D%29%29%3B)

很明显的发现在更新过程中并不需要整个max_product以及整个min_product，只是需要一个**min_product[index-1]**以及**max_product[index-1]**。那么完全可以不用一个数组来存储信息，只需要两个变量分别存储min_product[index-1]以及max_product[index-1]，并且在循环过程中不断更新就可以了，所以代码可以修改如下。

**###code**

```cpp
class Solution {
public:
    int maxProduct(vector<int>& nums) {
        int max_product=nums[0];
        int max_product_temp=nums[0];
        int min_product_temp=nums[0];

        for(int index=1;index<nums.size();++index)
        {
            int a=max_product_temp;
            //max_product会被覆盖，所以要先保存下来。
            max_product_temp= max(nums[index],
            max(nums[index]*max_product_temp,nums[index]*min_product_temp));
            min_product_temp= min(nums[index],
            min(nums[index]*a,nums[index]*min_product_temp));
            if(max_product_temp>max_product)max_product=max_product_temp;
        }       
        return max_product;
    }
};
```