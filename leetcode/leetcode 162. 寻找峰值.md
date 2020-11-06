**###题目**

峰值元素是指其值大于左右相邻值的元素。

给定一个输入数组 nums，其中 nums[i] ≠ nums[i+1]，找到峰值元素并返回其索引。

数组可能包含多个峰值，在这种情况下，返回任何一个峰值所在位置即可。

你可以假设 nums[-1] = nums[n] = -∞。

- 输入: nums = [1,2,3,1]
- 输出: 2
- 输入: nums = [1,2,1,3,5,6,4]
- 输出: 1 或 5

**###思路**

这个题目最主要的是要搞清楚一点，由于 ![[公式]](https://www.zhihu.com/equation?tex=nums%5Bi%5D+%E2%89%A0+nums%5Bi%2B1%5D) ，所以数组的相邻元素大小之间一定存在一个趋势，这个趋势是上升或者下降的，上升趋势的终点，下降趋势的起点都是一个峰值，所以只要找出这两种点就可以了，这两种点其实也是一类点，因为假设nums[-1] = nums[n] = -∞，所以上升趋势的终点就是下降趋势的起点，题目要求 ![[公式]](https://www.zhihu.com/equation?tex=logn) 的时间复杂度，所以大概率是二分查找。

**###code**

```c
int findPeakElement(int* nums, int numsSize)
{  
    int left = 0, right = numsSize-1;

    while (left < right)
    {
        int mid = left + ((right - left)>>1);
        /*说明nums[mid]与nums[mid+1]组成了一个下降序列，去寻找它的起点*/
        if (nums[mid] > nums[mid+1])
        {
            right = mid;
        }
        /*说明nums[mid]与nums[mid+1]组成了一个上升序列，去寻找它的终点*/
        else 
        {
            left = mid + 1;
        }
    }
    return left;
}
```