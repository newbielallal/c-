**###题目**

给定一个二叉树，[原地](https://link.zhihu.com/?target=https%3A//baike.baidu.com/item/%E5%8E%9F%E5%9C%B0%E7%AE%97%E6%B3%95/8010757)将它展开为链表。

- 输入：

![img](https://pic4.zhimg.com/80/v2-05be0530ba6333b99b0cec59ffc7c4df_720w.jpg)

- 输出：

![img](https://pic3.zhimg.com/80/v2-fe3b089fccf9ffa4b80b454b180577a2_720w.jpg)

**###思路**

题目没有要求时间和空间，所以先来一个最简单的版本，观察转化而成的链表，可以明显发现它的连接顺序为先根节点，再左子树，再右子树，所以通过先序遍历子树得到一个数组，然后再将此数组按顺序接在根节点上。

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
    void xianxu(TreeNode*root,vector<int>&num)
    {
        num.push_back(root->val);
        if(root->left)
        xianxu(root->left,num);
        if(root->right)
        xianxu(root->right,num);
        return ;
    }
    void flatten(TreeNode* root) {
        if(root==NULL)
            return ;
        vector<int>num;
        xianxu(root,num);
        root->right=NULL;
        root->left=NULL;
        for(int i=1;i<num.size();++i)
        {
            TreeNode*temp=new TreeNode(num[i]);
            root->right=temp;
            root=root->right;
        }
        return ;
    }
};
```

**###思路**

第一种方法需要额外的空间，如何对此方法进行优化，比如可以在遍历到节点的时候直接改变它的指向，那么就可以不用数组来保存了遍历过的节点了。但是这个过程注意一个问题就是改变了指向之后不能够丢失信息，所以采用先处理右子树，再处理左子树，最后处理根节点的方法避免丢失信息。处理过程中将所有处理过的节点全部整理为最后的链表形式，对于题目给出的例子来说就是这样一个处理流程：

- 先处理6，此时链表为6。
- 再处理5，此时链表为5->6。
- 再处理4，此时链表为4->5->6。
- 再处理3，此时链表为3->4->5->6。
- 再处理2，此时链表为2->3->4->5->6。
- 再处理1，此时链表为1->2->3->4->5->6。

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
    TreeNode* pre=NULL;
    void flatten(TreeNode* root) {
        if (root == NULL)
            return;
        flatten(root->right);
        flatten(root->left);
        root->right = pre;
        root->left = NULL;
        pre = root;
    }
};
```

**###思路**

第三种方法也是改变节点的指向，不过这个方法是从根节点开始处理的，从上往下处理，处理规则如下：

- 节点root是否有左子树，如果没有，访问它的右子树。
- 如果有左子树，那么找到root左子树的最右边的节点。
- 将root的右子树接在左子树的最右节点上。
- 将root的左子树接在原来右子树的位置。
- 将root的左子树置为NULL。
- 继续往下访问root->right。



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
    void flatten(TreeNode* root) {
        while(root)
        {
            if(root->left)
            {   
                TreeNode* temp=root->left;
                while(temp->right)
                    temp=temp->right;
                temp->right=root->right;
                root->right=root->left;
                root->left=NULL;
            }
            root=root->right;
        }
    }
};
```