**###题目**

根据一棵树的前序遍历与中序遍历构造二叉树。**注意:**你可以假设树中没有重复的元素。

- 输入：前序遍历 preorder = [3,9,20,15,7]，中序遍历 inorder = [9,3,15,20,7]
- 输出：

![img](https://pic1.zhimg.com/80/v2-84e2cd4453779382281bc2390f3a13f4_720w.jpg)

**###思路**

因为二叉树的前序和中序遍历可以确定一颗二叉树，利用递归解决这个问题。

根据前序遍历和中序遍历的规则，前序遍历是先遍历根节点，再遍历左子树，再遍历右子树，而中序遍历是先遍历左子树，再遍历根节点，再遍历右子树。

所以前序遍历数组的第一个元素就是根节点，然后因为题目中说树中不存在重复元素，所以可以利用这个特点在中序遍历中找到根节点的位置，然后就可以在中序遍历中将这棵树的左右子树分开，然后重复上面的过程处理左右两棵子树，递归的出口就是分成的左右子树中只有一个节点，返回此节点即可。

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
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
         if(preorder.size()==0||preorder.size()!=inorder.size())//长度不等直接错误
	            return NULL;
	        return solve(preorder,inorder,0,0,preorder.size());
    }
    TreeNode* solve(vector<int>const &pre,vector<int>const &vin,int preL,int inL,int n)
	{
	    if(n==0)//长度为0或1直接返回
	        return NULL;
	    if (n==1) 
	    {
	        
	        TreeNode* p=new TreeNode(pre[preL]); 
	        return p;
	    }
	    TreeNode* p=new TreeNode(pre[preL]); 
	    int i=0;
	    for (i=0; i<n; i++)
	    {
	        if (vin[inL+i] == p->val)//找到根节点的位置 
	            break;
	    }//划分左右子树
	    int  L = i; int R = n-L-1;//L，R代表左右子树的长度
	    p->left=solve(pre,vin,preL+1, inL, L);
	    p->right=solve(pre,vin,preL+L+1, inL+L+1, R);
	    return p;
	}
};
```