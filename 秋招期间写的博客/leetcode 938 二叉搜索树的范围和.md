---
title: leetcode 938 二叉搜索树的范围和
tags:
  - c++ 
categories: c++ 
---
——————分隔符——————
<!-- more -->

### 题目
给定二叉搜索树的根结点 root，返回 L 和 R（含）之间的所有结点的值的和。

二叉搜索树保证具有唯一的值。
### 思路
充分利用二叉搜索树的性质，分三种情况考虑，第一种情况，如果某节点的值在左右值之间，那么首先加上此节点，其次我们应该无法确定左右子树的值是否会包含在这个范围内，所以再对左右子树的值进行判断。第二种情况，节点的值大于右边界，所以右子树肯定不会含有此范围的值，我们直接进入左子树寻找，第三种情况，节点小于左边界，同理，直接进入右子树寻找。
### code
     int rangeSumBST(TreeNode* root, int L, int R) {
        if(root == NULL){
            return 0;
        }
        if(root->val > R){
            return rangeSumBST(root->left, L, R);
        } else if(root->val < L){
            return rangeSumBST(root->right, L, R);
        } else {
            return root->val + rangeSumBST(root->left, L, R) + rangeSumBST(root->right, L, R);
        }

