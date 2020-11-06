**###题目**

给定一个**非空**二叉树，返回其最大路径和。

本题中，路径被定义为一条从树中任意节点出发，达到任意节点的序列。该路径**至少包含一个**节点，且不一定经过根节点。

**###思路**

题目要求是最大最路径和即可，而且并不需要包含多少节点，也对路径中的节点没有要求，所以可以只包含一个节点，因为最后得到的最大路径和肯定是会包含一个节点的，那么就求出二叉树中每个节点的最大路径和，取其中的最大值作为最后的结果，对于某个节点temp，其有以下几种情况：

- 左子节点存在，从其中得到的最大路径和大于0，那么带上左子节点才能得到最大路径和，若不大于0或者左子节点不存在最大路径直接不包含左节点。
- 右子节点存在，从其中得到的最大路径和大于0，那么带上右子节点才能得到最大路径和，若不大于0或者右子节点不存在最大路径直接不包含左节点。

通过上述两步得到temp节点的最大路径和，然后与历史最大路径和做比较进行更新。

因为temp节点不一定是根节点，当它为其祖先节点的路径时，不可能路径中同时包含它左右子节点所在的路径，所以将temp左右子节点中得到更大的那条路径返回上去，给temp的祖先节点做路径，这样得到的就是祖先节点在路径中有temp时的最大路径和。

这里面的难点就是如何判断每个节点的左右子节点能够得到的最大路径和，但是通过递归可以很简单的解决这个问题，具体可以看代码注释。

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
    int max_res(TreeNode* root,int& res)
    {
        if(root==NULL)return 0;
        //找出左子节点能表示的最大路径，若为负数直接不要左边分支
        int left=max(0,max_res(root->left,res));
        //找出右子节点能表示的最大路径，若为负数直接不要右边分支
        int right=max(0,max_res(root->right,res));
        //得到包含当前节点的最大路径和
        int temp=root->val+left+right;
        //与历史结果比较并更新历史结果
        res=max(res,temp);
        //返回当前节点更大的那条分支给祖先节点。
        return root->val+max(left,right);
    }
    int maxPathSum(TreeNode* root) {
        int res=INT_MIN;
        max_res(root,res);
        return res;
    }
};
```