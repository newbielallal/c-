---
title: 重建二叉树
tags:
  - c++ 
categories: 剑指offer
---
这个题深刻的暴露了我的浅薄无知
<!-- more -->
题目描述
输入某二叉树的前序遍历和中序遍历的结果，请重建出该二叉树。假设输入的前序遍历和中序遍历的结果中都不含重复的数字。例如输入前序遍历序列{1,2,4,7,3,5,6,8}和中序遍历序列{4,7,2,1,5,3,8,6}，则重建二叉树并返回。
Ac代码：

	class Solution {
	public:
	    TreeNode* solve( vector<int>const &pre,vector<int>const &vin,int preL,int inL,int n)
	    {
	        if(n==0)
	            return NULL;
	        if (n==1) 
	        {
	            
	            TreeNode* p=new TreeNode(pre[preL]); 
	            return p;
	        }
	        int i;
	        int L;
	        int R;
	        TreeNode* p=new TreeNode(pre[preL]); 
	        for (i=0; i<n; i++)
	        {
	            if (vin[inL+i] == p->val) 
	                break;
	        }
	        L=i; 
	        R=n-L-1;
	        p->left=solve(pre,vin,preL+1, inL, L);
	        p->right=solve(pre,vin,preL+L+1, inL+L+1, R);
	        return p;
	    }
	    TreeNode* reConstructBinaryTree(vector<int> pre,vector<int> vin) {
	        if(pre.size()==0||pre.size()!=vin.size())
	            return NULL;
	        return solve(pre,vin,0,0,pre.size());
	    }
	};

之前一直错的代码：

```
	TreeNode* solve( vector<int>const &pre,vector<int>const &vin,int preL,int inL,int n)
	{
	    if(n==0)
	        return NULL;
	    if (n==1) 
	    {
	        TreeNode a=TreeNode(pre[preL]);
	        TreeNode* p=&a; 
	        return p;
	    }
	    TreeNode root = TreeNode(pre[preL]);
	    TreeNode* p=&root;
	    int i=0;
	    for (i=0; i<n; i++)
	    {
	        if (vin[inL+i] == root.val) 
	            break;
	    }
	    int  L = i; int R = n-L-1;
	    root.left=solve(pre,vin,preL+1, inL, L);
	    root.right=solve(pre,vin,preL+L+1, inL+L+1, R);
	    return p;
	}
	class Solution {
	public:
	    TreeNode* reConstructBinaryTree(vector<int> pre,vector<int> vin) {
	        if(pre.size()==0||pre.size()!=vin.size())
	            return NULL;
	        return solve(pre,vin,0,0,pre.size());
	    }
	};
```

首先函数定义在了类的外面，还要操作类的私有变量，然后是尽然直接生成一个局部变量用来作为最终的结果。
