\###题目

给定一个二叉树，返回其按层次遍历的节点值，即逐层地，从左到右访问所有节点。

输入：

![img](https://pic1.zhimg.com/80/v2-4fef09f095fa80c7bfc946dc1f1b92e4_720w.jpg)

输出：[ [3],[9,20],[15,7]]

\###思路

层次遍历，利用BFS以及队列来循环处理。

- 从左至右将层内的节点都存入队列中，然后将每一层的节点值保存下来
- 从左至右将层内每个节点的左右子节点都保存在队列中用于下次处理
- 循环此过程，直到处理完所有节点

所以需要设置一个长度l用来存储队列内元素的长度，然后处理l次，每次处理的同时添加该节点的左右子节点在队列的后面，这样当l次处理完后，就刚好处理完了这一层的节点，并且队列中存储的都是下一层的节点。

\###code

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
    vector<vector<int>> levelOrder(TreeNode* root) {
        queue<TreeNode*>q;//用于保存节点。
        if(root==NULL)return {};
        q.push(root);//先添加根节点
        vector<vector<int>>res;
        while(!q.empty())
        {
            int l=q.size();//记录下待处理这一层的节点数
            vector<int> temp_res;
            while(l--)
            {
                TreeNode* temp=q.front();
                q.pop();
                temp_res.push_back(temp->val);//压如值
                if(temp->left)q.push(temp->left);//压如左右节点
                if(temp->right)q.push(temp->right);
            }
            res.push_back(temp_res);
        }
        return res;
    }
};
```