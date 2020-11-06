**###题目**

给定一个无序的数组，找出数组在排序之后，相邻元素之间最大的差值。

如果数组元素个数小于 2，则返回 0。

说明：

- 你可以假设数组中所有元素都是非负整数，且数值在 32 位有符号整数范围内。
- **请尝试在线性时间复杂度和空间复杂度的条件下解决此问题。**

**###思路**

题目要求线性时间复杂度，肯定不能用排序算法的，所以就是我不会的，直接看的官方题解。原理是鸽笼原理，可以将数据分别都放在桶里。

![img](https://pic4.zhimg.com/80/v2-529467596b61014e74ee0fa4e5dbb8bf_720w.jpg)

然后所有相邻桶的前一个桶的最大值与后一个桶的最小值的差的最大值就是相邻的元素的最大差值，比如上面这个图相邻桶的最大值与最小值的差就是8-3=5，最后的答案也是5.

只需要保证以下的一个点就可以了：

1、桶内相邻元素的差值必须要小于相邻桶之间最大值与最小值的差。

这样相当于原来是要将整个数组排序，现在不用了，现在不用保证桶内元素有序，只用保证桶间有序即可，相当于宏观上的有序。

那如何保证上面提到的那一点呢？

这就取决于桶的范围了，例如上面那张图，第0个桶的范围是1~2，第1个桶的范围是3~4，第2个桶的范围是5~6，第3个桶的范围是7~8，第4个桶的范围是9~10。

桶的范围如果过大，比如等于8，那么就会变成1，2，8和9，这样的出来的结果就是1。

桶的范围如果为1，那么就是每一个数一个桶，需要更多的桶去存储，很费空间，此外桶增多了，比较的次数也会增多。

桶的范围为1肯定是没问题的，但是为了节约空间，要找出一个最大的间距同时又能保证桶内元素的值的间距不会大于桶外元素的间距。

选择的桶的间距是 ![[公式]](https://www.zhihu.com/equation?tex=bucketSize+%3D+%28maxNums+-+minNums%29%2F%28l-1%29%3B) bucketSize的意思是nums中每相连的两个数差值的最终平均差，而我们要求的是nums里面相连两个数最大差值，所以一般情况下不是桶的容量也就不可能出现在桶的内部，因为一个小了，另一个必定就大了，除非当nums里面元素是均匀的，但是此时的最大间距就是桶容量，每个元素会分一个桶，也不会错。

知道桶的范围，那么就求桶的个数了， ![[公式]](https://www.zhihu.com/equation?tex=bucketNum+%3D+%28maxNums+-+minNums%29%2FbucketSize+%2B+1%3B) 桶的个数还要加一的原因是为了避免半开半闭区间导致最后极值还要单独处理。

后面的就是求出每个数在哪个桶里面，然后在保留每个桶内元素的最大值与最小值用于最后的比较即可。

**###code**

```cpp
class Solution {
public:
    struct BUCKET
    {
        bool vali = 0;
        int maxNum=INT_MIN;
        int minNum=INT_MAX;
    };
    int maximumGap(vector<int>& nums) {
        int l=nums.size();
        if(l<2)return 0;
        int res=0;
        int maxNums=*max_element(nums.begin(), nums.end());
        int minNums=*min_element(nums.begin(), nums.end());
        int bucketSize = (maxNums - minNums)/(l-1);
        if(bucketSize == 0)
        {
            bucketSize = 1;
        }
        int bucketNum = (maxNums - minNums)/bucketSize + 1;
        vector<BUCKET>bucket(bucketNum);

        for(int i=0; i<l; ++i)
        {
            int position = (nums[i] - minNums)/bucketSize;
            bucket[position].vali = 1;
            bucket[position].maxNum = max(nums[i],bucket[position].maxNum);
            bucket[position].minNum = min(nums[i],bucket[position].minNum);
        }

        int pre = bucket[0].maxNum;
        for(int i=1;i<bucketNum;++i)
        {
            if(bucket[i].vali == 0)
            {
                continue;
            }
            res= max(res, (bucket[i].minNum - pre));
            pre= bucket[i].maxNum;
        }
        return res;
    }
};
```