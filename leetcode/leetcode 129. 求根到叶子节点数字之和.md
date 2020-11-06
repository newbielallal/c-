**###题目**

给定一个二叉树，它的每个结点都存放一个 0-9 的数字，每条从根到叶子节点的路径都代表一个数字。

例如，从根到叶子节点路径 1->2->3 代表数字 123。

计算从根到叶子节点生成的所有数字之和。

说明: 叶子节点是指没有子节点的节点。

**###思路**

思路比较简单，就是一路向下，找到叶子节点，然后计算这一路的节点组成得数字，例如

![img](https://pic1.zhimg.com/80/v2-fbcd41cda3ade17c6aec2656bff57a18_720w.jpg)

- 从4出发，4存在左子节点，那么记下数字49。
- 4存在右子节点，记下数字40，右子节点为叶子节点，将40加到最后得结果当中。
- 再从9这个节点出发，存在左孩子，记下数字495，9的左孩子为叶子节点，将495加到最后得结果中。
- 9这个节点出发，存在右孩子，记下数字491，9的右孩子为叶子节点，将491加到最后得结果中。
- 所有节点遍历结束，得到最后结果。

**###code**

```cpp
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
    void qiuhe(int& res,TreeNode* root,int num)
    {
        if(root->left==NULL&&root->right==NULL)
        {
            res+=num*10+root->val;
            return ;
        }
        if(root->left)
            qiuhe(res,root->left,num*10+root->val);
        if(root->right)
            qiuhe(res,root->right,num*10+root->val);
        return;
    }
    int sumNumbers(TreeNode* root) {
        int res=0;
        if(root==NULL)return res;
        int num=0;
        qiuhe(res,root,num);
        return res;
    }
};
```