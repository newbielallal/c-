---
title: leetcode 98 验证二叉搜索树
tags:
  - c++ 
categories: c++ 
---
提供了leetcode 98题的两种解法，一种耗时40ms，一种耗时16ms。

<!-- more -->

### 题目
给定一个二叉树，判断其是否是一个有效的二叉搜索树。

假设一个二叉搜索树具有如下特征：

节点的左子树只包含小于当前节点的数。
节点的右子树只包含大于当前节点的数。
所有左子树和右子树自身必须也是二叉搜索树。

### 思路
按照二叉搜索树的定义，分别将它的左子树和右子树是否为二叉搜索树进行分别判断，例如zuo判断，如果节点没有左子树，则返回true，若节点有左子树，那节点要比所有的左子树的值大，需要一个栈将所有的左子树的值存入进行比较，然后再对节点的左节点进行左右子树是否为二叉搜索树判断，you判断同理，这里面会有大量的比较。没有利用上比如a大于b，b大于c，那a肯定大于c，而是做了两次比较a是否大于c，b是否大于c，存在冗余计算。
### code
    解法一（40ms，最开始自己写的）
    bool iszuo(TreeNode* root)
    {
        if(!root->left)
            return true;
        stack<TreeNode*> node;
        node.push(root->left);
        while(!node.empty())
        {
            TreeNode* p1=node.top();
            node.pop();
            if (p1->val>=root->val)
                return false;
            if(p1->left)
                node.push(p1->left);
            if(p1->right)
                node.push(p1->right);
        }
        
        return iszuo(root->left)&&isyou(root->left);
    }
    bool isyou(TreeNode* root)
    {
        if(!root->right)
            return true;
        stack<TreeNode*> node;
        node.push(root->right);
        while(!node.empty())
        {
            TreeNode* p1=node.top();
            node.pop();
            if (p1->val<=root->val)
                return false;
            if(p1->left)
                node.push(p1->left);
            if(p1->right)
                node.push(p1->right);
        }
        
        return iszuo(root->right)&&isyou(root->right);
    }
    bool isValidBST(TreeNode* root) {
        if (root==NULL)
            return true;
        return iszuo(root)&&isyou(root);
    }
### 思路

我们利用前序遍历对二叉树进行一次遍历，根据前序遍历的定义，首先遍历树的左子树，在遍历中间根节点，在遍历右子树，这样就相当于将二叉树从最左端的叶子开始慢慢遍历，一个根节点，只有在它的左边的节点全部进入遍历数组之后它才会进入遍历数组，它的右子树只有在它进入遍历数组之后才会进入遍历数组，所以我们将其实现前序遍历之后，只要比较数组是否是有序的就可以了。相比上一个对每一个子树进行检查，速度快了一倍。

### code
    解法二（利用前序遍历实现一个数组，16ms）
    void qianxuf(vector<int> &qianxu,TreeNode* root)//要记得用&还是*
       {
        if(root->left)
            qianxuf(qianxu,root->left);
        qianxu.push_back(root->val);
        if(root->right)
            qianxuf(qianxu,root->right);
        return ;
        }
    bool isValidBST(TreeNode* root) {
        if(root==NULL)
            return true;
        vector<int> qianxu;
        qianxuf(qianxu,root);
        for(int i=0;i<qianxu.size()-1;i++)
        {
            if(qianxu[i]>=qianxu[i+1])
                return false;
        }
        return true;
       }


