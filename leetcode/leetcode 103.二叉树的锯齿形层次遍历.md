**###题目**

给定一个二叉树，返回其节点值的锯齿形层次遍历。（即先从左往右，再从右往左进行下一层遍历，以此类推，层与层之间交替进行）。

- 输入：

![img](https://pic4.zhimg.com/80/v2-12869cb6efa1977950e06cb3aacd875b_720w.jpg)

- 输出：[ [3],[20,9],[15,7]]

**###思路**

和上一题一样的，开始还想着要不要用两个队列来分别存储，突然觉得自己真是白痴，直接加一个树的深度判断，偶数深度的时候直接对存储遍历节点值的数组加上一个反转不就行了嘛。

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
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        queue<TreeNode*>q;
        if(root==NULL)return {};
        q.push(root);
        vector<vector<int>>res;
        int level=1;
        while(!q.empty())
        {
            int l=q.size();
            vector<int> temp_res;
            while(l--)
            {
                TreeNode* temp=q.front();
                q.pop();
                temp_res.push_back(temp->val);
                if(temp->left)q.push(temp->left);
                if(temp->right)q.push(temp->right);
            }
            if(level%2==0)//判断是否是偶数
                reverse(temp_res.begin(),temp_res.end());//反转数组
            level+=1;//记录深度
            res.push_back(temp_res);
        }
        return res;
    }
};
```