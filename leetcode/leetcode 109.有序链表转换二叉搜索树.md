**###题目**

给定一个单链表，其中的元素按升序排序，将其转换为高度平衡的二叉搜索树。本题中，一个高度平衡二叉树是指一个二叉树每个节点 的左右两个子树的高度差的绝对值不超过 1。

- 输入：[-10, -3, 0, 5, 9]
- 输出：

![img](https://pic2.zhimg.com/80/v2-2cdbc58f3dc57b7c09d6e98ab3293ab9_720w.jpg)

**###思路**

题目已经说了链表是一个有序链表，我们需要建立一个子树高度差绝对值不超过1的二叉搜索树，基于这一要求，采用如下的步骤建立这棵树：

- 通过快慢指针，找到链表的中间位置，如果链表的节点数为偶数，那么处于中间的第一个节点和第二个节点都可以。
- 以链表中间位置为根节点，将链表前半部分的值赋给该根节点的左子树，后边部分的值赋给该根节点的右子树，这样左子树的所有节点值小于根节点，右子树的所有节点值大于根节点，因为是链表中间位置，所以左右子树的节点数最多相差一，因为每次都是找的中间位置，所以构建的左右子树除了最深一层外都是满二叉树。由 ![[公式]](https://www.zhihu.com/equation?tex=log_%7B2%7D%5E%7Bn%2B1%7D+-+log_%7B2%7D%5E%7Bn%7D+%3C1) ，可以证明其高度相差不大于1.
- 对分出来的链表的部分也进行找中间位置，再分割左右子树这个操作，不断进行递归，直到处理完链表中所有节点即可。

具体情况结合注释。

**###code**

```cpp
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    TreeNode* sortedListToBST(ListNode* head) {
        if(head==NULL)return NULL;//处理完所有节点返回
        ListNode* fast=head;//快慢指针
        ListNode* slow=head;
        ListNode* pre=NULL;//用来断开链表
        while(fast&&fast->next)//找出链表的中间位置
        {
            fast=fast->next->next;
            pre=slow;
            slow=slow->next;
        }
        if(pre!=NULL)pre->next=NULL;//断开链表
        TreeNode* res=new TreeNode(slow->val);//设置根节点
        //将前半部分断开链表递归构建左子树
        res->left=sortedListToBST(slow==head ? NULL:head);
        //将后半部分断开链表递归构建右子树
        res->right=sortedListToBST(slow->next);
        return res;
    }
};
```

**###思路**

进行了优化，但是利用了更多的空间，将链表中的值用一个数组保存下来，这样每次寻找中间节点不需要在遍历链表，只需要将待处理的数组的长度除2即可，这样构造的二叉搜索树和第一种方法构造出排列不同，但是符合规则。

**###code**

```cpp
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    TreeNode* solve(vector<int>&num,int left,int right)
    {
        if(left>right) //递归出口
        {
            return NULL;
        }
        if(left==right)
        {
            TreeNode* res=new TreeNode(num[left]);
            return res;
        }
        int mid=(left+right)/2;//找中间位置
        TreeNode* res=new TreeNode(num[mid]);
        res->left=solve(num,left,mid-1);//将[left,mid-1]范围内的数组元素作为左子树
        res->right=solve(num,mid+1,right);//将[mid+1,right]范围内的数组元素作为右子树
        return res;
    }
    TreeNode* sortedListToBST(ListNode* head) {
        if(head==NULL)return NULL;
        vector<int>num;
        while(head)//记录下链表中的值。
        {
            num.push_back(head->val);
            head=head->next;
        }
        return solve(num,0,num.size()-1);;
    }
};
```