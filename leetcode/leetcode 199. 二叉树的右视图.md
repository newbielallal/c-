**###题目**

给定一棵二叉树，想象自己站在它的右侧，按照从顶部到底部的顺序，返回从右侧所能看到的节点值。

- **输入:** [1,2,3,null,5,null,4]
- **输出:** [1, 3, 4]

示意图：

![img](https://pic2.zhimg.com/80/v2-045847509c3db6fabcaac8d43be24f8d_720w.jpg)

**###思路**

其实很简单，就是找出二叉树每一层的最后一个结点，那么直接层序遍历然后记录每一层的最后一个节点就可以了。

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
    vector<int> rightSideView(TreeNode* root) {
        vector<int>res;
        if(NULL == root)return res;
        queue<TreeNode*> saveRoot;

        saveRoot.push(root);
        while(!saveRoot.empty())
        {
            int lenRoot = saveRoot.size();
            res.push_back(saveRoot.back()->val);
            while(lenRoot--)
            {
                TreeNode* tempRoot = saveRoot.front();
                saveRoot.pop();
                if(tempRoot->left) saveRoot.push(tempRoot->left);
                if(tempRoot->right) saveRoot.push(tempRoot->right);
            }
        }
        return res;
    }
};
```