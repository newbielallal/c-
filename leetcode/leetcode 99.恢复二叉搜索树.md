**###题目**

二叉搜索树中的两个节点被错误地交换。请在不改变其结构的情况下，恢复这棵树。

![img](https://pic2.zhimg.com/80/v2-b583b3ccdf6dfca0fdb28550b4f05021_720w.jpg)

**###思路**

整个过程的流程是这样进行的：

- 中序遍历这棵树，得到中序遍历数组，因为二叉搜索树肯定严格递增序列。
- 文中提出有两个节点被交换了，被交换的两个节点在数组中是以逆序对的状态出现。所以在前序遍历数组中找到这一个逆序对。
- 然后把树中这个逆序对对应的节点的值进行交换即可。

所以整个代码分为三部分，第一部分对树进行中序遍历，第二部分找出遍历数组中的逆序对，第三部分，在树中交换该逆序对的值。

**###代码**

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
    void qianxu(TreeNode* root,vector<int>&tree)
    {
        if(root->left)
            qianxu(root->left,tree);
        tree.push_back(root->val);
        if(root->right)
            qianxu(root->right,tree);
        return ;
    }
    void bianli(TreeNode* root,int num1,int num2)//交换逆序对的值
    {
        if(root->val==num1)
            root->val=num2;
        else if(root->val==num2)
            root->val=num1;
        if(root->left)
            bianli(root->left,num1,num2);
        if(root->right)
            bianli(root->right,num1,num2);
        return ;

    }
    void recoverTree(TreeNode* root) {
        vector<int>tree;
        qianxu(root,tree);//前序遍历
        int num1,num2;
        bool flag=true;
        vector<int>tree_copy(tree);
        sort(tree_copy.begin(),tree_copy.end());
        for(int i=0;i<tree.size();++i)//找出该逆序对
        {
            if(tree[i]!=tree_copy[i]&&flag)
            {
                flag=false;
                num1=tree[i]; 
                continue;
            }
             if(tree[i]!=tree_copy[i])
            {
                num2=tree[i];
                break; 
            }
        }
        bianli(root,num1,num2);//交换该逆序对的值。
        return ;
    }
};
```

**###思路**

第一种方法需要 ![[公式]](https://www.zhihu.com/equation?tex=O%28n%29) 级别的额外空间，题目的进阶要求是常数的额外空间,想了很久没写出来，从评论区看到别人写的，用的Morris遍历，记录一下。

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
    // s1 存小索引那个结点，s2存大索引那个结点，pre存前驱结点
    TreeNode *s1 = NULL, *s2 = NULL, *pre = NULL;
    void recoverTree(TreeNode* root) {
        TreeNode* cur = root;  // 游标
        while(cur != NULL){           
            if(cur->left != NULL){  // 进入左子树
                // 找到cur的前驱结点，分两种情况
                // 1、cur的左子结点没有右子结点，那cur的左子结点就是前驱
                // 2、cur的左子结点有右子结点，就一路向右下，走到底就是cur的前驱
                TreeNode* predecessor = cur->left;
                while(predecessor->right != NULL && predecessor->right != cur){
                    predecessor = predecessor->right;
                }

                // 前驱还没有指向自己，说明左边还没有遍历，将前驱的右指针指向自己，后进入前驱
                if(predecessor->right == NULL){
                    predecessor->right = cur;
                    cur = cur->left;
                }else{
                    // 前驱已经指向自己了，直接比较是否有逆序对，然后进入右子树
                    if(pre != NULL && cur->val < pre->val){
                        if(s1 == NULL) s1 = pre;
                        s2 = cur;
                    }
                    pre = cur;
                    predecessor->right = NULL;
                    cur = cur->right;
                }
            }else{  // 左子树为空时，检查是否有逆序对，然后进入右子树
                if(pre != NULL && cur->val < pre->val){
                    if(s1 == NULL) s1 = pre;
                    s2 = cur;
                }
                pre = cur;
                cur = cur->right;
            }
        }
        // 进行交换
        int t = s1->val;
        s1->val = s2->val;
        s2->val = t;
        return;
    }
};
```