**###题目**

假设按照升序排序的数组在预先未知的某个点上进行了旋转。( 例如，数组 [0,1,2,4,5,6,7] 可能变为 [4,5,6,7,0,1,2] )。请找出其中最小的元素。**注意数组中可能存在重复的元素。**

- 输入: [1,3,5]
- 输出: 1
- 输入: [2,2,2,0,1]
- 输出: 0

**###思路**

题目是在第153题的基础上延展来的。

不同的地方是在数组中加入了重复的数字，这样上一题使用的方法就不行了，因为假如有旋转后的数组[4,4,4,1,4,4,4]，这样在 ![[公式]](https://www.zhihu.com/equation?tex=nums%5Bmid%5D%3D%3Dtarget) 的时候无法判断mid是在最大值的左边还是右边，所以失效，本题采用的方法依然是二分法，具体如下：

1. 首先申明变量l=0、r=numsSize-1代表二分的左右边界。
2. 然后比较mid的值与nums[r]的大小，分三种情况：

- nums[mid]>nums[r]，代表此时在右边那个有序的序列中，但mid可能是最小值，所以r=mid。
- nums[mid]<nums[r]，代表此时在左边那个有序的序列中，所以l=mid+1。
- nums[mid]=nums[r]，此时无法判断处于哪个序列中，但是最小值肯定是在l与r之间的，所以直接r=r-1，缩小范围，最后在找到最小值的情况下，r=r-1也可以跳出循环。

最后输出nums[l]即可。

**###code**

```c
int findMin(int* nums, int numsSize){
        int l = 0, r = numsSize-1;
        while(l < r)
        {
            int mid=l + ((r - l) >> 1);
            if(nums[mid] > nums[r])
                l = mid+1;
            else if( nums[mid] < nums[r])
                r = mid;
            else
                r = r-1;
        }
        return nums[l];
}
```