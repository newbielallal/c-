---
title: leetcode 94 二叉树的中序遍历
tags:
  - c++ 
categories: c++ 
---
用递归很简单。
<!-- more -->

### 题目
返回中序遍历
### 思路
就是利用递归实现中序遍历。
### code

     void zhongxu(TreeNode* root,vector<int>&res)
    {
        if(root->left!=NULL)
            zhongxu(root->left,res);
        res.push_back(root->val);
        if(root->right!=NULL)
            zhongxu(root->right,res);
        
    }
    vector<int> inorderTraversal(TreeNode* root) {
        if(root==NULL)
            return {};
        vector<int>res;
        zhongxu(root,res);
        return res;
    }

