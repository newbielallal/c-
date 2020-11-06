**###题目**

根据一棵树的前序遍历与中序遍历构造二叉树。**注意:**你可以假设树中没有重复的元素。

- 输入：中序遍历 inorder = [9,3,15,20,7]，后序遍历 postorder = [9,15,7,20,3]
- 输出：

![img](https://pic3.zhimg.com/80/v2-09c8906cb5a5fc801e31477c6992ee7e_720w.jpg)

**###思路**

**第105题的镜像问题：**

只需要修改一下这两个地方就可以了：

- 前序遍历时，根节点在数组的首部，而后续遍历时，根节点在数组的尾部
- 递归的时候下一个寻找根节点的位置是从后开始，注意左右子树的递归参数。



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
    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
         if(postorder.size()==0||postorder.size()!=inorder.size())//长度不等直接错误
	            return NULL;
	        return solve(postorder,inorder,0,postorder.size()-1,postorder.size());
    }
    TreeNode* solve(vector<int>const &pre,vector<int>const &vin,int inL,int post,int n)
	{
	    if(n==0)//长度为0或1直接返回
	        return NULL;
	    if (n==1) 
	    {
	        
	        TreeNode* p=new TreeNode(pre[post]); 
	        return p;
	    }
	    TreeNode* p=new TreeNode(pre[post]); 
	    int i=0;
	    for (;i<n; ++i)
	    {
	        if (vin[inL+i] == p->val)//找到根节点的位置 
	            break;
	    }//划分左右子树
	    int  L = i; int R = n-L-1;//L，R代表左右子树的长度
	    p->left=solve(pre,vin,inL,post-1-R, L);
	    p->right=solve(pre,vin,inL+L+1, post-1, R);
	    return p;
	}
};
```