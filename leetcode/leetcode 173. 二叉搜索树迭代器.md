**###题目**

实现一个二叉搜索树迭代器。你将使用二叉搜索树的根节点初始化迭代器。

调用 next() 将返回二叉搜索树中的下一个最小的数。

示例：

![img](https://pic4.zhimg.com/80/v2-83e235c8e412d661cf5ccc2938eda85f_720w.jpg)

BSTIterator iterator = new BSTIterator(root);

[iterator.next](https://link.zhihu.com/?target=http%3A//iterator.next)(); // 返回 3

[iterator.next](https://link.zhihu.com/?target=http%3A//iterator.next)(); // 返回 7

iterator.hasNext(); // 返回 true

[iterator.next](https://link.zhihu.com/?target=http%3A//iterator.next)(); // 返回 9

iterator.hasNext(); // 返回 true

[iterator.next](https://link.zhihu.com/?target=http%3A//iterator.next)(); // 返回 15

iterator.hasNext(); // 返回 true

[iterator.next](https://link.zhihu.com/?target=http%3A//iterator.next)(); // 返回 20

iterator.hasNext(); // 返回 false

提示：

next() 和 hasNext() 操作的时间复杂度是 O(1)，并使用 O(h) 内存，其中 h 是树的高度。

你可以假设 next() 调用总是有效的，也就是说，当调用 next() 时，BST 中至少存在一个下一个最小的数。

**###思路**

直接用的一个栈来保存二叉树的中序遍历的结果，但是分步骤放入节点，首先先输出左子树的节点，然后是根节点，最后是右节点。因为是平衡二叉树，这样栈的栈顶元素肯定是最小的值。next()的时间复杂度应该没达到O（1）的要求。

**##code**

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
class BSTIterator {
public:
    stack<TreeNode*>temp;
    BSTIterator(TreeNode* root) {
        TreeNode * temp_treenode = root;
        
        while(temp_treenode)
        {
            temp.push(temp_treenode);
            temp_treenode = temp_treenode->left;
        }
    }
    
    /** @return the next smallest number */
    int next() {
        TreeNode * temp_treenode = temp.top();
        int res = temp_treenode->val;
        temp.pop();
        temp_treenode = temp_treenode->right;
        while(temp_treenode)
        {
            temp.push(temp_treenode);
            temp_treenode=temp_treenode->left;
        }
        return res;
    }
    
    /** @return whether we have a next smallest number */
    bool hasNext() {
        return temp.size();
    }
};

/**
 * Your BSTIterator object will be instantiated and called as such:
 * BSTIterator* obj = new BSTIterator(root);
 * int param_1 = obj->next();
 * bool param_2 = obj->hasNext();
 */
```