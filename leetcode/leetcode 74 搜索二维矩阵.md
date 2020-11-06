**###题目**

编写一个高效的算法来判断 m x n 矩阵中，是否存在一个目标值。该矩阵具有如下特性：

- 每行中的整数从左到右按升序排列。
- 每行的第一个整数大于前一行的最后一个整数。

**###思路**

题目要求高效的算法，那就是说要利用数组内部元素排列的特点了，这个![img](https://mmbiz.qpic.cn/mmbiz_svg/bj9JGugn6UeichWGHZwfNPrwsZ21nrgbJ5gPmwf0gibMewfwpn6mUKjITP4TmOUoDbXCjXYrnxsuLibXSqnelHz2KXzywv2Fj9h/640?wx_fmt=svg&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1)的矩阵可以看做一个有序的 ![img](https://mmbiz.qpic.cn/mmbiz_svg/bj9JGugn6UeichWGHZwfNPrwsZ21nrgbJ5gPmwf0gibMewfwpn6mUKjITP4TmOUoDbXCjXYrnxsuLibXSqnelHz2KXzywv2Fj9h/640?wx_fmt=svg&tp=webp&wxfrom=5&wx_lazy=1&wx_co=1) 一维数组.所以明显可以利用二分法，只是如何将mid转换成在matrix中的下标(i,j)就可以了：

- i=mid/matrix[0].size()
- j=mid%matrix[0].size()

**###code**

```
class Solution {
public:
bool searchMatrix(vector<vector<int>>& matrix, int target) {
    if(matrix.empty()) return false;
    int l1=matrix.size(),l2=matrix[0].size();
    int left = 0, right =l1*l2-1;
    while (left <= right) 
    {
        int mid =((right-left)>>1)+left;
        if (target == matrix[mid/l2][mid%l2]) return true;
        else if (target < matrix[mid/l2][mid%l2]) right = mid - 1;
        else left = mid + 1;
    
    }
    return false;
}
};
```

**###思路**

从第0行开始比较行尾数字与target的大小，分三种情况：

- 等于target，那么返回true
- 如果行尾的数字大于target，那么说明下面所有行的元素都大于target，所以比较行尾前一个数字，依次往回找，如果这一行都没有找到，那么输出false
- 如果行尾数字小于target，继续往下一行找

**###code**

```

class Solution {
public:
bool searchMatrix(vector<vector<int>>& matrix, int target) {
    if(matrix.empty()) return false;
    int l1=matrix.size(),l2=matrix[0].size();
    int row=0;
    int col=l2-1;
    while(row<l1 && col>=0)
    {
        if(matrix[row][col]==target)    //返回true
        {
            return true;
        }
        else if(matrix[row][col]>target)   //比target大，此时当前列不符合条件，往回一列
              --col;
        else //比target小,往下一行寻找
            ++row;
    }
    return false;
}
};
```

